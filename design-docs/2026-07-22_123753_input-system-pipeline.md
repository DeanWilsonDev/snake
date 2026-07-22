# Input System: Event-Driven Pipeline & Application Systems Extension Point

*Design document — not yet implemented. Per this repository's read-only policy, this is a
proposal for a human to build; Claude has not touched any source file.*

## Executive summary

The engine already has one working example of the shape this design reuses: the entity
manager's component pipeline (`EntityManager` → `ComponentDispatcher` → N
`IComponentRegistrar`s). Input needs the same shape for the same reason components do —
multiple independent producers (keyboard today, gamepad soon) need to resolve into one
shared vocabulary (`Action`) without the aggregator knowing about each producer's internals.

This document proposes:

1. An **input pipeline** — `IInputSource` implementations (one per device) feed an
   `InputDispatcher`, which aggregates per-`Action` state, edge-detects press/release
   transitions, and publishes them on the existing `IEventBus`.
2. An **`ISystem` extension point on `Application`** — a small, explicit, app-global list of
   update-driven systems, run once per frame *before* the scene manager, so that
   synchronously-dispatched events (like input) reach their subscribers in the same frame
   they occur.

Net effect: `SnakeGame::GameplayState::Update()` stops polling `IsActionPressed()` every
frame (removing the `MAIN QUEST` TODO already sitting at `gameplay-state.cpp:45-63`) and
instead subscribes once to `InputActionPressedEvent`.

---

## 1. Why mirror the entity pipeline pattern

The entity pipeline pattern earns its complexity because it solves a specific problem: an
**open-ended set of producers, each opting into a shared concern, aggregated by one
dispatcher that doesn't know their concrete types.** For entities that's "component type →
registrar." For input, the same shape shows up once a second device is in scope: "input
device → resolves into `Action` state."

Today there is one device (keyboard) and no dispatcher — `InputSystem` polls
`IInputBackend` directly. That's fine in isolation, but a planned gamepad source means the
aggregation logic (OR-ing multiple devices' state per `Action`, edge-detecting once, not per
device) needs a home now, or it gets bolted on awkwardly later.

<svg viewBox="0 0 760 420" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="own1" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="obs1" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a99fc4"/></marker>
  </defs>
  <text x="20" y="24" font-family="-apple-system,sans-serif" font-size="12" fill="#a99fc4" font-weight="600">EXISTING — entity component pipeline</text>
  <g>
    <rect x="30" y="40" width="180" height="56" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="120" y="63" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">EntityManager</text>
    <text x="120" y="80" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">owns pipeline</text>
  </g>
  <g>
    <rect x="300" y="40" width="190" height="56" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="395" y="63" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">ComponentDispatcher</text>
    <text x="395" y="80" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">vector&lt;unique_ptr&lt;IComponentRegistrar&gt;&gt;</text>
  </g>
  <g>
    <rect x="580" y="18" width="160" height="46" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="660" y="46" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#e8e3f5" font-weight="600">RenderComponentRegistrar</text>
  </g>
  <g>
    <rect x="580" y="76" width="160" height="40" rx="8" fill="#241f33" stroke="#4b3f6b" stroke-dasharray="4 3"/>
    <text x="660" y="100" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">…more registrars</text>
  </g>
  <line x1="210" y1="68" x2="300" y2="68" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own1)"/>
  <text x="255" y="60" text-anchor="middle" font-size="10" fill="#c4b5fd">owns</text>
  <line x1="490" y1="60" x2="580" y2="42" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own1)"/>
  <line x1="490" y1="76" x2="580" y2="96" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own1)"/>
  <line x1="20" y1="150" x2="740" y2="150" stroke="#362e4d" stroke-width="1"/>
  <text x="380" y="146" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4" font-style="italic">same shape, mirrored ↓</text>
  <text x="20" y="184" font-family="-apple-system,sans-serif" font-size="12" fill="#a99fc4" font-weight="600">PROPOSED — input pipeline</text>
  <g>
    <rect x="30" y="200" width="180" height="56" rx="8" fill="#1d1a2b" stroke="#a78bfa" stroke-width="2"/>
    <text x="120" y="223" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">InputSystem</text>
    <text x="120" y="240" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#c4b5fd">: Core::ISystem</text>
  </g>
  <g>
    <rect x="300" y="200" width="190" height="56" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="395" y="223" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">InputDispatcher</text>
    <text x="395" y="240" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">vector&lt;unique_ptr&lt;IInputSource&gt;&gt;</text>
  </g>
  <g>
    <rect x="580" y="178" width="160" height="46" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="660" y="200" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#e8e3f5" font-weight="600">KeyboardInputSource</text>
    <text x="660" y="215" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a99fc4">wraps IInputBackend + KeyMap</text>
  </g>
  <g>
    <rect x="580" y="236" width="160" height="46" rx="8" fill="#221c2a" stroke="#a99fc4" stroke-width="1.4" stroke-dasharray="5 4"/>
    <text x="660" y="257" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#a99fc4" font-weight="600">GamepadInputSource</text>
    <text x="660" y="272" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a99fc4">(planned, not built)</text>
  </g>
  <line x1="210" y1="228" x2="300" y2="228" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own1)"/>
  <text x="255" y="220" text-anchor="middle" font-size="10" fill="#c4b5fd">owns</text>
  <line x1="490" y1="220" x2="580" y2="201" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own1)"/>
  <line x1="490" y1="236" x2="580" y2="259" stroke="#a99fc4" stroke-width="1.6" stroke-dasharray="5 4" marker-end="url(#obs1)"/>
  <text x="120" y="310" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">
    <tspan x="30" dy="0">InputSystem is the pipeline owner — same role EntityManager plays.</tspan>
    <tspan x="30" dy="16">It is what gets registered with Application as an ISystem (§3).</tspan>
  </text>
  <g>
    <rect x="30" y="340" width="710" height="60" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="1.4"/>
    <text x="385" y="364" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="11.5" fill="#8ee7bf" font-weight="600">Key difference from the entity pipeline</text>
    <text x="385" y="382" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">Sources report raw level state only (IsActionDown). Edge-detection and event</text>
    <text x="385" y="396" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">publishing live centrally in InputDispatcher — not duplicated per source.</text>
  </g>
