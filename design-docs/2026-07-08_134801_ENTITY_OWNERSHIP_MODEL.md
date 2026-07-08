# Single Entity-Ownership Model — Snake Engine

**Branch:** `game-with-engine-architecture` **·** **Date:** 2026-07-08 **·** **Scope:** entity / component lifetime across `src/engine`, `src/snake-game`, `src/renderer-2d`

---

## 1. Executive summary

The reported double-free (F1/F2) and the live null-deref crash (F8) are three faces of one
root cause: **the same objects are reachable through owners with incompatible lifetime
assumptions.** Entities are `new`ed and handed to a raw-pointer container while their
sub-objects are held by `unique_ptr` elsewhere; some objects have two owners, others have
none. This document proposes a **single-owner model** — exactly one `unique_ptr` owner per
object, everyone else a non-owning observer — and shows how it dissolves F1, F2, F3, F4,
F8, F9 and F13 together.

> **The rule:** *Exactly one owner (`unique_ptr`) per object. Everyone else holds a
> non-owning observer (`T*` / `T&`) and must de-register before the owner's destructor runs.*

---

## 2. Where we are today — tangled ownership

Three lifetime models point at the same objects. `SnakeSegment` has **two** owners; `Apple`
and its transform have **none**; the render manager holds raw pointers into objects owned by
someone else.

<svg viewBox="0 0 760 540" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="aA" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="aD" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#fb7185"/></marker>
  </defs>

  <!-- nodes -->
  <g>
    <rect x="290" y="18" width="180" height="42" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="44" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">GameplayScene</text>
  </g>

  <g>
    <rect x="55" y="112" width="255" height="60" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="182" y="136" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">EntityManager</text>
    <text x="182" y="156" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">vector&lt;IEntity*&gt; — non-owning</text>
  </g>

  <g>
    <rect x="470" y="112" width="235" height="60" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="587" y="136" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">Snake</text>
    <text x="587" y="156" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#fb7185">new — never stored ⇒ leaked</text>
  </g>

  <g>
    <rect x="480" y="236" width="215" height="58" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="587" y="260" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">Snake::body</text>
    <text x="587" y="279" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">deque&lt;unique_ptr&lt;SnakeSegment&gt;&gt;</text>
  </g>

  <g>
    <rect x="300" y="360" width="185" height="56" rx="8" fill="#2a1c26" stroke="#fb7185" stroke-width="2"/>
    <text x="392" y="384" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">SnakeSegment</text>
    <text x="392" y="403" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#fb7185">⚠ two owners</text>
  </g>

  <g>
    <rect x="70" y="360" width="170" height="56" rx="8" fill="#2a1c26" stroke="#fb7185" stroke-width="2"/>
    <text x="155" y="384" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">Apple</text>
    <text x="155" y="403" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#fb7185">⚠ no owner ⇒ leak</text>
  </g>

  <g>
    <rect x="70" y="458" width="290" height="58" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="215" y="482" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">RenderComponent2DManager</text>
    <text x="215" y="501" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">vector&lt;IRenderComponent*&gt; (app-lifetime)</text>
  </g>

  <g>
    <rect x="430" y="458" width="255" height="58" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="557" y="482" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5" font-weight="600">Entity's render component</text>
    <text x="557" y="501" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">unique_ptr — owned by Entity</text>
  </g>

  <!-- edges -->
  <line x1="352" y1="60" x2="215" y2="112" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#aA)"/>
  <text x="243" y="86" text-anchor="middle" font-size="10" fill="#c4b5fd">owns (by value)</text>

  <line x1="420" y1="60" x2="560" y2="112" stroke="#fb7185" stroke-width="1.6" stroke-dasharray="5 4" marker-end="url(#aD)"/>
  <text x="512" y="86" text-anchor="middle" font-size="10" fill="#fb7185">new → leak</text>

  <line x1="587" y1="172" x2="587" y2="236" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#aA)"/>
  <text x="601" y="208" font-size="10" fill="#c4b5fd">owns</text>

  <line x1="500" y1="294" x2="470" y2="360" stroke="#fb7185" stroke-width="1.8" marker-end="url(#aD)"/>
  <text x="470" y="330" text-anchor="end" font-size="10" fill="#fb7185">unique_ptr OWNS</text>

  <line x1="240" y1="168" x2="360" y2="360" stroke="#fb7185" stroke-width="1.6" stroke-dasharray="5 4" marker-end="url(#aD)"/>
  <text x="248" y="270" font-size="10" fill="#fb7185">raw IEntity* — 2nd claim</text>

  <line x1="165" y1="172" x2="157" y2="360" stroke="#fb7185" stroke-width="1.6" stroke-dasharray="5 4" marker-end="url(#aD)"/>
  <text x="120" y="250" font-size="10" fill="#fb7185">raw — no owner</text>

  <line x1="360" y1="487" x2="430" y2="487" stroke="#fb7185" stroke-width="1.6" stroke-dasharray="5 4" marker-end="url(#aD)"/>
  <text x="395" y="477" text-anchor="middle" font-size="9.5" fill="#fb7185">dangles</text>
