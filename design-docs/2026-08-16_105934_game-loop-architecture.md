# Game Loop Timing Architecture

**Project:** Umbra Engine
**Date:** 2026-08-16
**Scope:** Fixed-timestep game loop, decoupled rendering, render interpolation

---

## Executive Summary

Umbra's current game loop couples simulation and rendering to the same frame cadence and feeds raw `deltaTime` directly into `OnUpdate`. This produces framerate-dependent simulation — physics, movement, and collision results differ between machines and under frame spikes. The fix is a fixed-timestep accumulator loop that ticks simulation at exactly 1/60 s regardless of render cadence, with interpolated rendering to keep visuals smooth. This document covers the loop redesign, the render component changes needed to support interpolation, what stays the same, and the recommended migration order.

---

## Problem: Current Loop

The existing loop in `Application::Run()` measures raw elapsed time each frame and passes it directly into `OnUpdate`, which propagates it through `SystemManager` and `SceneManager` to all game systems.

```
while (!window->ShouldClose()) {
    deltaTime = currentTime - lastTime;   // raw, noisy
    OnUpdate(deltaTime);                  // simulation sees variable step
    OnDebugUpdate();
    OnRender(renderer);                   // coupled to simulation tick
    renderer->EndDrawing();
}
```

**Consequences:**

- Simulation results are framerate-dependent. Movement with friction, acceleration, or collision detection produces different outcomes at 30 fps vs 60 fps vs 144 fps.
- A single slow frame (OS event, shader compile, asset load) causes a large `deltaTime`, which causes objects to tunnel through geometry or overshoot targets.
- No spiral-of-doom protection — a frame that takes longer than one tick triggers more updates, which makes the next frame slower, which triggers more updates.
- Determinism is impossible. Input replays and frame-accurate debugging cannot be built on a variable-step loop.

---

## Solution: Fixed Timestep with Decoupled Rendering

Simulation runs at a fixed rate of 1/60 s. Rendering runs as fast as the hardware allows, interpolating between the last two simulation states using the accumulator remainder as an alpha value.

### Loop Structure

```cpp
static constexpr float FIXED_TIMESTEP          = 1.0f / 60.0f;
static constexpr float MAX_ACCUMULATED_TIME    = 8.0f / 60.0f; // spiral cap (~7.5 fps)
static constexpr float TIME_SNAP_THRESHOLD     = 0.0002f;       // vsync jitter tolerance

float accumulator = 0.0f;

while (!window->ShouldClose()) {
    float rawDeltaTime     = MeasureElapsedTime();
    float clampedDeltaTime = std::min(rawDeltaTime, MAX_ACCUMULATED_TIME);

    // Snap to exact fixed step when close — eliminates vsync jitter drift
    if (std::abs(clampedDeltaTime - FIXED_TIMESTEP) < TIME_SNAP_THRESHOLD) {
        clampedDeltaTime = FIXED_TIMESTEP;
    }

    accumulator += clampedDeltaTime;

    OnPollInput();                          // every real frame, not every tick

    while (accumulator >= FIXED_TIMESTEP) {
        renderComponentManager->SnapshotAllPreviousStates();
        OnFixedUpdate(FIXED_TIMESTEP);      // always exactly 1/60 s
        accumulator -= FIXED_TIMESTEP;
    }

    const float interpolationAlpha = accumulator / FIXED_TIMESTEP;

    OnDebugUpdate();
    OnRender(renderer, interpolationAlpha);
    OnDebugRender();
    renderer->EndDrawing();
}
```

### Time Snapping

When vsync is active, frame times cluster very close to 1/60 s but never land exactly on it due to OS timer precision. Without snapping, the accumulator drifts, causing periodic double-updates (stutter). Snapping clamps measured delta to exactly `FIXED_TIMESTEP` when within `0.0002 s` — close enough to mean "this was a vsync frame." When vsync is off or the frame genuinely took longer, the raw value falls outside the threshold and passes through unchanged.

### Spiral-of-Doom Cap

