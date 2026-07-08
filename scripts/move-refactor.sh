#!/usr/bin/env bash
#
# move-refactor.sh — move a source file and update every reference to it.
#
# Moves  src/<old>  ->  src/<new>  and, across src/ and tests/:
#   1. rewrites  #include "<old>"       ->  #include "<new>"
#   2. rewrites  <OldNamespace>::Type   ->  <NewNamespace>::Type   (fully-qualified only)
#   3. rewrites the moved file's own  namespace  declaration
#   4. REPORTS forward-declarations and other refs that need a human eye
#
# Namespaces are assumed to mirror the folder structure under src/, e.g.
#   src/core/spatial/i-transform-2d.hpp   ->  namespace Core::Spatial
#   src/engine/spatial/components/x.hpp   ->  namespace Engine::Spatial::Components
# kebab-case folders map to PascalCase segments: renderer-2d -> Renderer2D.
#
# Dry-run by default. Pass --apply to actually change files.
#
# Usage:
#   scripts/move-refactor.sh <old-path> <new-path> [--apply]
#   scripts/move-refactor.sh src/core/math/i-transform-2d.hpp src/core/spatial/i-transform-2d.hpp
#   scripts/move-refactor.sh src/core/math/i-transform-2d.hpp src/core/spatial/i-transform-2d.hpp --apply
#
set -euo pipefail

# ----- pretty output ---------------------------------------------------------
if [ -t 1 ]; then
  BOLD=$(printf '\033[1m'); DIM=$(printf '\033[2m'); RED=$(printf '\033[31m')
  GRN=$(printf '\033[32m'); YEL=$(printf '\033[33m'); CYN=$(printf '\033[36m'); RST=$(printf '\033[0m')
else
  BOLD=; DIM=; RED=; GRN=; YEL=; CYN=; RST=
fi
info()  { printf '%s\n' "$*"; }
step()  { printf '\n%s==>%s %s%s%s\n' "$CYN" "$RST" "$BOLD" "$*" "$RST"; }
warn()  { printf '%s!! %s%s\n' "$YEL" "$*" "$RST"; }
err()   { printf '%sxx %s%s\n' "$RED" "$*" "$RST" >&2; }
ok()    { printf '%s ok %s%s\n' "$GRN" "$*" "$RST"; }

usage() { sed -n '2,26p' "$0" | sed 's/^#//; s/^ //'; exit "${1:-0}"; }

# ----- args ------------------------------------------------------------------
MODE=dry
OLD_ARG=""; NEW_ARG=""
for a in "$@"; do
  case "$a" in
    --apply) MODE=apply ;;
    -h|--help) usage 0 ;;
    -*) err "unknown flag: $a"; usage 1 ;;
    *) if [ -z "$OLD_ARG" ]; then OLD_ARG="$a"; elif [ -z "$NEW_ARG" ]; then NEW_ARG="$a"; else err "too many args"; usage 1; fi ;;
  esac
done
[ -n "$OLD_ARG" ] && [ -n "$NEW_ARG" ] || usage 1

ROOT=$(git rev-parse --show-toplevel 2>/dev/null || pwd)
cd "$ROOT"

