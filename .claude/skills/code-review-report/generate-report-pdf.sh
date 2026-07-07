#!/usr/bin/env bash
#
# generate-report-pdf.sh — render a Markdown report into a styled dark-mode PDF.
#
# Usage:
#   ./generate-report-pdf.sh <input.md> [output.pdf] [style.css]
#
# Defaults:
#   output.pdf  -> same path as input with a .pdf extension
#   style.css   -> assets/report-style.css next to this script (dark / purple)
#
# Pipeline: marked (GFM) -> HTML  ->  wrap in styled template  ->  Chrome --print-to-pdf
# Requires: npx (Node) and Google Chrome. No network needed after marked is cached once.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

INPUT="${1:-}"
if [[ -z "$INPUT" || ! -f "$INPUT" ]]; then
  echo "error: input markdown file not found: '${INPUT:-<none>}'" >&2
  echo "usage: $0 <input.md> [output.pdf] [style.css]" >&2
  exit 1
fi

OUTPUT="${2:-${INPUT%.*}.pdf}"
CSS="${3:-$SCRIPT_DIR/assets/report-style.css}"
if [[ ! -f "$CSS" ]]; then
  echo "error: stylesheet not found: $CSS" >&2
  exit 1
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
if [[ -z "$CHROME" ]]; then
  echo "error: could not find Chrome/Chromium/Edge to print the PDF" >&2
  exit 1
fi

TITLE="$(basename "${INPUT%.*}")"
TMPDIR_R="$(mktemp -d)"
trap 'rm -rf "$TMPDIR_R"' EXIT
BODY="$TMPDIR_R/body.html"
PAGE="$TMPDIR_R/report.html"

# --- markdown -> html body ---
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

# --- html -> pdf ---
"$CHROME" --headless --disable-gpu --no-pdf-header-footer \
  --print-to-pdf="$OUTPUT" "file://$PAGE" >/dev/null 2>&1

if [[ -f "$OUTPUT" ]]; then
  echo "✔ PDF written: $OUTPUT"
else
  echo "error: PDF was not produced" >&2
  exit 1
fi