If a frame takes longer than `MAX_ACCUMULATED_TIME` (e.g. a blocking load), the accumulator is capped before entering the fixed-tick loop. The simulation falls behind real time rather than attempting to compensate with a burst of updates that would make subsequent frames even slower.

---

## Data Flow Diagrams

### Current Loop (Coupled)

<svg viewBox="0 0 760 200" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#17171a;border:1px solid #3a3a3a;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="arr-a" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#fb7185"/></marker>
  </defs>
  <g>
    <rect x="20" y="70" width="140" height="56" rx="8" fill="#2a1c26" stroke="#fb7185"/>
    <text x="90" y="94" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">MeasureTime</text>
    <text x="90" y="112" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">raw deltaTime</text>
  </g>
  <line x1="160" y1="98" x2="200" y2="98" stroke="#fb7185" stroke-width="1.8" marker-end="url(#arr-a)"/>
  <g>
    <rect x="200" y="70" width="140" height="56" rx="8" fill="#2a1c26" stroke="#fb7185"/>
    <text x="270" y="94" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">OnUpdate</text>
    <text x="270" y="112" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">variable step</text>
  </g>
  <line x1="340" y1="98" x2="380" y2="98" stroke="#fb7185" stroke-width="1.8" marker-end="url(#arr-a)"/>
  <g>
    <rect x="380" y="70" width="140" height="56" rx="8" fill="#2a1c26" stroke="#fb7185"/>
    <text x="450" y="94" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">OnRender</text>
    <text x="450" y="112" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">coupled to sim</text>
  </g>
  <text x="380" y="170" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="11" fill="#fb7185">⚠ simulation and render on same variable tick — framerate-dependent results</text>
</svg>

### Proposed Loop (Decoupled)

<svg viewBox="0 0 760 320" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#17171a;border:1px solid #3a3a3a;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="arr-b" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="arr-c" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#34d399"/></marker>
    <marker id="arr-d" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a3a3a8"/></marker>
  </defs>
  <g>
    <rect x="20" y="30" width="160" height="56" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="100" y="54" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">MeasureTime</text>
    <text x="100" y="72" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">snap + clamp</text>
  </g>
  <line x1="180" y1="58" x2="220" y2="58" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#arr-b)"/>
  <g>
    <rect x="220" y="30" width="160" height="56" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="300" y="54" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">Accumulator</text>
    <text x="300" y="72" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">+= clampedDelta</text>
  </g>
  <line x1="300" y1="86" x2="300" y2="126" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#arr-b)"/>
  <g>
    <rect x="180" y="126" width="240" height="56" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="2"/>
    <text x="300" y="150" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">OnFixedUpdate</text>
    <text x="300" y="168" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#8ee7bf">always 1/60 s — deterministic</text>
  </g>
  <line x1="420" y1="154" x2="500" y2="154" stroke="#a3a3a8" stroke-width="1.5" stroke-dasharray="5 4" marker-end="url(#arr-d)"/>
  <g>
    <rect x="500" y="126" width="200" height="56" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="600" y="150" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">SnapshotStates</text>
    <text x="600" y="168" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">prev ← current</text>
  </g>
  <line x1="300" y1="182" x2="300" y2="222" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#arr-b)"/>
  <g>
    <rect x="180" y="222" width="240" height="56" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="300" y="246" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">OnRender</text>
    <text x="300" y="264" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">interpolationAlpha = acc / step</text>
  </g>
  <line x1="500" y1="182" x2="430" y2="230" stroke="#a3a3a8" stroke-width="1.5" stroke-dasharray="5 4" marker-end="url(#arr-d)"/>
  <text x="380" y="300" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="11" fill="#34d399">✓ simulation fixed — render decoupled and interpolated</text>
</svg>

<span style="font-size:11px;color:#a3a3a8">— purple solid: data flow &nbsp;|&nbsp; grey dashed: read/observe &nbsp;|&nbsp; green border: fixed-rate / deterministic</span>

---

## Render Component Changes