</svg>

<span style="color:#a78bfa">■</span> owns (`unique_ptr`) &nbsp;&nbsp;
<span style="color:#a99fc4">┄</span> planned / not-yet-built

---

## 2. Input pipeline types

```cpp
// core/input/i-input-source.hpp
namespace Core::Input {
class IInputSource {
 public:
  virtual ~IInputSource() = default;
  virtual bool IsActionDown(Engine::Input::Action action) const = 0;
};
}  // namespace Core::Input
```

`IInputSource` reports **level state only** — no press/release logic. That logic is
centralized once in the dispatcher instead of being reimplemented per device (today's
`InputSystem::IsActionPressed` derives edges from raylib's own per-frame `IsKeyPressed`,
which won't exist in the same form on a gamepad backend — better to not depend on each
device having edge-detection built in).

```cpp
// core/input/i-input-dispatcher.hpp
namespace Core::Input {
class IInputDispatcher {
 public:
  virtual ~IInputDispatcher() = default;
  virtual void AddSource(std::unique_ptr<IInputSource> source) = 0;
  virtual void Run() = 0;
};
}  // namespace Core::Input
```

```cpp
// engine/input/input-dispatcher.hpp / .cpp
namespace Engine::Input {
class InputDispatcher final : public Core::Input::IInputDispatcher {
 public:
  InputDispatcher(Core::Events::IEventBus& eventBus);
  void AddSource(std::unique_ptr<Core::Input::IInputSource> source) override;
  void Run() override;
  bool IsActionDown(Action action) const;  // pull-query escape hatch, see §4

 private:
  std::vector<std::unique_ptr<Core::Input::IInputSource>> sources;
  std::array<bool, static_cast<size_t>(Action::Count)> lastFrameDown = {};
  Core::Events::IEventBus& eventBus;
};
}  // namespace Engine::Input
```

`Run()`, per `Action`:

1. `isDown = OR` across every source's `IsActionDown(action)`.
2. Compare against `lastFrameDown[action]`.
3. On `false → true`, `eventBus.Publish(InputActionPressedEvent{action})`.
   On `true → false`, `eventBus.Publish(InputActionReleasedEvent{action})`.
4. `lastFrameDown[action] = isDown`.

```cpp
// engine/input/sources/keyboard-input-source.hpp
namespace Engine::Input::Sources {
class KeyboardInputSource final : public Core::Input::IInputSource {
 public:
  KeyboardInputSource(Core::Input::IInputBackend& backend, const KeyMap& keyMap);
  bool IsActionDown(Action action) const override;

 private:
  Core::Input::IInputBackend& backend;
  KeyMap keyMap;
};
}  // namespace Engine::Input::Sources
```

