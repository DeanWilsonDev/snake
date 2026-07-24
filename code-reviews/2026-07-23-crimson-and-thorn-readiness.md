# Crimson and Thorn Readiness — Snake's Engine vs. the Platformer's Requirements

**Date:** 23 July 2026
**Scope:** How far the engine currently being rebuilt under Snake is from what
`crimson-and-thorn` (Umbra Engine Milestone 2, a 2D narrative platformer) needs — sized
against that project's own design docs, not a guess.
**Sources:** This branch's source (`src/raylib-facade/`, `src/core/`, `src/engine/`),
verified directly rather than assumed; `~/development/projects/fearless-hq/Projects/crimson-and-thorn/`
— specifically `umbra-engine-feature-roadmap.md`, `game-design-document.md`,
`mechanics-design.md`, and `sprite-and-asset-pipeline.md`; the prior
`2026-07-23-engine-completion-status.md` report in this directory, whose Snake punch list
this one builds on rather than repeats.

---

## TL;DR

**Finishing Snake is the small, nearly-in-reach part of this picture.** The platformer's
own engine roadmap — written by the project itself, not inferred here — calls for six
systems, several of which do not exist **at all** in this codebase today, verified
directly against source rather than taken on the roadmap doc's word:

- `IRenderer`/`RaylibRendererFacade` expose exactly four methods —
  `BeginDrawing`/`EndDrawing`/`ClearBackground`/`DrawRectangle`. No texture loading, no
  sprites, no camera, no layers, no colour grading, no particles.
- There is no audio code anywhere in `src/` — no interface, no facade, not a stub. Zero.
- There is no `Camera` type anywhere in `src/`.
- `IUserInterface`/`RaylibUserInterfaceFacade` expose exactly one method —
  `DrawTextCentered`. No font control, no colour, no alignment options.
- There is no persistence/save system (the one `grep` hit for "persist" is an unrelated
  `SceneLifetime::Persistent` enum value).
- No gamepad support. No JSON library linked in `CMakeLists.txt` yet — needed for both
  scene serialisation and save data.

Against that, the platformer's own roadmap (`umbra-engine-feature-roadmap.md`) lists **21
distinct sub-features across those 6 systems**, several — a first-party level editor with
its own UI, a layered audio mixer, a particle system — that are each roughly the size of
an existing engine subsystem Snake spent months building. Snake's own remaining punch
list, by comparison, is **13 items**, all mechanical or wiring-level fixes to code that
already exists.

**The honest scope read:** finishing Snake closes out the current chapter. Getting the
engine to where Crimson and Thorn's own roadmap says it needs to be is not a
continuation of that chapter — it's a comparably-sized *next* one. This report tries to
size that next chapter using the platformer's own docs, but says plainly where it can't:
several of the roadmap's own line items are still marked "TBD during prototyping" in the
source document, so any timeline here is an order-of-magnitude estimate, not a plan.

---

## Where we are in the project lifecycle

The timeline below carries forward from the 23 July status report, extended in both
directions: back through the same verified `git log` milestones, and forward past
Snake's own estimated finish line into the platformer's requirements. Everything up to
and including "Snake feature-complete" is **date-proportional**, same as before. Past
that point the axis deliberately **breaks scale** — there's a real difference between "we
know the date" and "we're sizing a not-yet-built thing," and drawing both on the same
proportional axis would manufacture false precision the platformer's own docs don't
claim to have.