### What Needs to Change

`RenderComponent2DManager::OnRender` currently calls `component->Render(renderer)` with no timing context. To interpolate, each component needs to know how far between its last two simulation states it is.

**`IRenderComponentManager` — two new methods:**

```cpp
virtual void SnapshotAllPreviousStates() = 0;
virtual void OnRender(const IRenderer& renderer, float interpolationAlpha) const = 0;
```

**`IRenderComponent2D` — snapshot contract:**

```cpp
class IRenderComponent2D : public IRenderComponent {
public:
    virtual void SnapshotPreviousState() = 0;
    virtual void Render(const IRenderer& renderer, float interpolationAlpha) const = 0;
};
```

**Concrete component — dual transform:**

```cpp
struct Transform2D {
    Vector2 position;
    float   rotation;
    Vector2 scale;
};

class SpriteRenderComponent2D : public IRenderComponent2D {
    Transform2D previousTransform;
    Transform2D currentTransform;
public:
    void SnapshotPreviousState() override {
        previousTransform = currentTransform;
    }
    void SetTransform(const Transform2D& transform) {
        currentTransform = transform;
    }
    void Render(const IRenderer& renderer, float interpolationAlpha) const override {
        Vector2 interpolatedPosition = Vector2Lerp(
            previousTransform.position,
            currentTransform.position,
            interpolationAlpha
        );
        float interpolatedRotation = std::lerp(
            previousTransform.rotation,
            currentTransform.rotation,
            interpolationAlpha
        );
        renderer.DrawSprite(texture, interpolatedPosition, interpolatedRotation, currentTransform.scale);
    }
};
```

### Ownership and Data Flow

<svg viewBox="0 0 760 260" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#17171a;border:1px solid #3a3a3a;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="arr-e" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="arr-f" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a3a3a8"/></marker>
    <marker id="arr-g" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#34d399"/></marker>
  </defs>
  <g>
    <rect x="20" y="30" width="200" height="56" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="120" y="54" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">Application</text>
    <text x="120" y="72" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">owns loop + managers</text>
  </g>
  <line x1="220" y1="58" x2="270" y2="58" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#arr-e)"/>
  <g>
    <rect x="270" y="30" width="220" height="56" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="380" y="54" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">RenderComponent2DManager</text>
    <text x="380" y="72" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">vector&lt;IRenderComponent2D*&gt; (non-owning)</text>
  </g>
  <line x1="380" y1="86" x2="380" y2="130" stroke="#a3a3a8" stroke-width="1.5" stroke-dasharray="5 4" marker-end="url(#arr-f)"/>
  <g>
    <rect x="270" y="130" width="220" height="56" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="2"/>
    <text x="380" y="154" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">SpriteRenderComponent2D</text>
    <text x="380" y="172" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#8ee7bf">previousTransform + currentTransform</text>
  </g>
  <line x1="120" y1="86" x2="120" y2="200" stroke="#a3a3a8" stroke-width="1.5" stroke-dasharray="5 4" marker-end="url(#arr-f)"/>
  <g>
    <rect x="20" y="200" width="200" height="44" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="120" y="218" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">OnFixedUpdate</text>
    <text x="120" y="236" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">calls SetTransform each tick</text>
  </g>
  <line x1="220" y1="222" x2="270" y2="175" stroke="#34d399" stroke-width="1.8" marker-end="url(#arr-g)"/>
  <text x="600" y="230" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">manager holds raw pointers</text>
  <text x="600" y="246" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">entities own their components</text>
</svg>

<span style="font-size:11px;color:#a3a3a8">— purple solid: ownership &nbsp;|&nbsp; grey dashed: non-owning observer &nbsp;|&nbsp; green solid: writes simulation result &nbsp;|&nbsp; green border: dual-state component</span>

---

## What Does Not Change

