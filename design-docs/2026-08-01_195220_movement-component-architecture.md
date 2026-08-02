# Movement Component Architecture

## Executive summary

Snake's movement logic currently lives directly on `SnakeSegment`/`SnakeHead` — each
segment carries its own `direction`, `pendingDirection`, `moveTimer`, and `moveInterval`
fields, and `SnakeHead` binds input directly to itself. This makes movement a
Snake-specific, non-reusable trait: nothing else in the engine could "just become
movable" without duplicating that state and logic onto its own class.

The proposed fix has three pieces, in order of foundational-ness:

1. **Components gain the ability to tick.** Today `IComponent` has no per-frame hook at
   all — `Entity` is the only thing the engine calls `Update()` on. Render and Input each
   worked around this with their own one-off manager (`RenderComponent2DManager`,
   `ActionRouter`), rather than a general capability.
2. **A generic `MovementComponent`** owns direction/timing state and its own input
   binding, and can be attached to *any* entity — the snake's head, or (as a test of the
   design) the apple.
3. **The snake-specific "body follows the head" behavior** stays out of
   `MovementComponent` entirely and instead reacts to a **data-carrying event**
   (`MovementSteppedEvent`) that `MovementComponent` publishes on the existing event bus
   — keeping the generic component generic, and the snake-specific behavior isolated to
   `SnakeBodyComponent`.

This document lays out the current state, the proposed shape, and a concrete adoption
order for getting there.

## Current state

`SnakeSegment` (and by inheritance `SnakeHead`) currently owns all of its own movement
state directly, and `SnakeHead` wires player input straight into itself. Nothing about
this is reusable — a second movable entity (the apple, an enemy, anything) would need
the same fields and the same `Step()` logic copy-pasted onto it.

<svg viewBox="0 0 760 300" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#17171a;border:1px solid #3a3a3a;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="own1" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="obs1" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a3a3a8"/></marker>
  </defs>
  <g>
    <rect x="270" y="20" width="260" height="66" rx="8" fill="#2a1c26" stroke="#fb7185" stroke-width="2"/>
    <text x="400" y="44" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e8ea" font-weight="600">SnakeHead : SnakeSegment</text>
    <text x="400" y="61" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#fca5b1">direction, pendingDirection, moveTimer,</text>
    <text x="400" y="75" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#fca5b1">moveInterval, Step(), SetDirection() — owned here</text>
  </g>
  <g>
    <rect x="20" y="150" width="150" height="50" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="95" y="180" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea">TransformComponent2D</text>
  </g>
  <g>
    <rect x="190" y="150" width="150" height="50" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="265" y="180" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea">ColliderComponent2D</text>
  </g>
  <g>
    <rect x="360" y="150" width="150" height="50" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="435" y="180" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea">RenderComponent2D</text>
  </g>
  <g>
    <rect x="530" y="150" width="150" height="50" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="605" y="180" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea">InputComponent</text>
  </g>
  <line x1="330" y1="86" x2="95" y2="150" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own1)"/>
  <line x1="360" y1="86" x2="265" y2="150" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own1)"/>
  <line x1="440" y1="86" x2="435" y2="150" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own1)"/>
  <line x1="470" y1="86" x2="605" y2="150" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own1)"/>
  <g>
    <rect x="230" y="240" width="340" height="46" rx="8" fill="#242424" stroke="#4a4a4e" stroke-dasharray="5 4"/>
    <text x="400" y="260" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#a3a3a8">IComponent</text>
    <text x="400" y="276" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a3a3a8">no OnUpdate() — components cannot tick themselves</text>
  </g>
  <line x1="95" y1="200" x2="330" y2="240" stroke="#a3a3a8" stroke-width="1.4" stroke-dasharray="5 4" marker-end="url(#obs1)"/>
  <line x1="265" y1="200" x2="370" y2="240" stroke="#a3a3a8" stroke-width="1.4" stroke-dasharray="5 4" marker-end="url(#obs1)"/>
  <line x1="435" y1="200" x2="420" y2="240" stroke="#a3a3a8" stroke-width="1.4" stroke-dasharray="5 4" marker-end="url(#obs1)"/>
  <line x1="605" y1="200" x2="470" y2="240" stroke="#a3a3a8" stroke-width="1.4" stroke-dasharray="5 4" marker-end="url(#obs1)"/>
</svg>

<span style="color:#a78bfa">■</span> owns &nbsp;&nbsp; <span style="color:#a3a3a8">┄</span> extends (no per-frame hook) &nbsp;&nbsp; <span style="color:#fb7185">■</span> movement state trapped on the entity, duplicated per-segment