This is today's `InputSystem::IsActionDown` body, moved down one layer unchanged.
`GamepadInputSource` gets the same shape later — that's the whole point of factoring this
out now rather than after the second device shows up.

```cpp
// engine/input/input-system.hpp
namespace Engine::Input {
class InputSystem final : public Core::ISystem {
 public:
  InputSystem(Core::Input::IInputBackend& backend, Core::Events::IEventBus& eventBus, const KeyMap& keyMap);
  void OnUpdate(float deltaTime) override;   // -> dispatcher.Run()
  void OnDebugUpdate() const override;       // optional: overlay current action state
  void OnDebugRender() const override;

 private:
  InputDispatcher dispatcher;
};
}  // namespace Engine::Input
```

`InputSystem` is the pipeline **owner** — the same role `EntityManager` plays over its two
pipelines. It's also the thing that becomes an `ISystem` and gets registered with
`Application` (§5).

---

## 3. Events

`IEventBus::Publish<TEvent>` dispatches by `typeid` against `std::any` — nothing requires
events to derive from `Core::Events::IEvent`. (That marker interface exists in the codebase
but nothing currently implements it; every event type so far, including
`window-resized-event.hpp` and `apple-collected-events.hpp`, is an empty stub.) Plain structs
are enough:

```cpp
// core/events/input/input-action-pressed-event.hpp
namespace Core::Events::Input {
struct InputActionPressedEvent {
  Engine::Input::Action action;
};
}  // namespace Core::Events::Input

// core/events/input/input-action-released-event.hpp
namespace Core::Events::Input {
struct InputActionReleasedEvent {
  Engine::Input::Action action;
};
}  // namespace Core::Events::Input
```

These fill in the two existing empty stubs at `core/events/input/key-pressed-event.hpp` /
`key-released-event.hpp` — but named after `Action`, not `KeyCode`. That naming choice
matters: a rebind, or a second device entirely, never touches subscriber code, because
subscribers only ever hear about the semantic action, never the physical key or button.

> **Cleanup note.** There are currently two empty stub locations for these events —
> `core/events/input/` and `engine/events/input/`. Recommend consolidating to
> `core/events/input/` only, consistent with `core/events/window/` already holding the
> window event types at the `core` layer.

---

## 4. Per-frame dispatch & edge-detection flow

<svg viewBox="0 0 760 560" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="own2" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="good2" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#34d399"/></marker>
    <marker id="obs2" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a99fc4"/></marker>
  </defs>
  <text x="380" y="24" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="12" fill="#a99fc4" font-weight="600">InputDispatcher::Run() — per Action, once per frame</text>
  <g>
    <rect x="180" y="40" width="400" height="50" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="70" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5">poll each source: source-&gt;IsActionDown(action)</text>
  </g>
  <line x1="380" y1="90" x2="380" y2="120" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own2)"/>
  <g>
    <rect x="180" y="120" width="400" height="50" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="150" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5">isDown = OR(...) across all sources</text>
  </g>
  <line x1="380" y1="170" x2="380" y2="200" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own2)"/>
  <g>
    <rect x="180" y="200" width="400" height="50" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="230" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5">wasDown = lastFrameDown[action]</text>
  </g>
  <line x1="380" y1="250" x2="380" y2="280" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own2)"/>
  <polygon points="380,280 500,325 380,370 260,325" fill="#241f33" stroke="#4b3f6b" stroke-width="1.4"/>
  <text x="380" y="320" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11" fill="#e8e3f5">isDown</text>
  <text x="380" y="335" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11" fill="#e8e3f5">!= wasDown ?</text>
  <line x1="500" y1="325" x2="600" y2="325" stroke="#34d399" stroke-width="1.8" marker-end="url(#good2)"/>
  <text x="550" y="315" text-anchor="middle" font-size="10" fill="#8ee7bf">yes</text>
  <g>
    <rect x="600" y="300" width="140" height="66" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="1.6"/>
    <text x="670" y="325" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="10.5" fill="#e8e3f5" font-weight="600">Publish</text>
    <text x="670" y="340" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#8ee7bf">Pressed / Released</text>
    <text x="670" y="353" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#8ee7bf">event via IEventBus</text>
  </g>
  <line x1="670" y1="366" x2="670" y2="410" stroke="#34d399" stroke-width="1.8" marker-end="url(#good2)"/>
  <g>
    <rect x="470" y="410" width="270" height="56" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="1.4"/>
    <text x="605" y="433" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#e8e3f5" font-weight="600">Subscribers react — same frame</text>
    <text x="605" y="450" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#8ee7bf">(Snake::SetDirection, UI, ...)</text>
  </g>
  <line x1="380" y1="370" x2="380" y2="490" stroke="#a99fc4" stroke-width="1.6" stroke-dasharray="5 4" marker-end="url(#obs2)"/>
  <text x="392" y="430" font-size="10" fill="#a99fc4">no — no publish</text>
  <g>
    <rect x="180" y="490" width="400" height="50" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="520" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5">lastFrameDown[action] = isDown</text>
  </g>
  <line x1="670" y1="466" x2="580" y2="490" stroke="#a99fc4" stroke-width="1.4" stroke-dasharray="5 4" marker-end="url(#obs2)"/>