| Concern | Status | Notes |
|---|---|---|
| `IWindow` / `IRenderer` interfaces | Unchanged | Rendering call sites gain `alpha` param only |
| `InputSystem` poll path | Minor split | `PollInput` separated from action application |
| `EventBus` | Unchanged | Events fired inside `OnFixedUpdate` as before |
| `SceneManager` / `EntityManager` | Unchanged internally | Called via `OnFixedUpdate` instead of `OnUpdate` |
| `GameSystemManager` | Unchanged internally | Same — receives fixed step |
| `DebugHUD` / `OnDebugUpdate` | Unchanged | Runs once per real frame, reads live state |
| `SystemManager` signature | `OnUpdate(float)` → `OnFixedUpdate(float)` | Rename only — same float param |
| Raylib/SDL3 facade layer | Unchanged | Timing lives above the facade |

---

## Input: Poll vs Apply

Input polling must happen every real frame to avoid missing events between ticks. Input *application* (moving a character, consuming an action event) must happen inside `OnFixedUpdate` to stay deterministic.

Current `InputSystem::OnUpdate` likely does both. The split is:

```
OnPollInput()      — called once per real frame, before accumulator loop
                     reads hardware, updates ActionSet, fires raw input events

OnFixedUpdate()    — systems consume ActionSet state / events
                     movement and game logic respond here
```

No new interface is needed — `InputSystem` gains a `PollInput()` method and its `OnUpdate` (now `OnFixedUpdate`) only applies already-polled state.

---

## What to Not Interpolate

Not everything needs or should be interpolated. Apply the rule: **if it doesn't move smoothly between frames, interpolating it produces wrong results.**

| State | Interpolate? | Reason |
|---|---|---|
| Entity position | Yes | Primary use case |
| Entity rotation | Yes, with care | Lerp breaks at > 180° delta — use `slerp` or clamp step size |
| Entity scale | No | Rarely changes frame-to-frame visually |
| Sprite frame index | No | Discrete — lerping an int makes no sense |
| Animation state machine | No | State transitions are instantaneous |
| Particle spawn events | No | 1-tick delay unnoticeable |
| UI element position | Depends | Static UI: no. Animated UI that tracks world: yes |
| Audio triggers | No | Fire in `OnFixedUpdate`, not render path |

---

## Migration Order

1. **Restructure `Application::Run()`** — introduce accumulator, time snap, spiral cap. `OnUpdate` becomes `OnFixedUpdate`. All existing systems keep working; only the call site changes.
2. **Split `InputSystem`** — add `PollInput()`, move action application to `OnFixedUpdate`. Verify no input events are dropped.
3. **Add `SnapshotAllPreviousStates()` to `IRenderComponentManager`** — stub returns in the default implementation so nothing breaks.
4. **Add `SnapshotPreviousState()` to `IRenderComponent2D`** — stub initially copies `currentTransform` to `previousTransform` with no actual interpolation yet.
5. **Pass `interpolationAlpha` through `OnRender`** — plumb the parameter down to `RenderComponent2DManager::OnRender` and each component's `Render`.
6. **Implement interpolation in concrete render components** — activate `Vector2Lerp` / `std::lerp` in `SpriteRenderComponent2D::Render`. At this point interpolation is live.
7. **Validate** — test at locked 60 fps (should be identical to current behaviour), then at uncapped frame rate (should be smooth), then with an artificial slow frame injected (should not spiral).

Each step is independently shippable. Steps 1–2 improve correctness immediately even without interpolation. Steps 3–6 are additive.

---

## Summary

| Property | Before | After |
|---|---|---|
| Simulation timestep | Variable (raw `deltaTime`) | Fixed (always `1/60 s`) |
| Render rate | Coupled to simulation | Decoupled, runs at hardware rate |
| Frame smoothness | Dependent on vsync | Interpolated — smooth at any rate |
| Determinism | None | Full within fixed-tick boundary |
| Slow frame behaviour | Spiral of doom | Capped — simulation falls behind, does not freeze |
| Vsync jitter | Causes periodic double-updates | Eliminated by time snapping |
| Implementation cost | — | Loop: trivial. Interpolation: per-component, one-time |