Render works around the missing hook with its own manager walking a registered list
(`RenderComponent2DManager::OnRender`); Input works around it with `ActionRouter::Update`
polling bound axes. Both are one-off, component-specific answers to the same missing
piece: **components have no generic way to run code once a frame.**

## Proposed architecture

### 1. `IComponent` gains `OnUpdate(float deltaTime)`

Matches the pattern `IEntity`/`ISystem` already use: a virtual method with an empty
default body (`virtual void OnUpdate(float) {}`), not pure — so existing components
(`TransformComponent2D`, `ColliderComponent2D`, `RenderComponent2D`, `InputComponent`)
need no changes at all, and only components that actually need a tick (like the new
`MovementComponent`) override it. `Entity::Update()` iterates its own `components` map
and calls `OnUpdate(deltaTime)` on each — one small, generic loop, replacing the need for
any future one-off component manager.

Deliberately **out of scope for this pass**: giving components the rest of the entity
lifecycle (`BeginPlay`/`OnActivate`/`OnRegistration`). Nothing needs it yet, and it's an
easy follow-up if a real need shows up later.

### 2. `MovementComponent` — generic, reusable

Owns everything that used to live on `SnakeSegment`: `direction`, `pendingDirection`,
`moveTimer`, `moveInterval`. Also owns its **own input binding** — it binds the
`"Up"`/`"Down"`/`"Left"`/`"Right"` actions itself in its constructor (or an
`OnRegistration` override), rather than the entity doing it. Attaching it to any entity
makes that entity grid-step and respond to input, with zero entity-specific code:

```cpp
// illustrative — not an applied edit
class MovementComponent : public Core::Components::IComponent {
 public:
  MovementComponent(
      Core::Events::IEventBus& eventBus, Core::Input::ActionRouter& inputRouter,
      Core::Spatial::ITransform2D& transform, MovementComponentParams params
  );
  void OnUpdate(float deltaTime) override;
  void SetDirection(Core::Math::Vector2D value);

 private:
  void Step();
  Core::Events::IEventBus& eventBus;
  Core::Spatial::ITransform2D& transform;
  Core::Math::Vector2D direction{};
  Core::Math::Vector2D pendingDirection{};
  float moveTimer = 0.0f;
  float moveInterval = 0.15f;
  float cellSize;
};
```

`SnakeHead`/`SnakeSegment` shed all of this — they go back to being plain transform +
collider + render holders, exactly like the apple.

### 3. Body-following stays snake-specific, driven by a data-carrying event

`MovementComponent` has no idea a "body" exists — attaching it to the apple must not
drag a tail behind it. So the tail-to-head follow logic stays on `SnakeBodyComponent`
(already snake-specific), and the two are decoupled through the **existing event bus**,
which already supports arbitrary fields on events with zero changes needed —
`IEventBus::Publish<TEvent>`/`Subscribe<TEvent>` are fully generic over the concrete
event type today (`i-event-bus.hpp:19-37`); `GameStartedEvent`/`AppleCollectedEvent` are
only empty because nobody's put fields on one yet.

Because the event bus is scene-global (one shared bus for everything), the event has to
carry enough to identify its source, so a subscriber can filter to "was that *my* head":

```cpp
// illustrative
struct MovementSteppedEvent : Core::Events::IEvent {
  Core::Entities::IEntity* entity;
  Core::Math::Vector2D oldPosition;
  Core::Math::Vector2D newPosition;
};
```

`SnakeBodyComponent` subscribes, checks `event.entity == this->owner`, and on a match
walks its segment deque **tail-to-head**, each segment taking the position of the one
ahead of it *before* that one moves this tick — the standard "follow the leader"
technique, and the reason the body traces the exact path the head took instead of
cutting corners.