</svg>

**Reading the diagram.** Solid purple = ownership (`unique_ptr` / by-value). Dashed red =
a non-owning raw pointer that *acts* like a claim. `SnakeSegment` is the collision point:
`Snake::body` owns it via `unique_ptr` while `EntityManager` also holds a raw `IEntity*`
to it — the moment the manager gets a real destructor (the natural fix for the `Apple`
leak), the segment is freed twice. `Apple` and its transform have no owner at all, so they
leak today. The app-lifetime `RenderComponent2DManager` keeps raw pointers into
per-entity components, so on scene teardown they dangle.

---

## 3. Target — one owner, observers everywhere else

`EntityManager` becomes the **sole owner** of every entity (segments *and* apple). `Snake`
becomes a controller that *observes* its segments. Managers keep non-owning observers and
are told to `Unregister` when the owner destroys the object.

<svg viewBox="0 0 760 470" style="width:100%;height:auto;max-width:760px;display:block;margin:16px auto;background:#1b1728;border:1px solid #362e4d;border-radius:10px" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <marker id="bA" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a78bfa"/></marker>
    <marker id="bG" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#34d399"/></marker>
    <marker id="bM" markerWidth="10" markerHeight="8" refX="8" refY="3" orient="auto"><path d="M0,0 L8,3 L0,6 Z" fill="#a99fc4"/></marker>
  </defs>

  <g>
    <rect x="290" y="16" width="180" height="42" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="380" y="42" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">GameplayScene</text>
  </g>

  <g>
    <rect x="235" y="112" width="280" height="60" rx="8" fill="#1d2a24" stroke="#34d399" stroke-width="2"/>
    <text x="375" y="136" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">EntityManager — SOLE OWNER</text>
    <text x="375" y="156" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#8ee7bf">vector&lt;unique_ptr&lt;IEntity&gt;&gt;</text>
  </g>

  <g>
    <rect x="560" y="112" width="180" height="60" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="650" y="136" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">Snake</text>
    <text x="650" y="156" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10.5" fill="#a99fc4">controller</text>
  </g>

  <g>
    <rect x="120" y="250" width="175" height="52" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="207" y="281" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">SnakeSegment</text>
  </g>

  <g>
    <rect x="330" y="250" width="150" height="52" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="405" y="281" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="13" fill="#e8e3f5" font-weight="600">Apple</text>
  </g>

  <g>
    <rect x="555" y="248" width="190" height="58" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="650" y="272" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12" fill="#e8e3f5" font-weight="600">Snake::body</text>
    <text x="650" y="291" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">deque&lt;SnakeSegment*&gt;</text>
  </g>

  <g>
    <rect x="40" y="382" width="300" height="58" rx="8" fill="#241f33" stroke="#4b3f6b"/>
    <text x="190" y="406" text-anchor="middle" font-family="ui-monospace,Menlo,monospace" font-size="12.5" fill="#e8e3f5" font-weight="600">RenderComponent2DManager</text>
    <text x="190" y="425" text-anchor="middle" font-family="-apple-system,sans-serif" font-size="10" fill="#a99fc4">vector&lt;IRenderComponent*&gt; (observers)</text>
  </g>

  <!-- edges -->
  <line x1="345" y1="58" x2="330" y2="112" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#bA)"/>
  <text x="285" y="90" text-anchor="end" font-size="10" fill="#c4b5fd">owns</text>

  <line x1="440" y1="52" x2="605" y2="112" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#bA)"/>
  <text x="540" y="78" text-anchor="middle" font-size="10" fill="#c4b5fd">owns (unique_ptr)</text>

  <line x1="320" y1="172" x2="215" y2="250" stroke="#34d399" stroke-width="1.8" marker-end="url(#bG)"/>
  <text x="238" y="212" text-anchor="middle" font-size="10" fill="#8ee7bf">owns</text>

  <line x1="390" y1="172" x2="405" y2="250" stroke="#34d399" stroke-width="1.8" marker-end="url(#bG)"/>
  <text x="418" y="212" font-size="10" fill="#8ee7bf">owns</text>

  <line x1="650" y1="172" x2="650" y2="248" stroke="#a78bfa" stroke-width="1.6" marker-end="url(#bA)"/>
  <text x="664" y="214" font-size="10" fill="#c4b5fd">has</text>

  <path d="M 600,306 C 520,346 360,346 252,304" fill="none" stroke="#a99fc4" stroke-width="1.5" stroke-dasharray="5 4" marker-end="url(#bM)"/>
  <text x="426" y="342" text-anchor="middle" font-size="10" fill="#a99fc4">observes (raw)</text>

  <line x1="200" y1="382" x2="207" y2="302" stroke="#a99fc4" stroke-width="1.5" stroke-dasharray="5 4" marker-end="url(#bM)"/>
  <text x="150" y="345" text-anchor="middle" font-size="9.5" fill="#a99fc4">observes; Unregister</text>
  <text x="150" y="358" text-anchor="middle" font-size="9.5" fill="#a99fc4">in ~Entity()</text>