# Normalise the two paths to be relative to the repo root and under src/.
norm() { # -> repo-relative path
  local p="$1"
  p="${p#./}"
  case "$p" in
    "$ROOT"/*) p="${p#"$ROOT"/}" ;;
  esac
  printf '%s' "$p"
}
OLD_REL=$(norm "$OLD_ARG")
NEW_REL=$(norm "$NEW_ARG")

case "$OLD_REL" in src/*) ;; *) err "old path must be under src/ (got: $OLD_REL)"; exit 1 ;; esac
case "$NEW_REL" in src/*) ;; *) err "new path must be under src/ (got: $NEW_REL)"; exit 1 ;; esac
[ -f "$OLD_REL" ] || { err "file not found: $OLD_REL"; exit 1; }
[ -e "$NEW_REL" ] && { err "destination already exists: $NEW_REL"; exit 1; }

# Include strings are paths relative to src/ (project-root include convention).
INC_OLD="${OLD_REL#src/}"
INC_NEW="${NEW_REL#src/}"
OLD_DIR=$(dirname "$INC_OLD")
NEW_DIR=$(dirname "$INC_NEW")

SCAN=(src)
[ -d tests ] && SCAN+=(tests)

# ----- path <-> namespace helpers -------------------------------------------
pascal_segment() { # kebab-case -> PascalCase (renderer-2d -> Renderer2D)
  perl -e '
    my $s = shift @ARGV;
    my @w = split /-/, $s;
    for my $t (@w) { $t =~ s/^(.)/\U$1/; $t =~ s/(\d)(\p{L})/$1 . uc($2)/ge; }
    print join("", @w);
  ' "$1"
}
path_to_ns() { # dir relative to src -> Foo::Bar::Baz
  local out="" seg
  local IFS='/'
  for seg in $1; do
    [ -z "$seg" ] || [ "$seg" = "." ] && continue
    local p; p=$(pascal_segment "$seg")
    out="${out:+$out::}$p"
  done
  printf '%s' "$out"
}
detect_ns() { # namespace chain that actually wraps the type DEFINITION
  # Brace-aware so leading forward-declaration blocks (namespace X { class Y; })
  # are entered and exited rather than mistaken for the file's real namespace.
  perl -e '
    my (@stack, @open_at, @res); my $depth = 0;
    open my $fh, "<", $ARGV[0] or die;
    while (my $l = <$fh>) {
      $l =~ s{//.*$}{};
      if ($l =~ /^\s*namespace\s+([A-Za-z0-9_:]+)\s*\{/) {   # namespace opener
        push @stack, [split /::/, $1]; push @open_at, $depth; $depth++; next;
      }
      if ($l =~ /^\s*(?:class|struct|enum)\b/ && !($l =~ /;/ && $l !~ /\{/)) {  # real definition (has { , not a fwd-decl)
        push @res, @$_ for @stack; last;
      }
      $depth += ($l =~ tr/{//) - ($l =~ tr/}//);            # track scope depth
      while (@open_at && $depth <= $open_at[-1]) { pop @open_at; pop @stack; }
    }
    print join("::", @res);
  ' "$1"
}

OLD_NS=$(path_to_ns "$OLD_DIR")
NEW_NS=$(path_to_ns "$NEW_DIR")
ACTUAL_NS=$(detect_ns "$OLD_REL")

# Types defined (not just forward-declared) in the file being moved.
mapfile -t TYPES < <(
  perl -ne 'if (/^\s*(?:class|struct)\s+([A-Za-z_]\w*)\b/)      { my $n=$1; print "$n\n" unless (/;/ && !/\{/); }
            elsif (/^\s*enum\s+(?:class\s+)?([A-Za-z_]\w*)\b/)  { my $n=$1; print "$n\n" unless (/;/ && !/\{/); }' \
    "$OLD_REL" | sort -u
)

# ----- plan ------------------------------------------------------------------
step "Plan"
info "  move        ${DIM}$OLD_REL${RST}  ->  ${DIM}$NEW_REL${RST}"
info "  include     ${DIM}\"$INC_OLD\"${RST}  ->  ${DIM}\"$INC_NEW\"${RST}"
info "  namespace   ${DIM}$OLD_NS${RST}  ->  ${DIM}$NEW_NS${RST}"
info "  types       ${TYPES[*]:-(none found)}"
if [ "$MODE" = dry ]; then info "  ${YEL}mode        DRY RUN (pass --apply to write changes)${RST}"
else info "  ${GRN}mode        APPLY${RST}"; fi

# Safety gate: only touch namespaces if the file really follows folder=namespace.
DO_NS=1
if [ "$ACTUAL_NS" != "$OLD_NS" ]; then
  DO_NS=0
  warn "This file's declared namespace is '$ACTUAL_NS', but its folder implies '$OLD_NS'."
  warn "It does NOT follow the folder=namespace convention, so namespace rewrites are"
  warn "SKIPPED. Includes will still be updated. Fix the namespace by hand (or align the"
  warn "convention first, then re-run)."
fi

# ----- editing helpers -------------------------------------------------------
# Collect candidate files once.
mapfile -t ALLFILES < <(find "${SCAN[@]}" \( -name '*.hpp' -o -name '*.cpp' \) -type f)

apply_perl() { # $1 = perl expr ; applies in-place across all files (apply mode only)
  [ "$MODE" = apply ] || return 0
  perl -i -pe "$1" "${ALLFILES[@]}"
}
preview_grep() { # $1 = extended-regex ; list matching lines (dry mode)
  grep -rnE --include='*.hpp' --include='*.cpp' "$1" "${SCAN[@]}" 2>/dev/null || true
}

# ----- 1. includes -----------------------------------------------------------
step "Includes referencing \"$INC_OLD\""
INC_HITS=$(preview_grep "#include[[:space:]]*[\"<]${INC_OLD//./\\.}[\">]")
if [ -n "$INC_HITS" ]; then
  info "$INC_HITS"
  apply_perl 's{(#include\s*)"'"$(perl -e 'print quotemeta shift' "$INC_OLD")"'"}{$1"'"$INC_NEW"'"}g;
              s{(#include\s*)<'"$(perl -e 'print quotemeta shift' "$INC_OLD")"'>}{$1<'"$INC_NEW"'>}g'
else
  info "  (none)"
fi

# ----- 2. fully-qualified references -----------------------------------------
if [ "$DO_NS" = 1 ] && [ "$OLD_NS" != "$NEW_NS" ] && [ "${#TYPES[@]}" -gt 0 ]; then
  step "Fully-qualified references  $OLD_NS::<Type>  ->  $NEW_NS::<Type>"
  for T in "${TYPES[@]}"; do
    Q=$(perl -e 'print quotemeta shift' "$OLD_NS::$T")
    HITS=$(preview_grep "(^|[^A-Za-z0-9_:])${Q}([^A-Za-z0-9_]|\$)")
    CNT=$(printf '%s' "$HITS" | grep -c . || true)
    info "  ${BOLD}$T${RST}: $CNT reference(s)"
    [ -n "$HITS" ] && printf '%s\n' "$HITS" | sed 's/^/    /'
    apply_perl 's/(?<![\w:])'"$Q"'\b/'"$NEW_NS::$T"'/g'
  done
fi

# ----- 3. the moved file's own namespace -------------------------------------
if [ "$DO_NS" = 1 ] && [ "$OLD_NS" != "$NEW_NS" ]; then
  step "Rewrite namespace inside the moved file"
  TARGET="$OLD_REL"   # edited in place at its old path; the git mv happens last
  if [ "$MODE" = apply ]; then
    # single-line form:  namespace Old::Ns {   and closing  // namespace Old::Ns
    perl -i -pe 's/\bnamespace\s+'"$(perl -e 'print quotemeta shift' "$OLD_NS")"'\b/namespace '"$NEW_NS"'/g;
                 s{//\s*namespace\s+'"$(perl -e 'print quotemeta shift' "$OLD_NS")"'\b}{// namespace '"$NEW_NS"'}g' "$TARGET"
    # nested form: replace each differing segment (same-depth moves)
    readarray -t O < <(printf '%s\n' "$OLD_NS" | perl -pe 's/::/\n/g')
    readarray -t N < <(printf '%s\n' "$NEW_NS" | perl -pe 's/::/\n/g')
    if [ "${#O[@]}" = "${#N[@]}" ]; then
      for i in "${!O[@]}"; do
        [ "${O[$i]}" = "${N[$i]}" ] && continue
        perl -i -pe 's/\bnamespace\s+'"${O[$i]}"'\b/namespace '"${N[$i]}"'/g;
                     s{//\s*namespace\s+'"${O[$i]}"'\b}{// namespace '"${N[$i]}"'}g' "$TARGET"
      done
    fi
    ok "updated namespace in $TARGET (verify it reads 'namespace $NEW_NS')"
  else
    info "  will change  ${DIM}namespace $OLD_NS${RST}  ->  ${DIM}namespace $NEW_NS${RST}  in $OLD_REL"
    grep -nE '^\s*namespace' "$OLD_REL" | sed 's/^/    /'
  fi
fi

# ----- 3b. compact single-line forward-declarations (auto-rewritten) --------
# Matches exactly:   namespace <OLD_NS> { struct|class <T>; }
# One type per line and nothing else in the block, so swapping the namespace is
# unambiguous and safe. Multi-type blocks / nested staircases fall through to (4).
if [ "$DO_NS" = 1 ] && [ "$OLD_NS" != "$NEW_NS" ] && [ "${#TYPES[@]}" -gt 0 ]; then
  step "Compact forward-declarations  namespace $OLD_NS { .. }  ->  namespace $NEW_NS { .. }"
  FOUND_COMPACT=0
  for T in "${TYPES[@]}"; do
    PAT="^[[:space:]]*namespace[[:space:]]+${OLD_NS}[[:space:]]*\{[[:space:]]*(class|struct)[[:space:]]+${T}[[:space:]]*;[[:space:]]*\}"
    HITS=$(grep -rnE --include='*.hpp' --include='*.cpp' "$PAT" "${SCAN[@]}" 2>/dev/null \
           | grep -v -e "$OLD_REL" -e "$NEW_REL" || true)
    if [ -n "$HITS" ]; then
      FOUND_COMPACT=1
      info "  ${BOLD}$T${RST}:"
      printf '%s\n' "$HITS" | sed 's/^/    /'
      if [ "$MODE" = apply ]; then
        QO=$(perl -e 'print quotemeta shift' "$OLD_NS")
        QT=$(perl -e 'print quotemeta shift' "$T")
        perl -i -pe 's/\bnamespace\s+'"$QO"'\b/namespace '"$NEW_NS"'/'" if "'/^\s*namespace\s+'"$QO"'\s*\{\s*(?:class|struct)\s+'"$QT"'\s*;\s*\}/;' "${ALLFILES[@]}"
      fi
    fi
  done
  if [ "$FOUND_COMPACT" = 1 ]; then
    [ "$MODE" = apply ] && ok "rewrote compact forward-declarations" || info "  ${YEL}(will rewrite on --apply)${RST}"
  else
    info "  (none)"
  fi
fi

# ----- 4. things a human must review ----------------------------------------
step "Manual review (NOT auto-changed)"
FOUND_MANUAL=0
if [ "${#TYPES[@]}" -gt 0 ]; then
  for T in "${TYPES[@]}"; do
    FWD=$(grep -rnE --include='*.hpp' --include='*.cpp' "^[[:space:]]*(class|struct)[[:space:]]+${T}[[:space:]]*;" "${SCAN[@]}" 2>/dev/null \
          | grep -v -e "$OLD_REL" -e "$NEW_REL" || true)
    if [ -n "$FWD" ]; then
      FOUND_MANUAL=1
      warn "nested/bare forward-declarations of '$T' — fix by hand, or migrate them to the"
      warn "compact form  ${BOLD}namespace $NEW_NS { class $T; }${RST}${YEL}  which this tool rewrites automatically:"
      printf '%s\n' "$FWD" | sed 's/^/    /'
    fi
  done
fi
if [ "$DO_NS" = 1 ]; then
  info "${DIM}  Note: only FULLY-qualified ($OLD_NS::Type) references are rewritten."
  info "  Partially-qualified refs (e.g. 'Spatial::Type' relative to an enclosing"
  info "  'namespace Core {') are NOT detected — grep for them if the build complains.${RST}"
fi
[ "$FOUND_MANUAL" = 0 ] && info "  (no forward-declarations found)"

# ----- 5. the move ------------------------------------------------------------
step "Move the file"
if [ "$MODE" = apply ]; then
  mkdir -p "$(dirname "$NEW_REL")"
  if git ls-files --error-unmatch "$OLD_REL" >/dev/null 2>&1; then
    git mv "$OLD_REL" "$NEW_REL"
  else
    mv "$OLD_REL" "$NEW_REL"
  fi
  ok "moved $OLD_REL -> $NEW_REL"
else
  info "  will run:  ${DIM}git mv $OLD_REL $NEW_REL${RST}"
fi

# ----- done ------------------------------------------------------------------
step "Done"
if [ "$MODE" = dry ]; then
  info "Dry run only — nothing changed. Re-run with ${BOLD}--apply${RST} to perform the move."
else
  info "Applied. Now ${BOLD}rebuild${RST} and address anything under 'Manual review' above:"
  info "  ${DIM}cmake --build build${RST}"
fi
