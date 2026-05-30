diff --git a/src/core/entity/i-entity.hpp b/src/core/entity/i-entity.hpp
deleted file mode 100644
index a7955e8..0000000
--- a/src/core/entity/i-entity.hpp
+++ /dev/null
@@ -1,34 +0,0 @@
-//
-// Created by Dean Wilson on 3 May 2026
-//
-#pragma once
-
-#include "core/debug/i-debugable.hpp"
-#include "core/i-updatable.hpp"
-#include "core/components/i-component.hpp"
-#include <cassert>
-#include <typeindex>
-
-namespace Core::Entity {
-
-class IEntity : public Core::Debug::IDebugable, Core::IUpdatable {
- public:
-  virtual ~IEntity() = 0;
-
-  virtual void Initialize() = 0;
-  virtual void Update([[maybe_unused]] float deltaTime) override = 0;
-  virtual void DebugUpdate() const override = 0;
-  virtual void DebugRender() const override = 0;
-  virtual int GetID() const = 0;
-  virtual bool IsActive() const = 0;
-  virtual void SetActive(bool active) = 0;
-  virtual const bool& GetActive() = 0;
-  virtual Core::Components::IComponent* GetComponentByType(std::type_index type) = 0;
-
-  template <typename T>
-  T* GetComponent()
-  {
-    return static_cast<T*>(this->GetComponentByType(typeid(T)));
-  };
-};
-}  // namespace Core::Entity
diff --git a/src/core/entity/i-game-entity.hpp b/src/core/entity/i-game-entity.hpp
deleted file mode 100644
index 54854ab..0000000
--- a/src/core/entity/i-game-entity.hpp
+++ /dev/null
@@ -1,28 +0,0 @@
-//
-// Created by Dean Wilson on 25/8/2025.
-//
-
-#pragma once
-
-#include "i-entity.hpp"
-#include "core/components/transform-component-2d.hpp"
-
-namespace Core::Components {
-class IComponent;
-}
-
-namespace Core {
-namespace Entity {
-
-class IGameEntity : virtual public IEntity {
- public:
-  ~IGameEntity() override = 0;
-
-  virtual void Update(float deltaTime) override = 0;
-  virtual void DebugUpdate() const override = 0;
-  virtual void DebugRender() const override = 0;
-  virtual void Initialize() override = 0;
-  virtual Components::TransformComponent2D& GetTransformComponent() = 0;
-};
-}  // namespace Entity
-}  // namespace Core
diff --git a/src/core/rendering/components/i-render-component.hpp b/src/core/rendering/components/i-render-component.hpp
index cc92ada..26387c5 100644
--- a/src/core/rendering/components/i-render-component.hpp
+++ b/src/core/rendering/components/i-render-component.hpp
@@ -23,7 +23,7 @@ class IRenderComponent : public Core::Components::IComponent, IRenderable {
   [[nodiscard]] virtual float GetY() const = 0;
   [[nodiscard]] virtual float GetWidth() const = 0;
   [[nodiscard]] virtual float GetHeight() const = 0;
-  [[nodiscard]] virtual bool GetActive() const = 0;
+  [[nodiscard]] virtual const bool& GetActive() const = 0;
 };
 }  // namespace Components
 }  // namespace Rendering
diff --git a/src/core/user-interface/i-user-interface-manager.hpp b/src/core/user-interface/i-user-interface-manager.hpp
index ea0da10..9c09050 100644
--- a/src/core/user-interface/i-user-interface-manager.hpp
+++ b/src/core/user-interface/i-user-interface-manager.hpp
@@ -4,13 +4,16 @@
 
 #pragma once
 
-#include "core/debug/i-debugable.hpp"
-#include "core/rendering/i-render-manager.hpp"
-#include "core/i-updatable.hpp"
+#include "core/debug/i-on-debugable.hpp"
+#include "core/rendering/i-on-renderable.hpp"
+#include "core/i-on-updatable.hpp"
 