</svg>

**Legend.** <span style="color:#34d399">■ green</span> = ownership transferred to the single
owner · <span style="color:#a78bfa">■ purple</span> = `unique_ptr` ownership ·
<span style="color:#a99fc4">■ dashed grey</span> = non-owning observer. There is now exactly
one solid arrow into every object, and observers can never outlive their target because the
owner's destructor drives de-registration.

---

## 4. The shape, in code

> These are **illustrative sketches** against the current types, not applied edits.

### 4.1 `EntityManager` becomes the sole owner

```cpp
// entity-manager.hpp
// sink: caller hands over ownership; returns a non-owning handle
Core::Entities::IEntity* AddEntity(std::unique_ptr<Core::Entities::IEntity> entity);
void RemoveEntity(Core::Entities::IEntity* entity);
private:
  std::vector<std::unique_ptr<Core::Entities::IEntity>> entities;   // was vector<IEntity*>
```

```cpp
IEntity* EntityManager::AddEntity(std::unique_ptr<IEntity> e) {
  IEntity* handle = e.get();
  entities.push_back(std::move(e));
  return handle;
}
void EntityManager::RemoveEntity(IEntity* e) {
  std::erase_if(entities, [&](const auto& p){ return p.get() == e; });
  // ~Entity() runs here → its components unregister themselves (§4.4)
}
```

### 4.2 `GameplayScene::OnEnter` — no raw `new`

```cpp
this->snake = std::make_unique<Snake>(SnakeParams{ .settings = gameSettings, /* … */ });
this->snake->Initialize(this->entityManager);          // creates segments INTO the manager

auto apple = std::make_unique<Apple>(AppleParams{ /* position value */ });
this->entityManager.AddEntity(std::move(apple));
```