<svg viewBox="0 0 760 360" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#17171a;border:1px solid #3a3a3a;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="own2" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="good2" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#34d399"/></marker>
    <marker id="obs2" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a3a3a8"/></marker>
  </defs>
  <g>
    <rect x="290" y="16" width="180" height="46" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="380" y="44" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e8ea" font-weight="600">SnakeHead : Entity</text>
  </g>
  <g>
    <rect x="20" y="100" width="200" height="50" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="120" y="130" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11" fill="#e8e8ea">Transform / Collider /</text>
    <text x="120" y="144" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11" fill="#e8e8ea">Render / Input (unchanged)</text>
  </g>
  <g>
    <rect x="280" y="100" width="200" height="50" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="2"/>
    <text x="380" y="122" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">MovementComponent</text>
    <text x="380" y="138" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#8ee7bf">direction, timer, input binding</text>
  </g>
  <g>
    <rect x="540" y="100" width="200" height="50" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="2"/>
    <text x="640" y="122" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea" font-weight="600">SnakeBodyComponent</text>
    <text x="640" y="138" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#8ee7bf">segments deque, tail-to-head follow</text>
  </g>
  <line x1="330" y1="62" x2="120" y2="100" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own2)"/>
  <line x1="370" y1="62" x2="380" y2="100" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own2)"/>
  <line x1="430" y1="62" x2="640" y2="100" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#own2)"/>
  <g>
    <rect x="280" y="210" width="200" height="50" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="380" y="232" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e8ea">IEventBus</text>
    <text x="380" y="248" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a3a3a8">scene-global, shared</text>
  </g>
  <path d="M380,150 C380,175 380,185 380,210" stroke="#34d399" stroke-width="1.8" fill="none" marker-end="url(#good2)"/>
  <text x="470" y="185" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#8ee7bf">Publish&lt;MovementSteppedEvent&gt;</text>
  <path d="M480,225 C560,200 600,175 640,150" stroke="#a3a3a8" stroke-width="1.6" fill="none" stroke-dasharray="5 4" marker-end="url(#obs2)"/>
  <text x="600" y="195" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a3a3a8">Subscribe, filter: event.entity == owner</text>
  <g>
    <rect x="280" y="300" width="200" height="46" rx="8" fill="#242424" stroke="#4a4a4e"/>
    <text x="380" y="322" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11" fill="#e8e8ea">SnakeSegment[] (body)</text>
    <text x="380" y="337" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a3a3a8">repositioned tail-to-head</text>
  </g>
  <line x1="640" y1="150" x2="420" y2="300" stroke="#a3a3a8" stroke-width="1.4" stroke-dasharray="5 4" marker-end="url(#obs2)"/>
</svg>

<span style="color:#a78bfa">■</span> owns &nbsp;&nbsp; <span style="color:#34d399">■</span> publish &nbsp;&nbsp; <span style="color:#a3a3a8">┄</span> subscribe / non-owning reaction

## One grid tick, end to end

1. Player presses a direction key → `InputComponent` fires the bound digital action →
   `MovementComponent::SetDirection(...)` sets `pendingDirection`.
2. Every frame, `Entity::Update` ticks every component, including `MovementComponent`;
   its `OnUpdate` accumulates `moveTimer += deltaTime`.
3. Once `moveTimer >= moveInterval`: commit `pendingDirection` into `direction`
   (reversal-guarded), record the transform's old position, move it by
   `direction * cellSize`, then publish `MovementSteppedEvent{ this->owner, oldPos, newPos }`.
4. `SnakeBodyComponent::OnMovementStepped` checks `event.entity == this->owner`; if it
   matches, it walks its segment deque from the tail forward, each segment taking the
   position the one ahead of it held *before* this tick — finishing with the frontmost
   segment taking the head's `oldPosition`.

## Adoption order

| Step | Change | Why this order |
|------|--------|-----------------|
| 1 | Add `virtual void OnUpdate(float) {}` to `IComponent` | Foundational — nothing else compiles against a ticking component until this exists |
| 2 | `Entity::Update` iterates `components` and calls `OnUpdate` on each | Makes step 1 actually happen every frame |
| 3 | Add `MovementSteppedEvent` (entity + old/new position) | Needed before either side of the pub/sub pair can be written |
| 4 | Build `MovementComponent`: state, input binding, timer-gated `Step()`, publish on step | Self-contained — can be attached to the apple as a smoke test before touching the snake at all |
| 5 | Strip `direction`/`pendingDirection`/`moveTimer`/`moveInterval`/`Step()`/`SetDirection()`/input binding out of `SnakeSegment`/`SnakeHead`; attach `MovementComponent` in `SnakeHead::OnRegistration` instead | Only safe once step 4 is proven working elsewhere |
| 6 | `SnakeBodyComponent` subscribes to `MovementSteppedEvent`, filters by entity, does the tail-to-head shift | Completes the feature — this is "Part 2" (body follows head) |
| 7 | *(optional smoke test)* Attach `MovementComponent` to `Apple` and confirm it grid-steps/responds to input with no apple-specific code | Validates the reusability goal directly, not just in theory |

## Summary

| Goal from discussion | How this design addresses it |
|---|---|
| "Is it a problem that components can't tick?" | Yes — fixed generically via `IComponent::OnUpdate`, not a one-off for movement |
| "Movement should be a character feature, not a game system" | `MovementComponent` is attachable to any entity; no `GameSystem` involved |
| "If I gave the apple a movement component, it should just work" | Component has zero snake-specific knowledge; body-following lives entirely in `SnakeBodyComponent` instead |
| "We have an event system for this" | Reused as-is — `Publish`/`Subscribe` already support arbitrary event data, just needed fields added |
| "Could events carry callable behavior too?" | Deliberately out of scope — flagged as a separate, parallel idea (a request/command mechanism) to consider later, not conflated with broadcast events here |
