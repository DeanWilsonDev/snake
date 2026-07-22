---
name: report-pdf
description: "Render any Markdown file into the house dark-mode (grey/black background, purple-accent) PDF style, with support for inline-SVG diagrams and a PNG preview mode for verifying them. Used internally by code-review-report and architecture-report to turn their authored Markdown into PDFs; invoke directly whenever asked to convert a Markdown file/report/doc to PDF in this style."
---

## Report PDF Renderer

Converts a Markdown file into a styled, dark-mode, purple-accent PDF via
`marked` (Markdown → HTML) → a shared stylesheet → headless Chrome
(`--print-to-pdf`). This is the shared rendering step other reporting skills
(`code-review-report`, `architecture-report`) delegate to, so their PDFs stay
visually consistent without duplicating a renderer each.

It can also be invoked directly: "convert this .md to a PDF" / "render this
report as a PDF" should reach for this skill.

---

### Usage

```bash
<this skill's directory>/render.sh <input.md>                 # -> <input>.pdf
<this skill's directory>/render.sh <input.md> --out out.pdf   # explicit output path
<this skill's directory>/render.sh <input.md> --css other.css # override stylesheet
```

The base directory for this skill is printed when it loads — run `render.sh`
from there (or reference it by that path) rather than assuming a fixed
project-relative location, since this skill may be installed globally
(`~/.claude/skills/report-pdf/`) or per-project (`.claude/skills/report-pdf/`).

### Verifying diagrams (Markdown containing inline `<svg>`)

`pdftoppm` is often unavailable, so the `Read` tool can't open the PDF
directly. Render a PNG snapshot instead and `Read` that back to check arrows
land on the right nodes, labels don't collide, and nothing overflows the
panel:

```bash
<this skill's directory>/render.sh <input.md> --png
<this skill's directory>/render.sh <input.md> --png --height 6000   # taller capture for a long doc
```

Adjust SVG coordinates in the source Markdown and re-render until it looks
right, *then* generate the final PDF. Skip this step entirely for
diagram-free Markdown.

### Requirements

- **Node / `npx`** — uses `npx --yes marked` (cached after first run).
- **Google Chrome** (or Chromium / Edge) — headless, for `--print-to-pdf` /
  `--screenshot`. Auto-detected from common macOS app paths and PATH names
  (`google-chrome`, `google-chrome-stable`, `chromium`, etc).

### Styling

The theme lives in `assets/report-style.css`: neutral grey/black background
(`--bg`, `--bg-alt`, `--code-bg`, `--inline-bg`, `--border`) with purple
accents preserved (`--accent`, `--accent-strong`, `--accent-soft`, `--link`)
plus semantic diagram colors (`--danger` red, `--safe` green). Retune the CSS
custom properties at the top of the file to restyle everything at once, or
pass a one-off stylesheet via `--css`.

Markdown support: headings, tables, fenced/inline code, blockquotes, lists,
links, horizontal rules, and raw inline `<svg>` (passed through untouched by
`marked` for diagrams). Tables and code blocks avoid breaking mid-element
across a PDF page.
