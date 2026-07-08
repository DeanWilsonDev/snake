# Diagram authoring guide

Diagrams are **inline `<svg>`** written directly in the Markdown. `marked` passes raw HTML
through untouched, so the SVG lands in the HTML and Chrome renders it into the PDF. Keep
diagrams self-contained (no external images/fonts) — hardcode the palette hexes below so
colours survive the PDF conversion.

## Palette (matches the stylesheet)

| Role | Hex | Use |
|------|-----|-----|
| panel background | `#1b1728` | the `<svg>` background |
| panel border | `#362e4d` | the `<svg>` border |
| node fill | `#241f33` | normal boxes |
| node border | `#4b3f6b` | normal box stroke |
| text | `#e8e3f5` | node titles |
| muted text | `#a99fc4` | sub-labels, observer arrows/labels |
| accent (purple) | `#a78bfa` | ownership arrows |
| accent-soft | `#c4b5fd` | ownership arrow labels |
| danger (red) | `#fb7185` | unsafe / dangling arrows, danger node stroke, danger node fill `#2a1c26` |
| safe (green) | `#34d399` | single-owner arrows, good node stroke, good node fill `#1d2a24` |
| safe-soft | `#8ee7bf` | green labels / sub-text |

## Arrow / edge semantics (be consistent across a document)

| Meaning | Colour | Style |
|---------|--------|-------|
| owns (`unique_ptr` / by-value) | `#a78bfa` purple | solid |
| ownership consolidated into the single owner | `#34d399` green | solid |
| non-owning observer (raw `T*`/`T&`) | `#a99fc4` grey | `stroke-dasharray="5 4"` |
| unsafe: second claim / leak / dangling | `#fb7185` red | dashed (or solid for the "owns" leg of a double-owned object) |

## Layout tips

- Wrap in `<svg viewBox="0 0 760 H" style="width:100%;height:auto;max-width:760px;
  display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px">`.
  Pick `H` (height) to fit; content width 760 matches the A4 text column.
- Nodes: rounded `<rect rx="8">`, title in `ui-monospace` ~13px, sub-label in
  `-apple-system` sans ~10.5px `fill="#a99fc4"`.
- Give each `<svg>` its **own** `<marker>` defs with unique ids (marker ids are
  document-global — reusing an id across two diagrams collides).
- Route arrows to avoid crossing unrelated nodes. If a straight line would pass through a
  box, use a curved `<path>` (e.g. `d="M x,y C ..."`) that bows around it.
- Add a one-line legend under the diagram (in Markdown) using coloured `<span>`s.

## Copy-paste template

```html
<svg viewBox="0 0 760 260" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="own1"  markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="obs1"  markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a99fc4"/></marker>
    <marker id="bad1"  markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#fb7185"/></marker>
    <marker id="good1" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#34d399"/></marker>
  </defs>

  <!-- a node -->
  <g>
    <rect x="60" y="40" width="220" height="56" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="170" y="64" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">OwnerType</text>
    <text x="170" y="83" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">vector&lt;unique_ptr&lt;T&gt;&gt;</text>
  </g>

  <!-- a "good" (single-owner) node -->
  <g>
    <rect x="480" y="40" width="220" height="56" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="2"/>
    <text x="590" y="72" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">Owned</text>
  </g>

  <!-- ownership edge + label -->
  <line x1="280" y1="68" x2="480" y2="68" stroke="#34d399" stroke-width="1.8" marker-end="url(#good1)"/>
  <text x="380" y="60" text-anchor="middle" font-size="10" fill="#8ee7bf">owns</text>
</svg>
```

## Verify loop

After generating, always render a PNG (`render.sh doc.md --png`) and `Read` it — check that
arrowheads land on nodes, labels don't overlap boxes, and nothing overflows the panel. Fix
coordinates and regenerate before reporting done.
