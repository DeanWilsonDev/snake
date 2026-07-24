---
name: completion-status-report
description: "Produce a 'how close to done' status report for a project: current build/run status verified directly (not just trusted from docs), a feature-by-feature comparison against a reference/target implementation when one exists (a branch, tag, earlier commit, or spec), and a dependency-ordered punch list to close the gap — as Markdown with two inline-SVG diagrams (a date-proportional milestone timeline and a remaining-work breakdown). Use when asked how close a project or feature is to finished, for a completion/progress status report, or 'where are we in the project lifecycle'. Writes only the .md — PDF rendering is a separate, explicitly-invoked step via the report-pdf skill."
---

## Completion Status Report

Produces a "how far from done" status report as Markdown, written to
`code-reviews/<YYYY-MM-DD>-completion-status.md` (matching this project's existing
`code-reviews/`/`design-docs/` convention for datestamped analysis output — if the
target repo uses a different convention for review/analysis output, e.g. `reports/`,
match that instead).

**This skill writes the Markdown and stops.** Same rule as `architecture-report` and
`code-review-report`: no auto-render of a PDF at the end — that's an explicit, separate
step via `/report-pdf`, run after the content has been reviewed. The one exception:
**diagrams must be verified with a PNG render before finishing** (Step 4) — that's
checking your own work, not producing the deliverable early.

---

### Step 1 — Gather ground truth, not just the paper trail

Read whatever progress-tracking docs exist (dev logs, `CHANGELOG`, design docs, prior
status reports) for the project's own account of where things stand — but treat every
claim in them ("this compiles", "X is implemented", "Y is wired up") as a hypothesis to
check, not a fact to repeat:

- **Run the actual build/test/start-up**, don't just read about it. A doc claiming
  something compiles is worth nothing next to actually running the build — this is
  usually where the most interesting, undocumented findings turn up (a genuinely new
  compile error the logs don't mention, a claim that's gone stale).
- Grep for the symbols/files a doc claims exist ("implemented", "wired up", "fixed") and
  confirm they're actually *called from somewhere* — not just declared, not just present
  in one file while orphaned everywhere else.
- If a claim conflicts with what you observe directly, trust what you observe, and say
  so explicitly and specifically in the report (which doc, which claim) — surfacing a
  stale doc is one of this report's more useful outputs, not an aside to skip past.

### Step 2 — Find or ask for the reference point

"How close to done" is meaningless without a definition of done. Look for one before
asking:
- A branch, tag, or old commit representing an earlier working/prototype/"v1" version —
  `git branch -a`, `git log --all --oneline --grep=...`, or ask the user directly if
  they mention one in passing ("check out the X branch too").
- A design doc, spec, or README describing target scope.
- Issue/ticket numbering already used in the project's own logs — reuse their IDs in the
  punch list rather than inventing a new scheme; it keeps the report cross-referenceable
  with what the team already tracks.

If nothing points to a target and the user hasn't named one, ask directly what "done"
means here rather than assuming — an accurate scope beats a plausible-sounding guess.

### Step 3 — Write the report

Structure that's worked well, in this order:

1. **TL;DR** — the honest one-paragraph verdict up front, not buried at the end.
2. **Where we are in the project lifecycle** — the milestone timeline diagram (Step 4),
   plus 2–3 sentences of interpretation. Don't make the reader infer the point from the
   picture alone — say what the shape of the timeline means.
3. **What "done" looks like** — the reference point from Step 2, described concretely as
   a feature/behaviour list, not vibes.
4. **Current build/run status** — what you actually observed in Step 1, including any
   discrepancy from what the docs claimed, called out explicitly.
5. **Feature-by-feature comparison** — a table, reference vs. current, one row per
   checkable behaviour, so nothing is hand-waved as "mostly working."
6. **Prioritized, dependency-ordered punch list** — grouped into phases where each phase
   unblocks visibility into the next (fix compile errors before you can even see the
   wiring gaps, etc.); reuse existing ticket IDs where the project already has them, and
   clearly mark anything found fresh during this pass as new.
7. **Remaining-work breakdown diagram** (Step 4), mapped 1:1 onto the punch list's
   phases and item counts — never invent numbers the punch list itself doesn't back up.

Keep the tone matter-of-fact: state what's broken and why, plainly, but don't editorialize
about pace or blame. A long timeline dominated by rearchitecture usually reflects that
rebuilding underneath a working prototype is genuinely slower than writing the prototype
was — that's a fact about the work, not a criticism worth dwelling on.

### Step 4 — Diagrams (and verify them)

Two inline-SVG diagrams, both detailed in `assets/diagram-guide.md` (palette, layout
conventions, and a copy-paste template for each):

- **Milestone timeline** — plotted **proportionally by real date**, not evenly spaced.
  Pull dates from `git log --reverse --date=short --pretty='%ad %s'` plus whatever Step 1
  turned up. Proportional spacing is the whole point — it's what makes "two-week
  prototype, then a year-plus rebuild that's still mid-flight" visible at a glance
  instead of merely asserted in prose.
- **Remaining-work breakdown** — a segmented bar (or equivalent) whose segment widths are
  literally `phase item count / total item count` from the punch list — not a subjective
  "N% done" guess.

> **No blank lines inside `<svg>...</svg>`.** This is the single most common way this
> diagram type silently breaks: `marked` (CommonMark) ends a raw-HTML block at the first
> blank line found inside it, and everything after that point gets wrapped in a stray
> `<p>` tag — which corrupts SVG foreign-content parsing in the browser, and the whole
> diagram degrades to unstyled flowing text with no visible shapes at all (dots, bars,
> and connector lines vanish; only the text labels remain, run together). Keep every
> line from the opening `<svg ...>` to the closing `</svg>` blank-line-free. Comments
> (`<!-- -->`) are fine; blank lines are not.

**Verify before finishing** — the one place this skill does render something before
handing back, precisely because this diagram type is easy to get subtly wrong by hand:

```bash
<report-pdf skill directory>/render.sh <report.md> --png --height 3000
```

`Read` the resulting `…preview.png` and check, specifically:
- Both diagrams show actual **shapes** (dots, lines, colored bars) — not flat unstyled
  text with no graphics, which is exactly what the blank-line bug above produces.
- Labels don't collide with each other or overlap the axis.
- Multi-line label groups **read top-to-bottom in the intended order**. This is easy to
  get backwards when hand-stacking `<text>` elements at different y-coordinates — a
  smaller `y` renders higher up the page, so if a two-line phrase reads wrong, the fix is
  swapping the two elements' `y` values, not the text content.

Fix and re-render until clean, then delete the temporary `…preview.png` and stop — do
not generate the final PDF unless asked.

### Notes

- This skill has no PDF-rendering logic of its own — `report-pdf` owns the Markdown→
  HTML→PDF pipeline and stylesheet shared across every report skill in a project that has
  it installed. Run it (or ask the user to) only when a PDF is actually wanted.
- If the repo has no obvious reference point (Step 2) and the user doesn't want to name
  one, this can still run as a pure build/wiring status report (Steps 1, 3.1, 3.4, 3.6,
  minus the comparison table and feature list) — say so explicitly in the report rather
  than forcing a comparison that doesn't fit.