+
+
+// MAIN QUEST: Refactor this and the concrete class (Move the concrete class to Engine)
 namespace Core {
 namespace UserInterface {
-class IUserInterfaceManager : public IUpdatable, Debug::IDebugable, Rendering::IRenderManager {
+class IUserInterfaceManager : public IOnUpdatable, Debug::IOnDebugable, Rendering::IOnRenderable {
  public:
   virtual ~IUserInterfaceManager() = default;
 
diff --git a/src/engine/entity/entity-base.cpp b/src/engine/entity/entity-base.cpp
deleted file mode 100644
index 2a9ef58..0000000
--- a/src/engine/entity/entity-base.cpp
+++ /dev/null
@@ -1,54 +0,0 @@
-//
-// Created by Dean Wilson on 29/5/2025.
-//
-
-#include "entity-base.hpp"
-
-namespace Engine::Entity {
-
-EntityBase::EntityBase(const EntityBaseParams& params) : active(params.active) {};
-
-EntityBase::~EntityBase() = default;
-
-void EntityBase::Initialize() {}
-
-void EntityBase::Update([[maybe_unused]] float deltaTime) {}
-
-void EntityBase::DebugUpdate() const {}
-
-void EntityBase::DebugRender() const {}
-
-int EntityBase::GetID() const
-{
-  return this->id;
-}
-bool EntityBase::IsActive() const
-{
-  return this->active;
-}
-
-void EntityBase::SetActive(const bool active)
-{
-  this->active = active;
-}
-
-const bool& EntityBase::GetActive()
-{
-  return this->active;
-}
-
-int EntityBase::GenerateId()
-{
-  static int nextId = 0;
-  return nextId++;
-};
-
-Core::Components::IComponent* EntityBase::GetComponentByType(std::type_index type)
-{
-  if (const auto it = components.find(type); it != components.end()) {
-    return it->second.get();
-  }
-  return nullptr;
-}
-
-}  // namespace Engine::Entity
diff --git a/src/engine/entity/entity-base.hpp b/src/engine/entity/entity-base.hpp
deleted file mode 100644
index 9c40485..0000000
--- a/src/engine/entity/entity-base.hpp
+++ /dev/null
@@ -1,68 +0,0 @@
-//
-// Created by Dean Wilson on 29/5/2025.
-//
-#pragma once
-
-#include "core/components/i-component.hpp"
-#include "core/entity/i-entity.hpp"
-#include <cassert>
-#include <typeindex>
-#include <unordered_map>
-#include <memory>
-
-namespace Engine::Entity {
-
-struct EntityBaseParams {
-  bool active = true;
-
-  EntityBaseParams(bool active = true) : active(active) {}
-};
-
-class EntityBase : virtual public Core::Entity::IEntity {
- public:
-  explicit EntityBase(const EntityBaseParams& params);
-  virtual ~EntityBase() = 0;
-
-  virtual void Initialize() override;
-  virtual void Update([[maybe_unused]] float deltaTime) override;
-  virtual void DebugUpdate() const override;
-  virtual void DebugRender() const override;
-  virtual int GetID() const override;
-  virtual bool IsActive() const override;
-  virtual void SetActive(bool active) override;
-  virtual const bool& GetActive() override;
-  Core::Components::IComponent* GetComponentByType(std::type_index type) override;
-
-  template <typename T, typename... Args>
-  void AddComponent(Args&&... args);
-
-  template <typename T>
-  void RemoveComponent();
-
- private:
-  std::unordered_map<std::type_index, std::unique_ptr<Core::Components::IComponent>> components{};
-
-  static int GenerateId();
-  const int id{GenerateId()};
-  bool active{true};
-};
-
-template <typename T, typename... Args>
-void EntityBase::AddComponent(Args&&... args)
-{
-  // Ensure no duplicate components of the same type
-  const auto type = std::type_index(typeid(T));
-  assert(!components.contains(type) && "Component already added!");
-
-  // Emplace a new instance of T using perfect forwarding of arguments
-  components[type] = std::make_unique<T>(std::forward<Args>(args)...);
-}
-
-template <typename T>
-void EntityBase::RemoveComponent()
-{
-  const auto type = std::type_index(typeid(T));
-  this->components.erase(type);
-}
-
-}  // namespace Engine::Entity
diff --git a/src/engine/entity/game-entity-manager.cpp b/src/engine/entity/game-entity-manager.cpp
deleted file mode 100644
index fed4986..0000000
--- a/src/engine/entity/game-entity-manager.cpp
+++ /dev/null
@@ -1,63 +0,0 @@
-//
-// Created by Dean Wilson on 25/8/2025.
-//
-
-#include "engine/entity/game-entity-manager.hpp"
-#include "core/entity/i-entity.hpp"
-#include "core/rendering/components/i-render-component.hpp"
-#include "core/rendering/i-render-manager.hpp"
-#include "core/rendering/i-renderer.hpp"
-#include "core/rendering/i-render-component-manager.hpp"
-#include <vector>
-
-namespace Engine::Entity {
-
-GameEntityManager::GameEntityManager(Core::Rendering::IRenderComponentManager* renderManager)
-    : renderManager(renderManager)
-{
-}
-
-void GameEntityManager::AddEntity(Core::Entity::IEntity* entity)
-{
-  if (!entity) {
-    return;
-  }
-  this->entities.push_back(entity);
-  this->renderManager->Register(
-      entity->GetComponent<Core::Rendering::Components::IRenderComponent>()
-  );
-}
-
-void GameEntityManager::OnUpdate(const float deltaTime)
-{
-  for (auto* object : this->entities) {
-    if (object->IsActive()) {
-      object->Update(deltaTime);
-    }
-  }
-}
-
-void GameEntityManager::OnDebugUpdate() const
-{
-  for (auto* object : this->entities) {
-    if (object->IsActive()) {
-      object->DebugUpdate();
-    }
-  }
-}
-
-void GameEntityManager::OnDebugRender() const
-{
-  for (auto* object : this->entities) {
-    if (object->IsActive()) {
-      object->DebugRender();
-    }
-  }
-}
-
-void GameEntityManager::OnRender(const Core::Rendering::IRenderer& renderer) const
-{
-  this->renderManager->OnRender(renderer);
-}
-
-}  // namespace Engine::Entity
diff --git a/src/engine/entity/game-entity-manager.hpp b/src/engine/entity/game-entity-manager.hpp
deleted file mode 100644
index 776d43e..0000000
--- a/src/engine/entity/game-entity-manager.hpp
+++ /dev/null
@@ -1,43 +0,0 @@
-//
-// Created by Dean Wilson on 25/8/2025.
-//
-
-#pragma once
-#include "core/debug/i-on-debugable.hpp"
-#include "core/i-on-updatable.hpp"
-#include "core/rendering/i-on-renderable.hpp"
-
-#include <vector>
-
-namespace Core {
-namespace Entity {
-class IEntity;
-}
-namespace Rendering {
-class IRenderer;
-class IRenderComponentManager;
-}  // namespace Rendering
-}  // namespace Core
-
-namespace Engine {
-
-namespace Entity {
-
-class GameEntityManager : public Core::IOnUpdatable,
-                          Core::Debug::IOnDebugable,
-                          Core::Rendering::IOnRenderable {
- public:
-  GameEntityManager(Core::Rendering::IRenderComponentManager* renderManager);
-  void AddEntity(Core::Entity::IEntity* entity);
-  void OnUpdate(float deltaTime) override;
-  void OnDebugUpdate() const override;
-  void OnDebugRender() const override;
-  void OnRender(const Core::Rendering::IRenderer& renderer) const override;
-
- private:
-  std::vector<Core::Entity::IEntity*> entities;
-  Core::Rendering::IRenderComponentManager* renderManager;
-};
-
-}  // namespace Entity
-}  // namespace Engine
diff --git a/src/engine/entity/game-entity.cpp b/src/engine/entity/game-entity.cpp
deleted file mode 100644
index 52cfae9..0000000
--- a/src/engine/entity/game-entity.cpp
+++ /dev/null
@@ -1,78 +0,0 @@
-//
-// Created by Dean Wilson on 25/8/2025.
-//
-
-#include "game-entity.hpp"
-#include <memory>
-#include "core/components/transform-component-2d.hpp"
-#include "entity-base.hpp"
-#include "core/math/vector-2d.hpp"
-#include "core/math/size-2d.hpp"
-#include "core/logging/log.hpp"
-
-namespace Engine::Entity {
-
-GameEntity::GameEntity(const GameEntityParams& params) : EntityBase(params)
-{
-  LOG_TRACE("[GameEntity] Setting up new GameEntity");
-
-  if (params.transform) {
-    this->transformComponent =
-        std::make_unique<Core::Components::TransformComponent2D>(params.transform);
-  }
-
-  LOG_TRACE(
-      "[GameEntity] Checking TransformComponent2D is Initialized: [{}]",
-      static_cast<void*>(&this->transformComponent)
-  );
-
-  if (this->transformComponent == nullptr) {
-    this->transformComponent = make_unique<Core::Components::TransformComponent2D>(
-        Core::Math::Vector2D::Zero(), 0.0f, Core::Math::Size2D::Zero()
-    );
-  }
-}
-
-GameEntity::~GameEntity() {}
-
-void GameEntity::DebugUpdate() const
-{
-  EntityBase::DebugUpdate();
-}
-
-void GameEntity::DebugRender() const
-{
-  EntityBase::DebugRender();
-}
-
-void GameEntity::Update(const float deltaTime)
-{
-  EntityBase::Update(deltaTime);
-}
-
-void GameEntity::Initialize()
-{
-  EntityBase::Initialize();
-}
-
-Core::Components::TransformComponent2D& GameEntity::GetTransformComponent()
-{
-  return *this->transformComponent;
-}
-
-bool GameEntity::IsActive() const
-{
-  return EntityBase::IsActive();
-}
-
-void GameEntity::SetActive(const bool active)
-{
-  return EntityBase::SetActive(active);
-}
-
-const bool& GameEntity::GetActive()
-{
-  return EntityBase::GetActive();
-}
-
-}  // namespace Engine::Entity
diff --git a/src/engine/entity/game-entity.hpp b/src/engine/entity/game-entity.hpp
deleted file mode 100644
index b66f981..0000000
--- a/src/engine/entity/game-entity.hpp
+++ /dev/null
@@ -1,55 +0,0 @@
-//
-// Created by Dean Wilson on 25/8/2025.
-//
-
-#pragma once
-#include <memory>
-#include "core/entity/i-game-entity.hpp"
-#include "entity-base.hpp"
-#include "core/components/transform-component-2d.hpp"
-#include "core/math/i-transform-2d.hpp"
-
-namespace Core::Components {
-class IComponent;
-}
-
-namespace Engine::Entity {
-
-struct GameEntityParams : EntityBaseParams {
-  Core::Math::ITransform2D* transform = {nullptr};
-
-  GameEntityParams(Core::Math::ITransform2D* transform = nullptr, bool active = true)
-      : EntityBaseParams(active), transform(transform)
-  {
-  }
-};
-
-class GameEntity : public EntityBase, Core::Entity::IGameEntity {
- public:
-  explicit GameEntity(const GameEntityParams& params);
-
-  GameEntity(const GameEntity&) = delete;
-  GameEntity& operator=(const GameEntity&) = delete;
-
-  GameEntity(GameEntity&&) noexcept = delete;
-  GameEntity& operator=(GameEntity&&) noexcept = delete;
-
-  ~GameEntity() override;
-
-  virtual void Update(float deltaTime) override;
-  virtual void DebugUpdate() const override;
-  virtual void DebugRender() const override;
-  virtual void Initialize() override;
-  virtual Core::Components::TransformComponent2D& GetTransformComponent() override;
-
-  virtual bool IsActive() const override;
-  virtual void SetActive(bool active) override;
-  virtual const bool& GetActive() override;
-
-  // Properties
- protected:
-  // 1UP: Refactor location of TransformComponent2D so that it lives in engine and has an interface
-  // in Core
-  std::unique_ptr<Core::Components::TransformComponent2D> transformComponent{nullptr};
-};
-}  // namespace Engine::Entity
diff --git a/src/renderer-2d/components/render-component-2d.cpp b/src/renderer-2d/components/render-component-2d.cpp
index c8736dd..969e4dd 100644
--- a/src/renderer-2d/components/render-component-2d.cpp
+++ b/src/renderer-2d/components/render-component-2d.cpp
@@ -10,7 +10,7 @@
 namespace Renderer2D::Components {
 
 RenderComponent2D::RenderComponent2D(
-    Core::Math::ITransform2D& transform, const Core::Color::ColorRGBA color, bool& active
+    Core::Math::ITransform2D& transform, const Core::Color::ColorRGBA color, const bool& active
 )
     : transform(transform), color(color), active(active)
 {
@@ -45,7 +45,7 @@ float RenderComponent2D::GetHeight() const
 {
   return this->transform.GetScale().GetHeight();
 }
-bool RenderComponent2D::GetActive() const
+const bool& RenderComponent2D::GetActive() const
 {
   return this->active;
 }
diff --git a/src/renderer-2d/components/render-component-2d.hpp b/src/renderer-2d/components/render-component-2d.hpp
index 52af4b8..c17ac67 100644
--- a/src/renderer-2d/components/render-component-2d.hpp
+++ b/src/renderer-2d/components/render-component-2d.hpp
@@ -18,7 +18,7 @@ namespace Renderer2D::Components {
 class RenderComponent2D final : public Core::Rendering::Components::IRenderComponent2D {
  public:
   RenderComponent2D(
-      Core::Math::ITransform2D& transform, Core::Color::ColorRGBA color, bool& active
+      Core::Math::ITransform2D& transform, Core::Color::ColorRGBA color, const bool& active
   );
   ~RenderComponent2D() override = default;
   void Render(const Core::Rendering::IRenderer& renderer) const override;
@@ -26,11 +26,11 @@ class RenderComponent2D final : public Core::Rendering::Components::IRenderCompo
   [[nodiscard]] float GetY() const override;
   [[nodiscard]] float GetWidth() const override;
   [[nodiscard]] float GetHeight() const override;
-  [[nodiscard]] bool GetActive() const override;
+  [[nodiscard]] const bool& GetActive() const override;
 
  private:
   Core::Math::ITransform2D& transform;
   Core::Color::ColorRGBA color;
-  bool& active;
+  const bool& active;
 };
 }  // namespace Renderer2D::Components
diff --git a/src/snake-game/game-entities/apple.cpp b/src/snake-game/game-entities/apple.cpp
index cc92adf..b63d2da 100644
--- a/src/snake-game/game-entities/apple.cpp
+++ b/src/snake-game/game-entities/apple.cpp
@@ -1,6 +1,6 @@
 #include "apple.hpp"
 #include <memory>
-#include "engine/entity/game-entity.hpp"
+#include "engine/entities/entity.hpp"
 #include "core/color/color.hpp"
 #include "debug/debug.hpp"
 #include "physics/collision/components/collider-component-2d.hpp"
@@ -13,16 +13,14 @@
 
 namespace SnakeGame {
 
-Apple::Apple(const AppleParams& params) : Engine::Entity::GameEntity(params) {}
+Apple::Apple(const AppleParams& params) : Engine::Entities::Entity(params) {}
 
 void Apple::Initialize()
 {
-  GameEntity::Initialize();
-
   LOG_TRACE("[Apple] Initializing Apple from Constructor");
 
   this->transformComponent = make_unique<Core::Components::TransformComponent2D>(
-      this->GetNewPosition(), 0, Core::Math::Size2D(this->size)
+      Core::Math::Vector2D::Zero(), 0, Core::Math::Size2D(this->size)
   );
 
   LOG_TRACE(
@@ -53,7 +51,8 @@ void Apple::Initialize()
       static_cast<void*>(&this->colliderComponent)
   );
 
-  this->transformComponent->SetPosition(this->GetNewPosition());
+  // MAIN QUEST: This should be handled by the apple spawner
+  // this->transformComponent->SetPosition(this->GetNewPosition());
 };
 
 void Apple::Update([[maybe_unused]] const float deltaTime) {}
diff --git a/src/snake-game/game-entities/apple.hpp b/src/snake-game/game-entities/apple.hpp
index f7803ee..022da6b 100644
--- a/src/snake-game/game-entities/apple.hpp
+++ b/src/snake-game/game-entities/apple.hpp
@@ -2,9 +2,8 @@
 
 #include <memory>
 #include "core/math/i-transform-2d.hpp"
-#include "engine/entity/game-entity.hpp"
+#include "engine/entities/entity.hpp"
 #include "physics/collision/components/collider-component-2d.hpp"
-#include "core/math/vector-2d.hpp"
 #include "core/rendering/components/i-render-component-2d.hpp"
 
 namespace Core {
@@ -17,14 +16,16 @@ class IRenderComponent2D;
 
 namespace SnakeGame {
 
-struct AppleParams : Engine::Entity::GameEntityParams {
+struct AppleParams : Engine::Entities::EntityParams {
+  Core::Math::ITransform2D* transform{nullptr};
+
   AppleParams(Core::Math::ITransform2D* transform = nullptr, bool active = true)
-      : Engine::Entity::GameEntityParams(transform, active)
+      : Engine::Entities::EntityParams(transform, active)
   {
   }
 };
 
-class Apple final : public Engine::Entity::GameEntity {
+class Apple final : public Engine::Entities::Entity {
  public:
   explicit Apple(const AppleParams& params);
   void Update(float deltaTime) override;
diff --git a/src/snake-game/game-entities/snake-segment.hpp b/src/snake-game/game-entities/snake-segment.hpp
index aba752f..a1a7f3b 100644
--- a/src/snake-game/game-entities/snake-segment.hpp
+++ b/src/snake-game/game-entities/snake-segment.hpp
@@ -1,12 +1,11 @@
 #pragma once
 
 #include <memory>
-#include "engine/entity/game-entity.hpp"
+#include "engine/entities/entity.hpp"
 #include "core/rendering/components/i-render-component-2d.hpp"
 #include "core/math/vector-2d.hpp"
 #include "physics/collision/components/collider-component-2d.hpp"
 #include "core/math/i-transform-2d.hpp"
-#include "core/components/transform-component-2d.hpp"
 
 namespace Core::Components {
 class TransformComponent2D;
@@ -16,19 +15,19 @@ class ColliderComponent2D;
 }
 namespace SnakeGame {
 
-struct SnakeSegmentParams : Engine::Entity::GameEntityParams {
+struct SnakeSegmentParams : Engine::Entities::EntityParams {
   int index{0};
   Core::Math::ITransform2D& initialTransform;
 
   SnakeSegmentParams(int index, Core::Math::ITransform2D* transform, bool active = true)
-      : Engine::Entity::GameEntityParams(transform, active)
+      : Engine::Entities::EntityParams(transform, active)
       , index(index)
       , initialTransform(*transform)
   {
   }
 };
 
-class SnakeSegment final : public Engine::Entity::GameEntity {
+class SnakeSegment final : public Engine::Entities::Entity {
  public:
   // Properties
   int index = {0};
diff --git a/src/snake-game/game-scenes/gameplay-scene.cpp b/src/snake-game/game-scenes/gameplay-scene.cpp
index 6bfa85a..66053ac 100644
--- a/src/snake-game/game-scenes/gameplay-scene.cpp
+++ b/src/snake-game/game-scenes/gameplay-scene.cpp
@@ -1,6 +1,6 @@
-#include "gameplay-scene.hpp"
-#include "core/entity/game-entity-manager.hpp"
-#include "core/rendering/render-component-2d-manager.hpp"
+#include "snake-game/game-scenes/gameplay-scene.hpp"
+#include "engine/entities/entity-manager.hpp"
+#include "renderer-2d/render-component-2d-manager.hpp"
 
 namespace SnakeGame {
 
@@ -42,7 +42,7 @@ void GameplayScene::Update(float deltaTime)
 //         transition.Pop();   // returns to gameplay, same instance
 // }
 
-void GameplayScene::DebugUpdate() {}
-void GameplayScene::DebugRender() {}
+void GameplayScene::DebugUpdate() const {}
+void GameplayScene::DebugRender() const {}
 
 }  // namespace SnakeGame
diff --git a/src/snake-game/game-scenes/gameplay-scene.hpp b/src/snake-game/game-scenes/gameplay-scene.hpp
index 75920f6..67ae956 100644
--- a/src/snake-game/game-scenes/gameplay-scene.hpp
+++ b/src/snake-game/game-scenes/gameplay-scene.hpp
@@ -8,8 +8,9 @@
 #include "core/rendering/i-renderer.hpp"
 #include "renderer-2d/render-component-2d-manager.hpp"
 #include "snake-game/game-state/gameplay-state-machine.hpp"
-#include "engine/entity/game-entity-manager.hpp"
+#include "engine/entities/entity-manager.hpp"
 #include "core/events/i-event-bus.hpp"
+#include "core/scenes/scene-transition-context.hpp"
 
 namespace Core {
 
@@ -30,17 +31,17 @@ class GameplayScene : public Core::Scenes::IGameScene {
   GameplayScene(const GameplaySceneParams& params);
   ~GameplayScene();
   void Initialize() override;
-  void OnEnter(Core::SceneTransitionContext ctx) override;
+  void OnEnter(Core::Scenes::SceneTransitionContext ctx) override;
   void OnExit() override;
   void Update(float deltaTime) override;
   void OnRender(const Core::Rendering::IRenderer& renderer) const override;
-  void DebugUpdate() override;
-  void DebugRender() override;
+  void DebugUpdate() const override;
+  void DebugRender() const override;
 
  private:
-  Core::SceneTransitionContext transition;
-  Core::Rendering::RenderComponent2DManager renderComponentManager;
-  Core::GameEntityManager entityManager;
+  Core::Scenes::SceneTransitionContext transition;
+  Renderer2D::RenderComponent2DManager renderComponentManager;
+  Engine::Entities::EntityManager entityManager;
   GameplayStateMachine stateMachine;
   Core::Events::IEventBus& eventBus;
 };
diff --git a/src/snake-game/game-state/gameplay-state-machine.cpp b/src/snake-game/game-state/gameplay-state-machine.cpp
index cfd01b1..88bba23 100644
--- a/src/snake-game/game-state/gameplay-state-machine.cpp
+++ b/src/snake-game/game-state/gameplay-state-machine.cpp
@@ -1,9 +1,9 @@
 
 #include "gameplay-state-machine.hpp"
 #include "engine/state/state-machine.hpp"
-#include "engine/entity/game-entity-manager.hpp"
+#include "engine/entities/entity-manager.hpp"
 #include "gameplay-state.hpp"
-#include "main-menu-state.hpp"
+#include "snake-game/game-state/main-menu-state.hpp"
 #include "core/state/i-game-state.hpp"
 
 #include <memory>
@@ -24,30 +24,30 @@ GameplayStateMachine::~GameplayStateMachine() {}
 
 void GameplayStateMachine::Update(const float deltaTime)
 {
-  this->gameEntityManager->OnUpdate(deltaTime);
+  this->entityManager->OnUpdate(deltaTime);
 
   Core::State::StateMachine::Update(deltaTime);
 }
 
 void GameplayStateMachine::DebugUpdate() const
 {
-  if (this->gameEntityManager) {
-    this->gameEntityManager->OnDebugUpdate();
+  if (this->entityManager) {
+    this->entityManager->OnDebugUpdate();
   }
 }
 
 void GameplayStateMachine::DebugRender() const
 {
-  if (this->gameEntityManager) {
-    this->gameEntityManager->OnDebugRender();
+  if (this->entityManager) {
+    this->entityManager->OnDebugRender();
   }
 }
 
 void GameplayStateMachine::SetGameEntityManager(
-    std::shared_ptr<Engine::Entity::GameEntityManager> gameEntityManager
+    std::shared_ptr<Engine::Entities::EntityManager> entityManager
 )
 {
-  this->gameEntityManager = gameEntityManager;
+  this->entityManager = entityManager;
 }
 
 }  // namespace SnakeGame
diff --git a/src/snake-game/game-state/gameplay-state-machine.hpp b/src/snake-game/game-state/gameplay-state-machine.hpp
index 364e364..cf87b6e 100644
--- a/src/snake-game/game-state/gameplay-state-machine.hpp
+++ b/src/snake-game/game-state/gameplay-state-machine.hpp
@@ -1,5 +1,5 @@
 #pragma once
-#include "engine/entity/game-entity-manager.hpp"
+#include "engine/entities/entity-manager.hpp"
 #include "engine/state/state-machine.hpp"
 #include "core/state/i-game-state.hpp"
 #include "engine/input/input-system.hpp"
@@ -42,7 +42,7 @@ class GameplayStateMachine final : public Core::State::StateMachine {
   // Setters
   void SetSnake(Snake& snake);
   void SetApple(Apple& apple);
-  void SetGameEntityManager(std::shared_ptr<Engine::Entity::GameEntityManager> gameEntityManager);
+  void SetGameEntityManager(std::shared_ptr<Engine::Entities::EntityManager> gameEntityManager);
   void SetRenderer(Core::Rendering::IRenderer& renderer) { this->renderer = &renderer; }
   void SetRenderManager(Core::Rendering::RenderComponent2DManager& renderManager)
   {
@@ -53,7 +53,7 @@ class GameplayStateMachine final : public Core::State::StateMachine {
  private:
   GameContext gameContext;
   Core::Rendering::RenderComponent2DManager* renderManager = nullptr;
-  std::shared_ptr<Engine::Entity::GameEntityManager> gameEntityManager = nullptr;
+  std::shared_ptr<Engine::Entities::EntityManager> entityManager = nullptr;
   Core::Rendering::IRenderer* renderer = nullptr;
 };
 }  // namespace SnakeGame
diff --git a/src/snake-game/game-state/main-menu-state.hpp b/src/snake-game/game-state/main-menu-state.hpp
index 2579189..2f32310 100644
--- a/src/snake-game/game-state/main-menu-state.hpp
+++ b/src/snake-game/game-state/main-menu-state.hpp
@@ -19,7 +19,8 @@ class MainMenuState final : public Core::State::IGameState {
 
   void Enter() override;
   void Update([[maybe_unused]] float deltaTime) override;
-  void DebugUpdate() override;
+  void DebugUpdate() const override;
+  void DebugRender() const override;
   void Exit() override;
   std::unique_ptr<Core::State::IGameState> GetNextState() override;
 
diff --git a/src/snake-game/ui/main-menu-ui.hpp b/src/snake-game/ui/main-menu-ui.hpp
index b0c3223..76711f7 100644
--- a/src/snake-game/ui/main-menu-ui.hpp
+++ b/src/snake-game/ui/main-menu-ui.hpp
@@ -3,7 +3,7 @@
 //
 
 #pragma once
-#include "core/i-game-ui.hpp"
+#include "core/user-interface/i-game-ui.hpp"
 
 namespace UserInterface {
 class IUserInterface;
@@ -12,15 +12,18 @@ class IUserInterface;
 namespace SnakeGame {
 struct GameSettings;
 
-class MainMenuUI final : public Core::IGameUI {
+class MainMenuUI final : public Core::UserInterface::IGameUI {
  public:
   explicit MainMenuUI(UserInterface::IUserInterface& ui, GameSettings& settings);
   ~MainMenuUI() override;
 
-  void Render() override;
+  void OnDrawUI() override;
+  void OnDebugDrawUI() override;
+
   [[maybe_unused]] virtual void Update([[maybe_unused]] float deltaTime) override;
-  [[maybe_unused]] virtual void DebugRender() override;
-  [[maybe_unused]] virtual void DebugUpdate() override;
+  [[maybe_unused]] virtual void DebugRender() const override;
+  [[maybe_unused]] virtual void DebugUpdate() const override;
+  [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI& GetRenderComponentUI() const override;
 
  private:
   char scoreBuffer[100] = {0};