<svg viewBox="0 0 1200 480" xmlns="http://www.w3.org/2000/svg" width="100%" height="auto" role="img" aria-label="Timeline from Snake's project start through today, an estimated Snake completion date, then a scale break into an order-of-magnitude estimate for the platformer's engine build-out and production timeline">
  <style>
    .axis { stroke:#6b7280; stroke-width:2; }
    .conn { stroke:#4b5563; stroke-width:1; }
    .dot  { fill:#a78bfa; }
    .lbl-b { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:12px; fill:#d1d5db; font-weight:600; }
    .sub   { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:11px; fill:#9ca3af; }
    .tiny  { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:10px; fill:#9ca3af; }
  </style>
  <defs>
    <pattern id="hatch" width="8" height="8" patternTransform="rotate(45)" patternUnits="userSpaceOnUse">
      <line x1="0" y1="0" x2="0" y2="8" stroke="#7c6fa8" stroke-width="2"/>
    </pattern>
  </defs>
  <text x="360" y="22" text-anchor="middle" class="lbl-b" font-size="15">Verified history (proportional by date)</text>
  <text x="900" y="22" text-anchor="middle" class="lbl-b" font-size="15" fill="#c4b5fd">Order-of-magnitude estimate (not to scale)</text>
  <line x1="60" y1="340" x2="660" y2="340" class="axis"/>
  <circle cx="60" cy="340" r="6" fill="#9ca3af"/>
  <line x1="60" y1="346" x2="60" y2="368" class="conn"/>
  <text x="60" y="382" text-anchor="middle" class="lbl-b">Mar 2025</text>
  <text x="60" y="396" text-anchor="middle" class="sub">Project starts</text>
  <circle cx="76" cy="340" r="6" class="dot"/>
  <line x1="76" y1="334" x2="76" y2="312" class="conn"/>
  <text x="76" y="304" text-anchor="middle" class="lbl-b">Mar 2025</text>
  <text x="76" y="290" text-anchor="middle" class="sub">Working prototype</text>
  <text x="76" y="278" text-anchor="middle" class="sub">(simple-game)</text>
  <circle cx="238" cy="340" r="6" class="dot"/>
  <line x1="238" y1="334" x2="238" y2="312" class="conn"/>
  <text x="238" y="304" text-anchor="middle" class="lbl-b">Aug 2025</text>
  <text x="238" y="290" text-anchor="middle" class="sub">"Game running!</text>
  <text x="238" y="278" text-anchor="middle" class="sub">still a bit broken"</text>
  <line x1="553" y1="300" x2="594" y2="300" stroke="#6b7280" stroke-width="1.5"/>
  <line x1="553" y1="300" x2="553" y2="334" class="conn"/>
  <line x1="558" y1="300" x2="558" y2="334" class="conn"/>
  <line x1="594" y1="300" x2="594" y2="334" class="conn"/>
  <circle cx="553" cy="340" r="5" class="dot"/>
  <circle cx="558" cy="340" r="5" fill="#c4b5fd"/>
  <circle cx="594" cy="340" r="5" class="dot"/>
  <rect x="440" y="196" width="230" height="98" rx="8" fill="#1c1a24" stroke="#4b5563"/>
  <text x="555" y="216" text-anchor="middle" class="lbl-b">Jun–Jul 2026</text>
  <text x="555" y="234" text-anchor="middle" class="sub">Jun 1 — "green build, game</text>
  <text x="555" y="248" text-anchor="middle" class="sub">doesn't run yet"</text>
  <text x="555" y="264" text-anchor="middle" class="sub" fill="#c4b5fd">Jun 5 — Crimson &amp; Thorn scoped</text>
  <text x="555" y="278" text-anchor="middle" class="sub">Jul 8 — entity ownership landed;</text>
  <text x="555" y="290" text-anchor="middle" class="sub">menu state disabled (workaround)</text>
  <line x1="611" y1="334" x2="611" y2="128" stroke="#f87171" stroke-width="1.5" stroke-dasharray="3,3"/>
  <circle cx="611" cy="340" r="8" fill="#f87171"/>
  <circle cx="611" cy="340" r="13" fill="none" stroke="#f87171" stroke-width="1.5" opacity="0.5"/>
  <rect x="500" y="56" width="222" height="72" rx="8" fill="#2a1d1d" stroke="#f87171" stroke-width="1.5"/>
  <text x="611" y="78" text-anchor="middle" class="lbl-b" fill="#fca5a5" font-size="13">TODAY — 23 Jul 2026</text>
  <text x="611" y="96" text-anchor="middle" class="sub" fill="#fca5a5">Input rewrite mid-flight —</text>
  <text x="611" y="110" text-anchor="middle" class="sub" fill="#fca5a5">build does not compile</text>
  <line x1="611" y1="340" x2="660" y2="340" stroke="#4ade80" stroke-width="2" stroke-dasharray="5,5"/>
  <circle cx="660" cy="340" r="7" fill="none" stroke="#4ade80" stroke-width="2" stroke-dasharray="3,2"/>
  <line x1="660" y1="346" x2="660" y2="362" stroke="#4ade80" stroke-width="1" stroke-dasharray="3,2"/>
  <text x="660" y="376" text-anchor="middle" class="lbl-b" fill="#86efac">Est. — Snake</text>
  <text x="660" y="390" text-anchor="middle" class="sub" fill="#86efac">feature-complete</text>
  <text x="660" y="404" text-anchor="middle" class="tiny" fill="#86efac">(a few focused sessions)</text>
  <polygon points="666,320 678,330 666,340 678,350 666,360" fill="none" stroke="#6b7280" stroke-width="2"/>
  <text x="672" y="300" text-anchor="middle" class="tiny">scale break</text>
  <rect x="700" y="300" width="280" height="80" fill="url(#hatch)" opacity="0.35"/>
  <rect x="700" y="300" width="280" height="80" fill="none" stroke="#a78bfa" stroke-width="1.5" stroke-dasharray="6,4"/>
  <text x="840" y="255" text-anchor="middle" class="lbl-b" fill="#c4b5fd">C&amp;T engine build-out</text>
  <text x="840" y="270" text-anchor="middle" class="sub">21 sub-features, 6 systems —</text>
  <text x="840" y="284" text-anchor="middle" class="sub">several from zero lines of code</text>
  <text x="840" y="340" text-anchor="middle" font-size="26" fill="#a78bfa" font-weight="700">?</text>
  <text x="840" y="400" text-anchor="middle" class="tiny">For scale: Snake's rebuild-to-date took ~16 months</text>
  <text x="840" y="414" text-anchor="middle" class="tiny">to deliver ONE renderer method + no audio/camera/editor.</text>
  <text x="840" y="428" text-anchor="middle" class="tiny">This roadmap spans 6 independent systems at once.</text>
  <rect x="1000" y="310" width="140" height="60" fill="#1d2a24" stroke="#4ade80" stroke-width="1.5" stroke-dasharray="6,4"/>
  <text x="1070" y="332" text-anchor="middle" class="lbl-b" fill="#86efac">C&amp;T production</text>
  <text x="1070" y="348" text-anchor="middle" class="sub">~6 months, per their</text>
  <text x="1070" y="360" text-anchor="middle" class="sub">own GDD (1+3+1+1)</text>
  <polygon points="1140,325 1160,340 1140,355" fill="#4ade80"/>
  <text x="1150" y="400" text-anchor="middle" class="tiny" fill="#86efac">shippable</text>
  <line x1="980" y1="340" x2="1000" y2="340" stroke="#4ade80" stroke-width="2" stroke-dasharray="5,5"/>
  <text x="600" y="452" text-anchor="middle" class="tiny">Solid = happened. Dashed green = estimate. Hatched purple = order-of-magnitude only, not calendar-scaled.</text>
  <text x="600" y="466" text-anchor="middle" class="tiny">C&amp;T's own roadmap doc predates Snake's engine having a working build by five weeks (scoped Jun 5, "green build" Jun 1, still broken today).</text>
</svg>

Reading this left to right: the same story as the 23 July report up through "today," then
a genuinely new observation worth sitting with — **Crimson and Thorn's engine roadmap was
written on 5 June 2026, four days after the commit literally titled "green build, game
doesn't run yet," and seven weeks before today's still-broken build.** The platformer's
scope was defined before its own prerequisite had ever run successfully. That's not
necessarily a mistake — scoping the destination while still building the road is normal —
but it means none of the roadmap's "extend `RaylibRendererFacade`" instructions have yet
been tried against a version of that class attached to a working game loop.

---

## What "platformer-ready" requires

Pulled directly from `umbra-engine-feature-roadmap.md`'s own priority order and
sub-sections — not reinterpreted, just tabulated:

| # | System | Sub-features (roadmap's own breakdown) | Count |
|---|---|---|---|
| 1 | **Rendering pipeline** | Sprite/texture rendering · sprite animation · layered rendering (bg/mid/fg/UI) · camera system · colour/palette system · particle system | 6 |
| 2 | **Audio system** | Raylib audio facade (`IAudioBackend`) · layered audio mixer (simultaneous tracks, named layers, fades) · audio state system (state → config mapping) | 3 |
| 3 | **Scene editor ("Dawn")** | Architecture (ImGui-backed, its own module) · canvas/viewport · entity placement · layer management · properties panel · JSON serialisation · runtime scene loader | 7 |
| 4 | **Transitions** | Fade to/from black or arbitrary colour, triggered with a completion callback, rendered as a top-level overlay | 1 |
| 5 | **Persistence** | Key-value JSON store (`IPersistenceBackend`) · 3-slot save flow (per `menu-and-save-flow.md`) | 2 |
| 6 | **UI & text rendering** | Font loading/size/colour/alignment · menu & credits UI | 2 |
| | | **Total** | **21** |

Explicitly **not** counted above, because the project's own docs track them as separate,
independently-scoped workstreams rather than engine work:

- **Custom asset packer** (`sprite-and-asset-pipeline.md`) — the prototype phase
  deliberately uses a third-party tool (TexturePacker) precisely so packer development
  doesn't block engine/game work; the custom packer is explicitly "tracked as a separate
  project."
- **Actual game production** (art, levels, audio content, narrative implementation) — the
  6-month figure in the timeline diagram above is the platformer's own quoted
  pre-production → production → testing → release estimate, and it assumes a ready engine
  as a starting precondition, not something layered on top of engine dev time.

Also surfaced while checking this against the current build (not called out as its own
roadmap line item, but a prerequisite for #3 and #5 above): **no JSON library is linked
in `CMakeLists.txt` yet** (only `raylib` and `firefly`). Scene serialisation and the
save-slot store both need one — this is a small addition, but it's a dependency this repo
doesn't have today.

---

## Current engine capability — verified against source, not assumed

| Roadmap system | Verified current state |
|---|---|
| Sprite/texture rendering | **Nothing.** `IRenderer`/`RaylibRendererFacade` (`core/rendering/i-renderer.hpp`, `raylib-facade/renderer/raylib-renderer-facade.hpp`) expose only `BeginDrawing`/`EndDrawing`/`ClearBackground`/`DrawRectangle`. No `LoadTexture`, no sub-rect drawing, no tint. |
| Sprite animation | **Nothing.** No `AnimationComponent` anywhere in `src/`; nothing resembling frame-stepping exists. |
| Layered rendering | **Nothing.** `RenderComponent2DManager` renders whatever's registered with no ordering/layer concept — confirmed by reading the manager directly. |
| Camera system | **Nothing.** Zero matches for `Camera` anywhere in `src/`. |
| Colour/palette system | **Partial primitive only.** `ColorRGBA`/`ColorHex` exist (`core/color/`) as static colour values — no interpolation, no named palette states, no per-Chapter tint application. |
| Particle system | **Nothing.** |
| Audio (facade, mixer, state system) | **Nothing at all.** Zero matches for audio/sound/music anywhere in `src/` — not a stub, not an empty interface, nothing. |
| Scene editor ("Dawn") | **Nothing.** No editor module, no ImGui dependency in `CMakeLists.txt`, no serialisation format defined. |
| Scene loader (JSON → entities) | **Nothing.** `SceneManager` constructs scenes from code today; no data-driven loader. |
| Transitions | **Nothing.** No fade/overlay concept found. |
| Persistence | **Nothing.** The only "persist" hit in the codebase is `SceneLifetime::Persistent`, an unrelated scene-lifetime enum value — not a save system. |
| UI & text rendering | **One method.** `IUserInterface`/`RaylibUserInterfaceFacade` expose exactly `DrawTextCentered(text, position, fontSize)` — no font asset loading, no colour, no alignment control, no menu/credits scaffolding. |
| Input (relevant groundwork) | **In progress, and directly reusable.** The `Action`/`ActionSet`/`KeyMap` rework this week (see the 23 July status report) is the one piece of current work that isn't a detour — C&T's "run, jump, variable jump height" platforming needs exactly this kind of named, data-driven action system. It's currently mid-rewrite and doesn't compile, but the shape is the right shape. |
| Gamepad support | **Nothing.** Zero matches for gamepad/joystick anywhere in `src/`. |

Twelve of thirteen rows above read "nothing" or "one method." This isn't a criticism of
pace — Snake's engine wasn't built to have these things yet, it was built to run a snake
around a grid — it's the actual distance being measured here.

---

## Scope comparison

Two different things, deliberately **not drawn on the same proportional scale** — a Snake
compile-fix and "build a first-party level editor" are not comparable units of effort,
and a chart implying otherwise would be more misleading than useful.

<svg viewBox="0 0 1200 300" xmlns="http://www.w3.org/2000/svg" width="100%" height="auto" role="img" aria-label="A small reference bar showing Snake's 13 remaining items, next to a much larger breakdown of the platformer's 21 required engine sub-features across 6 systems">
  <style>
    .plbl { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:12.5px; fill:#111827; font-weight:700; }
    .pcnt { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:19px; fill:#111827; font-weight:700; }
    .cap  { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:12px; fill:#9ca3af; }
    .tiny { font-family: -apple-system, Helvetica, Arial, sans-serif; font-size:10.5px; fill:#9ca3af; }
  </style>
  <text x="140" y="24" text-anchor="middle" class="cap" font-weight="600" fill="#d1d5db">Reference — Snake's own remaining work</text>
  <rect x="60" y="34" width="160" height="34" fill="#a78bfa" opacity="0.55"/>
  <text x="140" y="56" text-anchor="middle" class="plbl">13 items (see 23 Jul report)</text>
  <path d="M 260 51 L 320 51" stroke="#6b7280" stroke-width="2" marker-end="url(#arr)"/>
  <defs>
    <marker id="arr" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#6b7280"/></marker>
  </defs>
  <text x="290" y="40" text-anchor="middle" class="tiny">different scale ▼</text>
  <text x="640" y="94" text-anchor="middle" class="cap" font-weight="600" fill="#d1d5db">Crimson &amp; Thorn's required engine work — 21 sub-features, 6 systems, priority-ordered left to right</text>
  <rect x="60" y="110" width="309" height="70" fill="#a78bfa"/>
  <text x="214" y="134" text-anchor="middle" class="plbl">1. Rendering pipeline</text>
  <text x="214" y="164" text-anchor="middle" class="pcnt">6</text>
  <rect x="369" y="110" width="154" height="70" fill="#60a5fa"/>
  <text x="446" y="134" text-anchor="middle" class="plbl">2. Audio</text>
  <text x="446" y="164" text-anchor="middle" class="pcnt">3</text>
  <rect x="523" y="110" width="360" height="70" fill="#fbbf24"/>
  <text x="703" y="134" text-anchor="middle" class="plbl">3. Scene editor "Dawn"</text>
  <text x="703" y="164" text-anchor="middle" class="pcnt">7</text>
  <rect x="883" y="110" width="51" height="70" fill="#2dd4bf"/>
  <text x="908" y="132" text-anchor="middle" class="plbl" font-size="9.5">4.</text>
  <text x="908" y="160" text-anchor="middle" class="pcnt" font-size="15">1</text>
  <rect x="934" y="110" width="103" height="70" fill="#f472b6"/>
  <text x="985" y="134" text-anchor="middle" class="plbl" font-size="11">5. Persistence</text>
  <text x="985" y="164" text-anchor="middle" class="pcnt" font-size="16">2</text>
  <rect x="1037" y="110" width="103" height="70" fill="#4ade80"/>
  <text x="1088" y="134" text-anchor="middle" class="plbl" font-size="11">6. UI/Text</text>
  <text x="1088" y="164" text-anchor="middle" class="pcnt" font-size="16">2</text>
  <line x1="369" y1="110" x2="369" y2="180" stroke="#111827" stroke-width="2"/>
  <line x1="523" y1="110" x2="523" y2="180" stroke="#111827" stroke-width="2"/>
  <line x1="883" y1="110" x2="883" y2="180" stroke="#111827" stroke-width="2"/>
  <line x1="934" y1="110" x2="934" y2="180" stroke="#111827" stroke-width="2"/>
  <line x1="1037" y1="110" x2="1037" y2="180" stroke="#111827" stroke-width="2"/>
  <circle cx="214" cy="200" r="6" fill="none" stroke="#f87171" stroke-width="2"/>
  <circle cx="446" cy="200" r="6" fill="#f87171"/>
  <circle cx="703" cy="200" r="6" fill="#f87171"/>
  <circle cx="908" cy="200" r="6" fill="#f87171"/>
  <circle cx="985" cy="200" r="6" fill="#f87171"/>
  <circle cx="1088" cy="200" r="6" fill="none" stroke="#f87171" stroke-width="2"/>
  <text x="600" y="222" text-anchor="middle" class="tiny">● = zero lines of code today   ○ = a bare stub exists (one method, no supporting behaviour)</text>
  <text x="600" y="252" text-anchor="middle" class="cap">Widths are proportional to sub-feature count within this set only — not comparable to the reference bar above.</text>
  <text x="600" y="270" text-anchor="middle" class="cap">A "sub-feature" here (e.g. "layered audio mixer") is individually far larger than a Snake punch-list item.</text>
</svg>

---

## What this means, plainly

- **Snake finishing is real and close.** The 13-item punch list from the 23 July report
  stands — mechanical compile fixes, then reconnecting logic that already exists. Nothing
  here changes that estimate.
- **The platformer is not "Snake plus a few features."** Two of its six required systems
  (rendering, scene editor) are individually larger than what exists in this engine
  today. Audio doesn't exist as a concept in this codebase at all. This is a second
  build-out, not a continuation of the current one.
- **The roadmap itself doesn't claim precision, and neither should this report.** Its own
  "Open Questions" table flags atlas strategy, particle complexity, and audio middleware
  as unresolved; `mechanics-design.md` and `sprite-and-asset-pipeline.md` each carry
  their own "to be resolved via prototyping" lists. Any date attached to "engine
  build-out" in the timeline above is a magnitude signal, not a commitment — which is
  exactly why it's drawn hatched and question-marked rather than as a dashed dot like
  Snake's estimate.
- **One piece of current work is genuinely dual-purpose.** The input-action rework
  happening in Snake right now (`Action`/`ActionSet`/`KeyMap`) is architecturally what
  C&T's platforming input needs too — named, data-driven actions rather than a hardcoded
  enum. Finishing it isn't a detour from the platformer goal, even though it's being
  built for Snake first.
- **The order of magnitude, stated once, plainly:** Snake's engine took roughly sixteen
  months to reach "green build, game doesn't run yet" while building one renderer method
  and no audio, camera, or editor. Crimson and Thorn's roadmap asks for six independent
  systems, several from zero, one of which (Dawn) is itself a small application in its
  own right. Treating the next phase as comparable in scale to the whole Snake rebuild
  to date — not a quick follow-on to it — is the honest way to size this.

---

*Not rendered to PDF. Run `/report-pdf` against this file when a shareable copy is
wanted.*