</svg>

The dispatcher never needs to know *which* source flipped the bit — only that the aggregate
changed. That's what makes adding `GamepadInputSource` later a pure addition: it plugs into
step 1's OR, nothing downstream changes.

`InputDispatcher::IsActionDown(action)` (the pull-query mentioned in §2) is a thin read of
the same aggregated `isDown` computed in step 2, exposed for callers that genuinely want
level-based polling (e.g. a UI element checking "is Confirm currently held") rather than
subscribing to edges. Snake's own movement doesn't need it — see §6.

---

## 5. `Application` systems extension point

`Core::IDependencyInjector` binds one implementation per interface type — there is no
"resolve all registered `ISystem`" query. So the systems list can't be assembled by the
container; `Application` has to build it explicitly, the same way it already hand-resolves
`window`, `renderer`, `input`, etc. in `Initialize()`.

```cpp
// core/systems/i-system.hpp
namespace Core {
class ISystem : public Core::IOnUpdatable, public Core::Debug::IOnDebugable {};
}  // namespace Core
```

No new methods — `ISystem` just names the combination of hooks (`OnUpdate`,
`OnDebugUpdate`, `OnDebugRender`) that `Application` already knows how to drive, the same
combination `IEntityManager` implements today.

<svg viewBox="0 0 760 480" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="own3" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
  </defs>
  <text x="20" y="24" font-family="-apple-system,sans-serif" font-size="12" fill="#a99fc4" font-weight="600">Wiring — RegisterDependencies() / Initialize()</text>
  <g>
    <rect x="30" y="40" width="700" height="60" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="64" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#e8e3f5">auto input = std::make_shared&lt;InputSystem&gt;(*inputBackend, *eventBus, keyMap);</text>
    <text x="380" y="82" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#e8e3f5">this-&gt;RegisterSystem(input);</text>
  </g>
  <line x1="380" y1="100" x2="380" y2="130" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own3)"/>
  <g>
    <rect x="230" y="130" width="300" height="50" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="160" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5">Application::systems</text>
    <text x="380" y="150" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a99fc4"></text>
  </g>
  <text x="380" y="196" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">vector&lt;shared_ptr&lt;ISystem&gt;&gt; — app-global, survives scene/state changes</text>
  <text x="20" y="238" font-family="-apple-system,sans-serif" font-size="12" fill="#a99fc4" font-weight="600">Frame loop — Application::OnUpdate(deltaTime)</text>
  <g>
    <rect x="30" y="254" width="700" height="180" rx="10" fill="#1b1728" stroke="#362e4d" stroke-dasharray="4 3"/>
  </g>
  <g>
    <rect x="60" y="274" width="640" height="50" rx="8" fill="#1d1a2b" stroke="#a78bfa" stroke-width="1.6"/>
    <text x="380" y="300" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#e8e3f5">for (auto&amp; system : this-&gt;systems) system-&gt;OnUpdate(deltaTime);</text>
    <text x="380" y="312" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9" fill="#c4b5fd">1st — includes InputSystem, publishes this frame's action events</text>
  </g>
  <line x1="380" y1="324" x2="380" y2="350" stroke="#a78bfa" stroke-width="1.8" marker-end="url(#own3)"/>
  <g>
    <rect x="60" y="350" width="640" height="46" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="378" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="11.5" fill="#e8e3f5">if (sceneManager) sceneManager-&gt;OnUpdate(deltaTime);</text>
  </g>
  <text x="380" y="416" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="9.5" fill="#a99fc4">2nd — scene/state logic reads this frame's already-published events</text>
  <g>
    <rect x="30" y="446" width="700" height="30" rx="6" fill="#2a1c26" stroke="#fb7185" stroke-width="1.2"/>
    <text x="380" y="466" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#fda4af">Reversing this order delays every press by one frame — IEventBus::Publish is synchronous, no queue.</text>
  </g>
