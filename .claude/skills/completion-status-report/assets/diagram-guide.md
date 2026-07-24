# Diagram authoring guide

Two diagram types, both **inline `<svg>`** written directly in the Markdown. `marked`
passes raw HTML through untouched, so the SVG lands in the HTML and Chrome renders it
into the PDF/PNG. Keep diagrams self-contained (hardcoded hex colours, system fonts) —
no external images or webfonts, they won't survive the render.

> **No blank lines inside `<svg>...</svg>`.** CommonMark (what `marked` implements) ends
> a raw-HTML block at the first blank line. A blank line anywhere between `<svg ...>` and
> `</svg>` splits the block — everything after it gets wrapped in a stray `<p>` tag
> instead of staying part of the SVG, which corrupts foreign-content parsing in the
> browser and makes the *entire* diagram fall back to flat, unstyled text with no visible
> shapes (not just the part after the blank line — the damage isn't localized). This is
> the single most common failure mode for this diagram type. Comments (`<!-- -->`) are
> fine; blank lines are not. If a diagram renders as a wall of text with no dots/bars
> when you preview it, this is the first thing to check — search the block for a blank
> line.

## Palette (dark-mode report theme)

| Role | Hex | Use |
|------|-----|-----|
| axis / structural line | `#6b7280` | the main timeline axis, arrowhead |
| connector line | `#4b5563` | thin leader from a dot up/down to its label |
| milestone dot (shipped/landed) | `#a78bfa` | solid circle, purple accent |
| milestone dot (project start) | `#9ca3af` | grey — start point isn't a "landing," so it's visually distinct |
| "today" / current-state marker | `#f87171` | red — filled circle, ring, dashed leader, callout box border |
| projected / estimated marker | `#4ade80` | green — **always paired with a dashed stroke**, never solid; solid would imply it already happened |
| label text (heading weight) | `#d1d5db` | bold sub-labels (dates, phase names) |
| label text (muted) | `#9ca3af` | descriptive sub-text under a heading label |
| phase-bar text | `#111827` | dark text sits directly on the coloured bar segments below, not on the page background |

### Remaining-work bar segment colours (in phase order — reuse this exact progression)

| Phase | Hex | Rationale |
|---|---|---|
| 1st phase (mechanical/build fixes) | `#f87171` red | closest to "broken," most urgent |
| 2nd phase | `#fbbf24` amber | |
| 3rd phase | `#60a5fa` blue | |
| last phase (closest to done) | `#4ade80` green | ties to the same green used for the "done" marker on the timeline — visually links the two diagrams as one story |

If there are more or fewer than four phases, interpolate/extend this progression
(red → amber → blue → green) rather than picking arbitrary colours — the reader should
be able to tell "further along" from hue alone without reading labels.

## Layout: milestone timeline

- `<svg viewBox="0 0 1100 460" width="100%" height="auto">` — width 1100 comfortably
  spans a rendered PDF page; height depends on how many stacked label rows you need
  above/below the axis (460 fit ~9 milestones with 2-row staggering each side).
- Draw the axis as a single horizontal `<line>` around `y=320` (leaving room for labels
  above and below), with a small `<polygon>` arrowhead at the right end.
- **Compute x-positions proportionally by real date**, not evenly spaced:
  `x = marginLeft + (dayOffset / totalDays) * plotWidth`, where `dayOffset` is days since
  the earliest milestone and `totalDays` includes some extra room for a projected/
  estimated end point past "today." This is the entire point of the diagram — a project
  dominated by a long rearchitecture will visibly bunch its early milestones and stretch
  out near the present, which is the story worth telling.
- **Stagger labels above and below the axis**, and within each side use two height rows
  ("near" the axis and "far" from it) in alternation, so adjacent milestones that fall
  close together on the date axis don't collide even though their dots are only a few
  pixels apart. Connect each dot to its label with a short `<line>` "leader."
- For a multi-line label (a heading line plus 1–2 lines of description), **the topmost
  line on the page must be the first line of the sentence** — since smaller `y` renders
  higher, that means the first line of text needs the *smallest* `y` value among that
  group. It's easy to instead just append `<text>` elements in writing order without
  checking which one ends up visually on top; always sanity-check this against the PNG
  preview (see SKILL.md Step 4) — a two-line phrase rendering back-to-front is the most
  common polish bug in this diagram, easy to miss without actually looking.
- Give "today" (or whatever the current-state marker is) its own prominent callout —
  larger dot, a ring around it, a bordered box set apart from the regular label rows —
  since it's the single most important data point on the chart and shouldn't have to
  compete visually with the historical milestones.
- Mark any projected/future point with a **dashed** connector and dashed dot outline
  (never solid), and a caption stating outright that it's an estimate, not a committed
  date.
- Close with a one-line caption under the diagram explaining the solid-vs-dashed
  convention, so the diagram is self-documenting without the reader needing this guide.

## Layout: remaining-work breakdown bar

- `<svg viewBox="0 0 1100 170" width="100%" height="auto">` is enough for a single
  segmented bar with labels above/below and a caption line.
- One `<rect>` per phase, x-widths computed as `phaseItemCount / totalItemCount *
  barWidth`, laid edge-to-edge (no gaps) starting at a shared `x`. Add a thin dark
  `<line>` divider between segments for a clean seam.
- Label each segment with the phase name and its item count, centered in the segment —
  drop to a smaller two-line label (`Phase N` / `short name`) for narrow segments so text
  doesn't overflow the rect.
- Bookend the bar with a "we are here" marker at the left edge and a "target/parity"
  marker at the right edge, in the timeline's red/green colours, so the two diagrams read
  as one continuous story (timeline ends where this bar begins).
- Caption underneath stating the total item count and, if true, that segment widths are
  proportional to item count rather than calendar time or subjective effort — say this
  explicitly, since a reader's first assumption about a bar chart is usually "duration."

## Copy-paste template — timeline (minimal skeleton, extend per the layout notes above)

```html
<svg viewBox="0 0 1100 460" xmlns="http://www.w3.org/2000/svg" width="100%" height="auto" role="img" aria-label="Describe the timeline's story in one sentence here">
  <style>
    .axis { stroke:#6b7280; stroke-width:2; }
    .conn { stroke:#4b5563; stroke-width:1; }
    .dot  { fill:#a78bfa; }
    .lbl-b { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:12px; fill:#d1d5db; font-weight:600; }
    .sub   { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:11px; fill:#9ca3af; }
  </style>
  <line x1="60" y1="320" x2="1040" y2="320" class="axis"/>
  <polygon points="1040,320 1030,314 1030,326" fill="#6b7280"/>
  <!-- one milestone, above the axis: dot, leader, then label lines with the FIRST sentence line at the SMALLEST y -->
  <circle cx="200" cy="320" r="6" class="dot"/>
  <line x1="200" y1="314" x2="200" y2="298" class="conn"/>
  <text x="200" y="276" text-anchor="middle" class="sub">First line of the description</text>
  <text x="200" y="288" text-anchor="middle" class="sub">second line, closer to the date</text>
  <text x="200" y="300" text-anchor="middle" class="lbl-b">Date</text>
  <!-- "today" callout: bigger, its own box, set apart -->
  <line x1="935" y1="314" x2="935" y2="118" stroke="#f87171" stroke-width="1.5" stroke-dasharray="3,3"/>
  <circle cx="935" cy="320" r="8" fill="#f87171"/>
  <circle cx="935" cy="320" r="13" fill="none" stroke="#f87171" stroke-width="1.5" opacity="0.5"/>
  <rect x="800" y="46" width="270" height="60" rx="8" fill="#2a1d1d" stroke="#f87171" stroke-width="1.5"/>
  <text x="935" y="68" text-anchor="middle" class="lbl-b" fill="#fca5a5" font-size="13">TODAY — state it plainly</text>
  <text x="935" y="86" text-anchor="middle" class="sub" fill="#fca5a5">one line of context</text>
  <!-- projected/estimated end point: dashed, green, explicitly labeled as an estimate -->
  <line x1="935" y1="320" x2="1040" y2="320" stroke="#4ade80" stroke-width="2" stroke-dasharray="5,5"/>
  <circle cx="1040" cy="320" r="7" fill="none" stroke="#4ade80" stroke-width="2" stroke-dasharray="3,2"/>
  <text x="1040" y="356" text-anchor="end" class="lbl-b" fill="#86efac">Est. — not a committed date</text>
  <text x="550" y="446" text-anchor="middle" class="sub">Solid = landed. Dashed green = estimate, not a committed date.</text>
</svg>
```

## Copy-paste template — remaining-work bar

```html
<svg viewBox="0 0 1100 170" xmlns="http://www.w3.org/2000/svg" width="100%" height="auto" role="img" aria-label="Describe the remaining-work breakdown in one sentence here">
  <style>
    .plbl { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:13px; fill:#111827; font-weight:700; }
    .pcnt { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:20px; fill:#111827; font-weight:700; }
    .cap  { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:12px; fill:#9ca3af; }
  </style>
  <!-- widths below sum to 980 and must equal (phase count / total count) * 980 each -->
  <rect x="60" y="30" width="452" height="60" fill="#f87171"/>
  <text x="286" y="55" text-anchor="middle" class="plbl">Phase 1 — short name</text>
  <text x="286" y="80" text-anchor="middle" class="pcnt">6</text>
  <rect x="512" y="30" width="226" height="60" fill="#fbbf24"/>
  <text x="625" y="55" text-anchor="middle" class="plbl">Phase 2 — short name</text>
  <text x="625" y="80" text-anchor="middle" class="pcnt">3</text>
  <rect x="738" y="30" width="151" height="60" fill="#60a5fa"/>
  <text x="813" y="55" text-anchor="middle" class="plbl" font-size="11">Phase 3</text>
  <text x="813" y="80" text-anchor="middle" class="pcnt" font-size="17">2</text>
  <rect x="889" y="30" width="151" height="60" fill="#4ade80"/>
  <text x="964" y="55" text-anchor="middle" class="plbl" font-size="11">Phase 4</text>
  <text x="964" y="80" text-anchor="middle" class="pcnt" font-size="17">2</text>
  <line x1="512" y1="30" x2="512" y2="90" stroke="#111827" stroke-width="2"/>
  <line x1="738" y1="30" x2="738" y2="90" stroke="#111827" stroke-width="2"/>
  <line x1="889" y1="30" x2="889" y2="90" stroke="#111827" stroke-width="2"/>
  <text x="60" y="112" text-anchor="start" class="cap" font-weight="600" fill="#fca5a5">◀ we are here</text>
  <text x="1040" y="112" text-anchor="end" class="cap" font-weight="600" fill="#86efac">done ▶</text>
  <text x="550" y="145" text-anchor="middle" class="cap">N concrete, already-scoped tasks remain — widths proportional to item count, not calendar time.</text>
</svg>
```

## Verify loop

After generating both diagrams, always render a PNG (`render.sh report.md --png
--height 3000`, from the `report-pdf` skill) and `Read` it back — see SKILL.md Step 4 for
exactly what to check. Fix coordinates and regenerate before reporting done; don't ship a
diagram you haven't actually looked at.
