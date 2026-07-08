---
name: architecture-report
description: "Produce an architecture / design document (ownership models, data-flow, module boundaries, lifetime/sequence explainers) as a dark-mode purple-accent PDF with rendered inline-SVG diagrams. Use when asked for a design doc, architecture write-up, or diagrammed explainer as a shareable PDF — matching the code-review report styling."
---

## Architecture / Design Report

Produces a design document as two deliverables side by side, written into a `design-docs/`
directory at the repo root, each filename prefixed with a datetime stamp:

1. `design-docs/<YYYY-MM-DD_HHMMSS>_<NAME>.md` — the written document, with **inline SVG
   diagrams** authored directly in the Markdown
2. `design-docs/<YYYY-MM-DD_HHMMSS>_<NAME>.pdf` — the same document rendered as a dark-mode
   PDF with purple accents (diagrams included)

The Markdown is authored by Claude; the PDF is generated from it by `render.sh`, so the two
never drift. This skill is self-contained (its own generator + stylesheet); the palette is
copied from the `code-review-report` skill so the two look consistent.

> **Output location & naming.** Always write under `design-docs/` with a shared datetime
> prefix so runs don't overwrite each other. Generate the timestamp once and reuse it:
>
> ```bash
> mkdir -p design-docs
> TS=$(date +%Y-%m-%d_%H%M%S)          # e.g. 2026-07-08_134801
> ```
>
> Consider adding `design-docs/` to `.gitignore` if these should stay local.

---

### Step 1 — Write the Markdown document

Write to `design-docs/${TS}_<NAME>.md`. Aim for this shape — it renders cleanly in the
template:

- An **Executive summary** answering the reader's actual question first.
- **Diagrams** as inline `<svg>` (see `assets/diagram-guide.md` before authoring them —
  it has the palette, the arrow/node conventions, reusable `<marker>` defs, and a
  copy-paste template).
- **Code sketches** in fenced blocks (label them illustrative if not applied edits).
- A **summary table** (e.g. mapping the design to the findings/requirements it resolves).
- A **migration / adoption order** when proposing a change.

Use headings, tables, fenced code blocks with language hints, `inline code` for symbols,
and blockquotes for callouts — the stylesheet themes all of these.

### Step 2 — Generate the PDF

```bash
.claude/skills/architecture-report/render.sh "design-docs/${TS}_<NAME>.md"
```

- Output defaults to the input path with a `.pdf` extension.
- Override: `render.sh <input.md> --out <file.pdf> --css <style.css>`

### Step 3 — Verify the diagrams (do not skip)

`pdftoppm` is often absent, so the `Read` tool may not be able to open the PDF. Render the
document to a **PNG** and read that back to confirm the SVG diagrams render — arrows land on
the right nodes, labels don't collide, nothing overflows the panel:

```bash
.claude/skills/architecture-report/render.sh "design-docs/${TS}_<NAME>.md" --png
```

Then `Read` the resulting `…preview.png`. Adjust the SVG coordinates and regenerate until it
looks right. Only then report both file paths back to the user.

---

### Requirements

- **Node / `npx`** — `render.sh` uses `npx --yes marked` (cached after first run).
- **Google Chrome** (or Chromium / Edge) — used headless for `--print-to-pdf` and
  `--screenshot`. Auto-detected from common macOS paths and PATH.

### Styling

The dark purple theme lives in `assets/report-style.css` (CSS custom properties at the top).
It adds base `svg`/`figure`/`figcaption` rules on top of the code-review palette. Retune the
variables or pass a different stylesheet via `--css`.

### Diagram conventions (summary)

Full details + templates in `assets/diagram-guide.md`. In short:

- **Solid purple** arrow = ownership (`unique_ptr` / by-value). **Dashed grey** = non-owning
  observer. **Dashed red** = unsafe / dangling. **Solid green** = ownership consolidated into
  a single owner.
- Nodes: rounded `<rect>` fill `#241f33` stroke `#4b3f6b`; danger node stroke `#fb7185`;
  highlighted "good" node stroke `#34d399`.
- Wrap each diagram in an `<svg viewBox="0 0 760 H">` panel (`background:#1b1728;
  border:1px solid #362e4d`) with `width:100%; max-width:760px`.
</content>
