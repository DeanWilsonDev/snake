---
name: code-review-report
description: "Run a code review of a codebase and deliver the findings as a Markdown report, then render it via the report-pdf skill into a styled dark-mode PDF. Use when asked to review code and produce a report, export a review/audit to PDF, or generate a shareable code review document."
---

## Code Review Report

Produces a code review as a Markdown report, written into a `code-reviews/`
directory at the repo root, filename prefixed with a datetime stamp:

`code-reviews/<YYYY-MM-DD_HHMMSS>_CODE_REVIEW.md` — severity-ranked findings
with `file:line` references.

The PDF companion is generated afterwards by the `report-pdf` skill, so the
rendering pipeline is shared (and stays visually consistent) with every other
report this project produces.

> **Output location & naming.** Always write reports under `code-reviews/` with
> a datetime-stamped filename so runs don't overwrite each other:
>
> ```bash
> mkdir -p code-reviews
> TS=$(date +%Y-%m-%d_%H%M%S)          # e.g. 2026-07-07_124914
> ```
>
> Consider adding `code-reviews/` to the project's `.gitignore` if it isn't already.

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

### Step 2 — Render the PDF

Invoke the `report-pdf` skill (or run its `render.sh` directly) against the Markdown file
just written:

```bash
<report-pdf skill directory>/render.sh "code-reviews/${TS}_CODE_REVIEW.md"
```

This writes `code-reviews/${TS}_CODE_REVIEW.pdf` next to the Markdown, styled with the
shared dark-mode/purple-accent theme. Report both file paths back to the user when done.

---

### Notes

- This skill contains no rendering logic of its own — `report-pdf` owns the
  Markdown→HTML→PDF pipeline and its stylesheet, shared across every report
  skill in this project.
- Standard GitHub-flavoured Markdown is supported: headings, tables,
  fenced/inline code, blockquotes, lists, links, horizontal rules.
