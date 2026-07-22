---
name: architecture-report
description: "Produce an architecture / design document (ownership models, data-flow, module boundaries, lifetime/sequence explainers) as Markdown with rendered inline-SVG diagrams, then render it via the report-pdf skill into a dark-mode purple-accent PDF. Use when asked for a design doc, architecture write-up, or diagrammed explainer as a shareable PDF — matching the code-review report styling."
---

## Architecture / Design Report

Produces a design document as Markdown, written into a `design-docs/`
directory at the repo root, filename prefixed with a datetime stamp:

`design-docs/<YYYY-MM-DD_HHMMSS>_<NAME>.md` — the written document, with
**inline SVG diagrams** authored directly in the Markdown.

The PDF companion is generated afterwards by the `report-pdf` skill, so the
rendering pipeline (and visual style) is shared with every other report this
project produces — this skill owns only the *content*.

> **Output location & naming.** Always write under `design-docs/` with a
> datetime-stamped filename so runs don't overwrite each other:
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

> **Important — raw HTML block rule.** `marked` (CommonMark) ends an inline
> `<svg>...</svg>` HTML block at the first blank line inside it. Do **not**
> leave blank lines between elements inside an `<svg>` — keep every line from
> `<svg ...>` to `</svg>` blank-line-free, or the SVG splits and later tags
> get wrapped in stray `<p>` tags instead of rendering as part of the image.

### Step 2 — Render the PDF

Invoke the `report-pdf` skill (or run its `render.sh` directly) against the Markdown file
just written:

```bash
<report-pdf skill directory>/render.sh "design-docs/${TS}_<NAME>.md"
```

Output defaults to the input path with a `.pdf` extension.

### Step 3 — Verify the diagrams (do not skip)

`pdftoppm` is often absent, so the `Read` tool may not be able to open the PDF. Render the
document to a **PNG** via the `report-pdf` skill and read that back to confirm the SVG
diagrams render — arrows land on the right nodes, labels don't collide, nothing overflows
the panel:

```bash
<report-pdf skill directory>/render.sh "design-docs/${TS}_<NAME>.md" --png
```

Then `Read` the resulting `…preview.png`. Adjust the SVG coordinates and regenerate until it
looks right. Only then report both file paths back to the user.

---

### Diagram conventions (summary)

Full details + templates in `assets/diagram-guide.md`. In short:

- **Solid purple** arrow = ownership (`unique_ptr` / by-value). **Dashed grey** = non-owning
  observer. **Dashed red** = unsafe / dangling. **Solid green** = ownership consolidated into
  a single owner.
- Nodes: rounded `<rect>` fill `#242424` stroke `#4a4a4e`; danger node stroke `#fb7185`;
  highlighted "good" node stroke `#34d399`.
- Wrap each diagram in an `<svg viewBox="0 0 760 H">` panel (`background:#17171a;
  border:1px solid #3a3a3a`) with `width:100%; max-width:760px`.

### Notes

- This skill contains no rendering logic of its own — `report-pdf` owns the
  Markdown→HTML→PDF pipeline and its stylesheet, shared across every report
  skill in this project. See that skill for requirements (Node/`npx`, Chrome)
  and styling details.
