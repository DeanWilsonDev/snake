---
name: code-review-report
description: "Run a code review of a codebase and deliver the findings as both a Markdown report and a styled dark-mode (purple accent) PDF. Use when asked to review code and produce a report, export a review/audit to PDF, or generate a shareable code review document."
---

## Code Review Report

Produces a code review as two deliverables side by side, written into a `code-reviews/`
directory at the repo root, each filename prefixed with a datetime stamp:

1. `code-reviews/<YYYY-MM-DD_HHMMSS>_CODE_REVIEW.md` — the written report (severity-ranked
   findings with `file:line` references)
2. `code-reviews/<YYYY-MM-DD_HHMMSS>_CODE_REVIEW.pdf` — the same report rendered as a
   dark-mode PDF with purple accents

The Markdown is authored by Claude; the PDF is generated from it by
`generate-report-pdf.sh`, so the two never drift.

> **Output location & naming.** Always write reports under `code-reviews/` with a shared
> datetime prefix so runs don't overwrite each other. Generate the timestamp once and
> reuse it for both files:
>
> ```bash
> mkdir -p code-reviews
> TS=$(date +%Y-%m-%d_%H%M%S)          # e.g. 2026-07-07_124914
> ```
>
> Then write the Markdown to `code-reviews/${TS}_CODE_REVIEW.md`. Consider adding
> `code-reviews/` to the project's `.gitignore` if it isn't already.

---

### Step 1 — Write the Markdown report

Review the code and write findings to `code-reviews/${TS}_CODE_REVIEW.md` (create the
directory and timestamp as shown above). Aim for this shape — it renders cleanly in the
PDF template:

- An **Executive summary** answering the user's actual question first.
- A **severity-ranked findings table** (columns: `#`, Severity, Area, `Location`, Issue),
  with intra-document anchor links to detail sections.
- **Detailed findings**, each with the exact `file:line`, a code excerpt in a fenced
  block, root cause, and a concrete fix.
- A **recommended fix order** and any tooling suggestions.

Use severity emoji (🔴 Critical / 🟠 High / 🟡 Medium / 🟢 Low), fenced code blocks with
language hints, and `inline code` for symbols and paths — the stylesheet themes all of these.

### Step 2 — Generate the styled PDF

Run the script (it does: `marked` → HTML → styled template → Chrome `--print-to-pdf`):

```bash
~/.claude/skills/code-review-report/generate-report-pdf.sh "code-reviews/${TS}_CODE_REVIEW.md"
```

- Output defaults to the input path with a `.pdf` extension, so it lands next to the
  Markdown in `code-reviews/` with the same datetime prefix.
- Override output or stylesheet: `generate-report-pdf.sh <input.md> [output.pdf] [style.css]`
- Make it executable once if needed: `chmod +x ~/.claude/skills/code-review-report/generate-report-pdf.sh`

Report both file paths back to the user when done.

---

### Requirements

- **Node / `npx`** — the script uses `npx --yes marked` (cached after first run).
- **Google Chrome** (or Chromium / Edge) — used headless for `--print-to-pdf`. The script
  auto-detects common macOS install paths and PATH fallbacks.

### Styling

The dark-mode purple theme lives in `assets/report-style.css` (CSS custom properties at
the top — `--bg`, `--accent`, `--accent-strong`, etc.). Edit those variables to retune, or
pass a different stylesheet as the third argument to the script. Pages are full-bleed dark
(`@page { margin: 0 }` with body padding) so backgrounds print edge to edge.

### Notes

- The template supports headings, tables, fenced/inline code, blockquotes, lists, links,
  and horizontal rules — standard GitHub-flavoured Markdown.
- Tables and code blocks are set to avoid page breaks mid-element.
- No network access is needed once `marked` has been fetched by `npx` the first time.