</svg>

`InputSystem` needs `IInputBackend&` and `IEventBus&`, both already resolved by
`Application::Initialize()` before systems are constructed, so no new DI plumbing is
required — just an explicit construction + `RegisterSystem` call alongside the existing
hand-wiring block.

---

## 6. Downstream effect on `SnakeGame`

`SnakeGame::GameContext` (`gameplay-state-machine.hpp:22`) currently holds
`unique_ptr<Engine::Input::InputSystem> input` as a per-state polling handle. Once
`InputSystem` is app-global and event-driven, that field goes away. `GameplayState`
(or `Snake` itself) subscribes once — e.g. in `Enter()` or construction — instead of the
polling block at `gameplay-state.cpp:45-63`:

```cpp
// illustrative — not applied
this->eventBus.Subscribe<InputActionPressedEvent>([this](const auto& e) {
  switch (e.action) {
    case Action::MoveLeft:  this->snake->SetDirection({-1, 0}); break;
    case Action::MoveRight: this->snake->SetDirection({1, 0});  break;
    case Action::MoveUp:    this->snake->SetDirection({0, -1}); break;
    case Action::MoveDown:  this->snake->SetDirection({0, 1});  break;
    default: break;
  }
});
```

**Why edge-triggered is correct here, not a compromise:** Snake only cares about direction
*changes* — it never needs to re-apply the same direction every frame the key stays held.
That's exactly what `InputActionPressedEvent` gives for free. A future held/level-based
action (e.g. a "boost" that only applies while a key is down) is the one case that
should use `InputDispatcher::IsActionDown()` as a pull-query instead — no third event type
needed.

---

## 7. Summary — design decisions and what they resolve

| Decision | Resolves | Rationale |
|---|---|---|
| `IInputSource` reports level state only, no per-source edge logic | Duplicated press/release logic across devices | Raylib gives free edge detection; a gamepad backend may not. Centralizing in the dispatcher means every device only needs to answer "is this down right now." |
| `InputDispatcher` aggregates via OR before edge-detecting | Multiple devices publishing conflicting/duplicate events for one logical press | Dispatcher sees one boolean per `Action`, not N per device — matches how `ComponentDispatcher` sees one component stream, not N per registrar. |
| Events keyed by `Action`, not `KeyCode` | Rebinding / new devices breaking subscriber code | Subscribers only ever hear semantic actions. |
| Plain structs for events, no `IEvent` base | Following existing (unused) pattern needlessly | `IEventBus` dispatches by `typeid`; nothing in the codebase actually requires `IEvent`. |
| `ISystem` list is app-global, owned by `Application` | Needing to design scene-transition ownership for systems right now | Matches how input actually behaves — always live, not scene-scoped. Deferred, not rejected: revisit if a system needs scene-scoped lifetime later. |
| Systems run before `sceneManager->OnUpdate()` | Input events arriving one frame late | `IEventBus::Publish` is synchronous — publisher and subscriber must run in dispatch order within the same frame. |
| Systems list assembled explicitly in `RegisterDependencies()`/`Initialize()`, not DI-resolved | `IDependencyInjector` has no "resolve all `X`" query | Matches existing hand-wiring pattern for `window`/`renderer`/etc. — no new DI capability needed. |

---

## 8. Suggested adoption order

1. Add `Core::ISystem` + the `systems` vector and `RegisterSystem` helper on `Application`;
   reorder `OnUpdate` (systems, then scene manager). No behavior change yet — empty list.
2. Add `Core::Input::IInputSource`, `IInputDispatcher`, `Engine::Input::InputDispatcher`.
3. Add `KeyboardInputSource`, wrapping today's `InputSystem` polling logic verbatim.
4. Fill in `InputActionPressedEvent` / `InputActionReleasedEvent` (consolidate the duplicate
   empty stub locations down to `core/events/input/` while here).
5. Rework `InputSystem` into the `ISystem`-implementing pipeline owner; register it in
   `Application::RegisterDependencies()`.
6. Migrate `GameplayState`/`Snake` from polling `GameContext::input` to subscribing to
   `InputActionPressedEvent`; remove the `GameContext::input` field and the TODO block at
   `gameplay-state.cpp:45-63`.
7. When a gamepad backend exists: add `GamepadInputSource`, register it alongside
   `KeyboardInputSource` in `InputSystem`'s constructor. No other code changes required —
   this is the step the whole design exists to make cheap.