The stray `new Engine::Spatial::Transform2D(...)` disappears — `Apple` builds and owns its
own `TransformComponent2D` from a **value**, which also removes F3's dangling stack-temp and
that transform leak.

### 4.3 `Snake` creates into the manager, keeps observers

```cpp
// snake.hpp
std::deque<SnakeSegment*> body;   // was deque<unique_ptr<SnakeSegment>>
SnakeSegment* head{};
```

```cpp
// snake.cpp
void Snake::CreateBody(EntityManager& em) {
  for (int i = 0; i < length; i++) {
    Engine::Spatial::Transform2D t = /* per-segment value */;
    auto seg = std::make_unique<SnakeSegment>(SnakeSegmentParams{ i, t });
    SnakeSegment* handle = static_cast<SnakeSegment*>(em.AddEntity(std::move(seg)));
    body.push_back(handle);
  }
  head = body.front();
}
```

Growth (F4) now reads each segment's **own** transform, not a shared function-local
`static` or an address into a sibling segment.

### 4.4 The linchpin — symmetric register / unregister

```cpp
RenderComponent2D::~RenderComponent2D() { manager->Unregister(this); }  // observer removed before owner frees it
```

Give the component a back-pointer to its manager (or drive it from `~Entity()` if entities,
not components, should own that relationship). Wherever you `Register`, guarantee the
matching `Unregister` runs on destruction.

### 4.5 Fix F1 while you're here — `Unregister` takes an observer

```cpp
void Register(std::unique_ptr<IRenderComponentUI> component);   // sink (takes ownership)
void Unregister(IRenderComponentUI* component);                 // observer (no ownership)
// impl: std::erase_if(renderComponents, [&](auto& up){ return up.get() == component; });
```

---

## 5. What this dissolves

| Finding | How the single-owner model resolves it |
|---|---|
| 🔴 F2 — double free / leak / UAF | One owner (`EntityManager`). `Snake::body` no longer owns ⇒ no double free; `Apple` + transform now owned ⇒ no leak |
| 🔴 F1 — `Unregister` double-free | `Unregister` takes an observer, never a second `unique_ptr` |
| 🟠 F8 — null `entityManager` deref (live crash) | Delete `GameplayStateMachine::entityManager`; the scene's manager is the only one — the null-deref path is gone |
| 🟡 F9 — two entity managers | Single manager owned by the scene; state machine no longer duplicates it |
| 🟠 F3 — dangling stack transform | Entities own transforms by value; no pointer to a temporary |
| 🟠 F4 — shared `static` transform | Per-entity transform storage; no aliasing |
| 🟢 F13 — segment transform built twice | Built once, owned by the entity |
| — Transient scene re-entry | Destroying an entity unregisters its render component, so `SwitchTo` cleans up the app-lifetime manager instead of leaving dangling pointers |

---

## 6. Destruction-order caveat

`Snake`'s observers point into entities owned by `EntityManager`. Declare `entityManager`
**before** `snake` in the scene (members destroy in reverse declaration order), or
`snake.reset()` first, so the observer-holder tears down before the owner. Since `~Snake()`
only drops raw pointers (never dereferences them), order is not fatal — but the invariant to
preserve is: *observers never touch an object after its owner is gone.*

## 7. Suggested migration order

1. **`EntityManager` ownership** (§4.1) + delete raw `new` in `gameplay-scene.cpp` (§4.2).
2. **`Snake` observers** (§4.3) — segments created into the manager.
3. **Register/Unregister discipline** (§4.4) + **F1 signature** (§4.5).
4. **Delete `GameplayStateMachine::entityManager`** (F8/F9) — crash removed *properly*.
5. Rebuild under **AddressSanitizer** and drive a scripted play-through; ASan now reports
   any residual aliasing deterministically.
</content>
</invoke>
