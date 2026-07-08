#!/usr/bin/env bash
#
# render.sh — render a Markdown design doc into a styled dark-mode PDF (or a PNG preview).
#
# Usage:
#   ./render.sh <input.md>                 # -> <input>.pdf
#   ./render.sh <input.md> --png           # -> <input>.preview.png  (for visual verification)
#   ./render.sh <input.md> --out f.pdf     # explicit output path
#   ./render.sh <input.md> --css s.css     # override stylesheet
#   ./render.sh <input.md> --png --height 3600   # taller PNG capture
#
# Pipeline: marked (GFM) -> HTML -> wrap in styled template -> Chrome (--print-to-pdf | --screenshot)
# Requires: npx (Node) and Google Chrome. No network needed after marked is cached once.

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

INPUT=""; MODE="pdf"; OUT=""; CSS="$SCRIPT_DIR/assets/report-style.css"; HEIGHT=3400; WIDTH=820
while [[ $# -gt 0 ]]; do
  case "$1" in
    --png)    MODE="png" ;;
    --out)    OUT="${2:-}"; shift ;;
    --css)    CSS="${2:-}"; shift ;;
    --height) HEIGHT="${2:-}"; shift ;;
    -h|--help) sed -n '2,15p' "$0" | sed 's/^#//; s/^ //'; exit 0 ;;
    -*) echo "unknown flag: $1" >&2; exit 1 ;;
    *)  INPUT="$1" ;;
  esac
  shift
done

if [[ -z "$INPUT" || ! -f "$INPUT" ]]; then
  echo "error: input markdown file not found: '${INPUT:-<none>}'" >&2; exit 1
fi
[[ -f "$CSS" ]] || { echo "error: stylesheet not found: $CSS" >&2; exit 1; }
if [[ -z "$OUT" ]]; then
  [[ "$MODE" == "png" ]] && OUT="${INPUT%.*}.preview.png" || OUT="${INPUT%.*}.pdf"
fi

# --- locate Chrome (macOS names + PATH fallbacks) ---
CHROME=""
for c in \
  "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" \
  "/Applications/Chromium.app/Contents/MacOS/Chromium" \
  "/Applications/Microsoft Edge.app/Contents/MacOS/Microsoft Edge" \
  "google-chrome" "chromium" "chrome"; do
  if [[ -x "$c" ]] || command -v "$c" >/dev/null 2>&1; then CHROME="$c"; break; fi
done
[[ -n "$CHROME" ]] || { echo "error: could not find Chrome/Chromium/Edge" >&2; exit 1; }

TITLE="$(basename "${INPUT%.*}")"
TMP="$(mktemp -d)"; trap 'rm -rf "$TMP"' EXIT
BODY="$TMP/body.html"; PAGE="$TMP/page.html"

# --- markdown -> html body (raw inline SVG passes through) ---
npx --yes marked --gfm -i "$INPUT" -o "$BODY" >/dev/null 2>&1

# --- assemble styled, self-contained html ---
{
  printf '<!DOCTYPE html>\n<html lang="en"><head><meta charset="utf-8">\n'
  printf '<title>%s</title>\n<style>\n' "$TITLE"
  cat "$CSS"
  printf '\n</style></head><body>\n'
  cat "$BODY"
  printf '\n</body></html>\n'
} > "$PAGE"

# --- render ---
if [[ "$MODE" == "png" ]]; then
  "$CHROME" --headless --disable-gpu --hide-scrollbars \
    --window-size="$WIDTH,$HEIGHT" --screenshot="$OUT" "file://$PAGE" >/dev/null 2>&1
else
  "$CHROME" --headless --disable-gpu --no-pdf-header-footer \
    --print-to-pdf="$OUT" "file://$PAGE" >/dev/null 2>&1
fi

if [[ -f "$OUT" ]]; then
  echo "✔ ${MODE^^} written: $OUT"
else
  echo "error: $MODE was not produced" >&2; exit 1
fi
