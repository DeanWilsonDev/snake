diff --git a/CMakeLists.txt b/CMakeLists.txt
index a684e12..ef3f4c4 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -58,13 +58,14 @@ add_executable(
   src/raylib-facade/core/raylib-core-facade.cpp
   src/physics/collision/components/collider-component-2d.cpp
   src/engine/dependency-injection/dependency-injector.cpp
-  src/engine/game/game.cpp
-  src/engine/entity/game-entity-manager.cpp
-  src/engine/entity/game-entity.cpp
-  src/engine/entity/entity-base.cpp
+  src/engine/entities/entity-manager.cpp
+  src/engine/entities/entity.cpp
   src/engine/state/state-machine.cpp
+  src/engine/scenes/scene-manager.cpp
+  src/engine/events/event-bus.cpp
   src/engine/ui/render-component-ui-manager.cpp
   src/debug/debug-hud.cpp
+  src/snake-game/snake-application.cpp
   src/snake-game/game-state/game-over-state.cpp
   src/snake-game/game-entities/apple.cpp
   src/snake-game/game-entities/snake-segment.cpp
@@ -72,6 +73,7 @@ add_executable(
   src/snake-game/game-state/gameplay-state-machine.cpp
   src/snake-game/game-state/gameplay-state.cpp
   src/snake-game/game-state/main-menu-state.cpp
+  src/snake-game/game-scenes/gameplay-scene.cpp
   src/snake-game/ui/game-over-ui.cpp
   src/snake-game/ui/main-menu-ui.cpp
   src/snake-game/ui/gameplay-ui.cpp)
@@ -107,7 +109,6 @@ endif()
 # -------------------------
 # Test executable
 # -------------------------
-option(SNAKE_BUILD_TESTS "Build tests" ON)
 
 if(SNAKE_BUILD_TESTS)
 
diff --git a/src/core/i-application-config.hpp b/src/core/application/i-application-config.hpp
similarity index 76%
rename from src/core/i-application-config.hpp
rename to src/core/application/i-application-config.hpp
index e68453f..66ebb02 100644
--- a/src/core/i-application-config.hpp
+++ b/src/core/application/i-application-config.hpp
@@ -8,6 +8,6 @@ namespace Core {
 
 struct IApplicationConfig {
  public:
-  virtual ~IDependencyInjector() = default;
+  virtual ~IApplicationConfig() = default;
 };
 }  // namespace Core
diff --git a/src/core/application/i-application.hpp b/src/core/application/i-application.hpp
new file mode 100644
index 0000000..face2d4
--- /dev/null
+++ b/src/core/application/i-application.hpp
@@ -0,0 +1,49 @@
+//
+// Created by Dean Wilson on 14/7/2025.
+//
+
+#pragma once
+
+#include "core/debug/i-on-debugable.hpp"
+#include "core/events/i-event-bus.hpp"
+#include "core/i-on-updatable.hpp"
+#include "core/rendering/i-on-renderable.hpp"
+#include "core/rendering/i-render-component-manager.hpp"
+#include "core/scenes/i-scene-manager.hpp"
+namespace Engine {
+namespace Config {
+struct ApplicationConfig;
+}
+}  // namespace Engine
+
+namespace Core {
+
+class IDependencyInjector;
+
+class IApplication : Core::Debug::IOnDebugable, Core::IOnUpdatable, Core::Rendering::IOnRenderable {
+ public:
+  virtual ~IApplication() = default;
+
+  virtual void Run() = 0;
+
+ protected:
+  // Called once to initialize application-specific systems and resources
+  virtual void Configure(Engine::Config::ApplicationConfig& config) = 0;
+  virtual void RegisterDependencies() = 0;
+  virtual const Engine::Config::ApplicationConfig& GetConfig() const = 0;
+  virtual Core::IDependencyInjector& GetInjector() const = 0;
+  virtual Core::Scenes::ISceneManager& GetSceneManager() const = 0;
+  virtual Core::Events::IEventBus& GetEventBus() const = 0;
+  virtual Core::Rendering::IRenderComponentManager& GetRenderComponentManager() const = 0;
+
+  virtual void Initialize() = 0;
+
+  // Called every frame to handle game-specific logic
+  virtual void OnUpdate(float deltaTime) override = 0;
+  virtual void OnDebugUpdate() const override = 0;
+  void OnRender(const Core::Rendering::IRenderer& renderer) const override = 0;
+  virtual void OnDebugRender() const override = 0;
+  virtual void Shutdown() = 0;
+};
+
+}  // namespace Core
diff --git a/src/core/color/color-hex.cpp b/src/core/color/color-hex.cpp
index 3b26d3c..f5622fd 100644
--- a/src/core/color/color-hex.cpp
+++ b/src/core/color/color-hex.cpp
@@ -6,12 +6,12 @@
 namespace Core {
 namespace Color {
 
-inline ColorRGBA ColorHex::ToRGBA()
+ColorRGBA ColorHex::ToRGBA()
 {
   return ColorRGBA::From(*this);
 };
 
-inline ColorHex ColorHex::From(const ColorRGBA& color)
+ColorHex ColorHex::From(const ColorRGBA& color)
 {
   return {
       static_cast<uint32_t>(color.red) << 24 | static_cast<uint32_t>(color.green) << 16 |
diff --git a/src/core/color/color-rgba.cpp b/src/core/color/color-rgba.cpp
index ab9b31f..d290560 100644
--- a/src/core/color/color-rgba.cpp
+++ b/src/core/color/color-rgba.cpp
@@ -10,7 +10,7 @@ ColorHex ColorRGBA::ToHex()
   return ColorHex::From(*this);
 }
 
-inline ColorRGBA ColorRGBA::From(const ColorHex& hex)
+ColorRGBA ColorRGBA::From(const ColorHex& hex)
 {
   return {
       static_cast<unsigned char>((hex.value >> 24) & 0xFF),
diff --git a/src/core/components/transform-component-2d.hpp b/src/core/components/transform-component-2d.hpp
index a996287..8cd0b6e 100644
--- a/src/core/components/transform-component-2d.hpp
+++ b/src/core/components/transform-component-2d.hpp
@@ -34,6 +34,10 @@ class TransformComponent2D final : public IComponent, public Math::ITransform2D
   [[nodiscard]] float& GetRotation() override { return this->rotation; };
   [[nodiscard]] Math::Size2D& GetScale() override { return this->scale; };
 
+  [[nodiscard]] const Math::Vector2D& GetPosition() const override { return this->position; }
+  [[nodiscard]] const float& GetRotation() const override { return this->rotation; };
+  [[nodiscard]] const Math::Size2D& GetScale() const override { return this->scale; };
+
   void SetPosition(const Math::Vector2D value) override { this->position = value; }
   void SetRotation(const float value) override { this->rotation = value; };
   void SetScale(const Math::Size2D& value) override { this->scale = value; };
diff --git a/src/debug/debug-node.hpp b/src/core/debug/debug-node.hpp
similarity index 95%
rename from src/debug/debug-node.hpp
rename to src/core/debug/debug-node.hpp
index 851d5fa..bdc65e7 100644
--- a/src/debug/debug-node.hpp
+++ b/src/core/debug/debug-node.hpp
@@ -4,9 +4,9 @@
 #include <unordered_map>
 #include <memory>
 #include <variant>
-#include <cstddef>
 #include "debug-value.hpp"
 
+namespace Core {
 namespace Debug {
 
 struct DebugNode;
@@ -26,3 +26,4 @@ struct DebugNode {
   const DebugMap* AsMap() const { return IsMap() ? &std::get<DebugMap>(data) : nullptr; }
 };
 }  // namespace Debug
+}  // namespace Core
diff --git a/src/debug/debug-value.hpp b/src/core/debug/debug-value.hpp
similarity index 96%
rename from src/debug/debug-value.hpp
rename to src/core/debug/debug-value.hpp
index 8c8572e..f30a45b 100644
--- a/src/debug/debug-value.hpp
+++ b/src/core/debug/debug-value.hpp
@@ -4,6 +4,7 @@
 #include <string>
 #include <memory.h>
 
+namespace Core {
 namespace Debug {
 
 struct DebugValue {
@@ -43,3 +44,4 @@ struct DebugValue {
   }
 };
 }  // namespace Debug
+}  // namespace Core
diff --git a/src/core/debug/i-debug-hud.hpp b/src/core/debug/i-debug-hud.hpp
index 56315a8..97d40d2 100644
--- a/src/core/debug/i-debug-hud.hpp
+++ b/src/core/debug/i-debug-hud.hpp
@@ -1,5 +1,7 @@
 #pragma once
 
+#include "debug-value.hpp"
+#include "debug-node.hpp"
 #include <format>
 #include <variant>
 #include <cstddef>
@@ -9,11 +11,6 @@
 #include <string_view>
 #include <functional>
 
-namespace Debug {
-struct DebugNode;
-struct DebugValue;
-}  // namespace Debug
-
 namespace Core {
 namespace Debug {
 
@@ -22,13 +19,12 @@ class IDebugHUD {
   virtual ~IDebugHUD() = default;
 
   virtual void Visit(
-      std::function<void(const std::string& key, const ::Debug::DebugNode& node, int depth)>
-          callback
+      std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
   ) const = 0;
 
   virtual void ClearFrameData() = 0;
 
-  virtual void Set(const std::string_view path, ::Debug::DebugValue value) = 0;
+  virtual void Set(const std::string_view path, DebugValue value) = 0;
 
   virtual void Remove(const std::string& path) = 0;
 
@@ -40,7 +36,37 @@ class IDebugHUD {
   void FormatPathAndSet(
       std::variant<int, size_t, float, std::string, bool> value,
       const std::format_string<Args...> format, Args&&... args
-  );
+  )
+  {
+    DebugValue debugValue{};
+    std::visit(
+        [&](const auto& x) {
+          using T = std::decay_t<decltype(x)>;
+          if constexpr (std::is_same_v<T, int>) {
+            debugValue = DebugValue::FromNumber(x);
+          }
+          if constexpr (std::is_same_v<T, size_t>) {
+            debugValue = DebugValue::FromNumber(x);
+          }
+          if constexpr (std::is_same_v<T, float>) {
+            debugValue = DebugValue::FromNumber(x);
+          }
+          if constexpr (std::is_same_v<T, double>) {
+            debugValue = DebugValue::FromNumber(x);
+          }
+          if constexpr (std::is_same_v<T, std::string>) {
+            debugValue = DebugValue::FromString(x);
+          }
+          if constexpr (std::is_same_v<T, bool>) {
+            debugValue = DebugValue::FromBool(x);
+          }
+        },
+        value
+    );
+
+    std::string path = std::format(format, std::forward<Args>(args)...);
+    this->Set(path, debugValue);
+  }
 };
 }  // namespace Debug
 }  // namespace Core
diff --git a/src/core/debug/i-debugable.hpp b/src/core/debug/i-debugable.hpp
index ba66705..542b743 100644
--- a/src/core/debug/i-debugable.hpp
+++ b/src/core/debug/i-debugable.hpp
@@ -21,8 +21,8 @@ namespace Debug {
 class IDebugable {
  public:
   virtual ~IDebugable() = default;
-  [[maybe_unused]] virtual void DebugUpdate() const {};
-  [[maybe_unused]] virtual void DebugRender() const {};
+  virtual void DebugUpdate() const = 0;
+  virtual void DebugRender() const = 0;
 };
 
 }  // namespace Debug
diff --git a/src/core/debug/i-on-debugable.hpp b/src/core/debug/i-on-debugable.hpp
index 649c9f3..d874eb5 100644
--- a/src/core/debug/i-on-debugable.hpp
+++ b/src/core/debug/i-on-debugable.hpp
@@ -21,8 +21,8 @@ namespace Debug {
 class IOnDebugable {
  public:
   virtual ~IOnDebugable() = default;
-  virtual void OnDebugUpdate() const;
-  virtual void OnDebugRender() const;
+  virtual void OnDebugUpdate() const = 0;
+  virtual void OnDebugRender() const = 0;
 };
 
 }  // namespace Debug
diff --git a/src/core/i-dependency-injector.hpp b/src/core/dependency-injection/i-dependency-injector.hpp
similarity index 98%
rename from src/core/i-dependency-injector.hpp
rename to src/core/dependency-injection/i-dependency-injector.hpp
index 3914863..71cbdb5 100644
--- a/src/core/i-dependency-injector.hpp
+++ b/src/core/dependency-injection/i-dependency-injector.hpp
@@ -43,7 +43,7 @@ class IDependencyInjector {
     return RegisterSingletonImplementation(typeid(TInterface), instance);
   }
 
-  virtual void Teardown();
+  virtual void Teardown() = 0;
 
   template <typename TInterface>
   void Unregister()
diff --git a/src/core/entities/i-entity.hpp b/src/core/entities/i-entity.hpp
index c851b10..39df808 100644
--- a/src/core/entities/i-entity.hpp
+++ b/src/core/entities/i-entity.hpp
@@ -18,7 +18,7 @@ namespace Entities {
 
 class IEntity : public Core::IUpdatable, public Core::Debug::IDebugable {
  public:
-  virtual ~IEntity() = 0;
+  virtual ~IEntity() = default;
 
   virtual void Initialize() = 0;
   virtual int GetID() const = 0;
@@ -26,6 +26,7 @@ class IEntity : public Core::IUpdatable, public Core::Debug::IDebugable {
   virtual void SetActive(bool active) = 0;
   virtual const bool& GetActive() const = 0;
   virtual Components::TransformComponent2D& GetTransformComponent() = 0;
+  virtual const Components::TransformComponent2D& GetTransformComponent() const = 0;
   virtual Core::Components::IComponent* GetComponentByType(std::type_index type) = 0;
   template <typename T>
   T* GetComponent()
diff --git a/src/core/i-application.hpp b/src/core/i-application.hpp
deleted file mode 100644
index b100930..0000000
--- a/src/core/i-application.hpp
+++ /dev/null
@@ -1,40 +0,0 @@
-//
-// Created by Dean Wilson on 14/7/2025.
-//
-
-#pragma once
-
-namespace Engine {
-namespace Config {
-struct ApplicationConfig;
-}
-}  // namespace Engine
-
-namespace Core {
-
-class IDependencyInjector;
-
-class IApplication {
- public:
-  virtual ~IApplication() = default;
-
-  virtual void Run() = 0;
-
- protected:
-  // Called once to initialize application-specific systems and resources
-  virtual void Configure(Engine::Config::ApplicationConfig& config) = 0;
-  virtual void RegisterDependencies() = 0;
-  virtual Engine::Config::ApplicationConfig& GetConfig() = 0;
-  virtual Core::IDependencyInjector& GetInjector() const = 0;
-
-  virtual void Initialize() = 0;
-
-  // Called every frame to handle game-specific logic
-  virtual void Update(float deltaTime) = 0;
-  virtual void DebugUpdate() = 0;
-  virtual void Render() = 0;
-  virtual void DebugRender() = 0;
-  virtual void Shutdown();
-};
-
-}  // namespace Core
diff --git a/src/core/i-on-updatable.hpp b/src/core/i-on-updatable.hpp
index 84355e7..58fb758 100644
--- a/src/core/i-on-updatable.hpp
+++ b/src/core/i-on-updatable.hpp
@@ -9,7 +9,7 @@ namespace Core {
 class IOnUpdatable {
  public:
   virtual ~IOnUpdatable() = default;
-  virtual void OnUpdate(float deltaTime);
+  virtual void OnUpdate(float deltaTime) = 0;
 };
 
 }  // namespace Core
diff --git a/src/core/i-updatable.hpp b/src/core/i-updatable.hpp
index ee4e33e..18acc54 100644
--- a/src/core/i-updatable.hpp
+++ b/src/core/i-updatable.hpp
@@ -9,7 +9,7 @@ namespace Core {
 class IUpdatable {
  public:
   virtual ~IUpdatable() = default;
-  [[maybe_unused]] virtual void Update([[maybe_unused]] float deltaTime) {};
+  virtual void Update(float deltaTime) = 0;
 };
 
 }  // namespace Core
diff --git a/src/core/math/i-transform-2d.hpp b/src/core/math/i-transform-2d.hpp
index 6b1102a..277c58a 100644
--- a/src/core/math/i-transform-2d.hpp
+++ b/src/core/math/i-transform-2d.hpp
@@ -9,12 +9,17 @@
 namespace Core::Math {
 
 class ITransform2D {
-public:
+ public:
   virtual ~ITransform2D() = default;
   virtual Vector2D& GetPosition() = 0;
   virtual float& GetRotation() = 0;
   virtual Size2D& GetScale() = 0;
-  virtual void SetPosition(const Math::Vector2D value) = 0; 
+
+  virtual const Vector2D& GetPosition() const = 0;
+  virtual const float& GetRotation() const = 0;
+  virtual const Size2D& GetScale() const = 0;
+
+  virtual void SetPosition(const Math::Vector2D value) = 0;
   virtual void SetRotation(const float value) = 0;
   virtual void SetScale(const Math::Size2D& value) = 0;
 };
diff --git a/src/core/math/transform-2d.hpp b/src/core/math/transform-2d.hpp
index 7d2269b..5faf924 100644
--- a/src/core/math/transform-2d.hpp
+++ b/src/core/math/transform-2d.hpp
@@ -39,6 +39,10 @@ struct Transform2D final : public ITransform2D {
   [[nodiscard]] Vector2D& GetPosition() override { return this->position; };
   [[nodiscard]] float& GetRotation() override { return this->rotation; };
   [[nodiscard]] Size2D& GetScale() override { return this->scale; };
+  
+  [[nodiscard]] const Vector2D& GetPosition() const override { return this->position; };
+  [[nodiscard]] const float& GetRotation() const override { return this->rotation; };
+  [[nodiscard]] const Size2D& GetScale() const override { return this->scale; };
 
   void SetPosition(const Math::Vector2D value) override { this->position = value; }
   void SetRotation(const float value) override { this->rotation = value; };
diff --git a/src/core/rendering/i-on-renderable.hpp b/src/core/rendering/i-on-renderable.hpp
index aa8aba9..b06f292 100644
--- a/src/core/rendering/i-on-renderable.hpp
+++ b/src/core/rendering/i-on-renderable.hpp
@@ -14,7 +14,7 @@ class IRenderer;
 
 class IOnRenderable {
  public:
-  virtual ~IOnRenderable() = 0;
+  virtual ~IOnRenderable() = default;
   virtual void OnRender(const IRenderer& renderer) const = 0;
 };
 }  // namespace Rendering
diff --git a/src/core/rendering/i-render-component-manager.hpp b/src/core/rendering/i-render-component-manager.hpp
index 672f577..3a258d9 100644
--- a/src/core/rendering/i-render-component-manager.hpp
+++ b/src/core/rendering/i-render-component-manager.hpp
@@ -17,7 +17,7 @@ class IRenderComponent2D;
 
 class IRenderComponentManager : public Core::Rendering::IRenderManager {
  public:
-  virtual ~IRenderComponentManager() = 0;
+  virtual ~IRenderComponentManager() = default;
   virtual void Register(Core::Rendering::Components::IRenderComponent* component) = 0;
   virtual void Unregister(Core::Rendering::Components::IRenderComponent* component) = 0;
   void OnRender(const Core::Rendering::IRenderer& renderer) const override = 0;
diff --git a/src/core/rendering/i-render-manager.hpp b/src/core/rendering/i-render-manager.hpp
index 7d4fdc5..4bf1e67 100644
--- a/src/core/rendering/i-render-manager.hpp
+++ b/src/core/rendering/i-render-manager.hpp
@@ -14,7 +14,7 @@ class IRenderer;
 
 class IRenderManager {
  public:
-  virtual ~IRenderManager() = 0;
+  virtual ~IRenderManager() = default;
   virtual void OnRender(const IRenderer& renderer) const = 0;
 };
 }  // namespace Rendering
diff --git a/src/core/rendering/i-renderable.hpp b/src/core/rendering/i-renderable.hpp
index 65daacc..ae669c5 100644
--- a/src/core/rendering/i-renderable.hpp
+++ b/src/core/rendering/i-renderable.hpp
@@ -14,7 +14,7 @@ class IRenderer;
 
 class IRenderable {
  public:
-  virtual ~IRenderable() = 0;
+  virtual ~IRenderable() = default;
   virtual void Render(const Rendering::IRenderer& renderer) const = 0;
 };
 }  // namespace Rendering
diff --git a/src/core/rendering/i-renderer.hpp b/src/core/rendering/i-renderer.hpp
index 5bc36e6..b51738a 100644
--- a/src/core/rendering/i-renderer.hpp
+++ b/src/core/rendering/i-renderer.hpp
@@ -8,9 +8,9 @@ class IRenderer {
  public:
   virtual ~IRenderer() = default;
 
-  void virtual BeginDrawing() = 0;
-  void virtual EndDrawing() = 0;
-  void virtual ClearBackground(Color::ColorRGBA color) = 0;
+  void virtual BeginDrawing() const = 0;
+  void virtual EndDrawing() const = 0;
+  void virtual ClearBackground(Color::ColorRGBA color) const = 0;
 
   // SIDE QUEST: Not sure if this one should be in here, we can come back to this
   void virtual DrawRectangle(float x, float y, float width, float height, Color::ColorRGBA) const = 0;
diff --git a/src/core/scenes/i-scene-manager.hpp b/src/core/scenes/i-scene-manager.hpp
index eb4f9b4..87c7098 100644
--- a/src/core/scenes/i-scene-manager.hpp
+++ b/src/core/scenes/i-scene-manager.hpp
@@ -7,7 +7,7 @@
 #include "core/i-on-updatable.hpp"
 #include "core/rendering/i-on-renderable.hpp"
 #include "core/scenes/scene-lifetime.hpp"
-#include "core/scenes/i-game-scene.hpp"
+#include "core/scenes/i-scene.hpp"
 #include <string>
 #include <functional>
 #include <memory>
@@ -15,11 +15,11 @@
 namespace Core {
 namespace Scenes {
 
-using SceneFactory = std::function<std::unique_ptr<IGameScene>()>;
+using SceneFactory = std::function<std::unique_ptr<IScene>()>;
 
-class ISceneManager : public Debug::IOnDebugable, IOnUpdatable, Rendering::IOnRenderable {
+class ISceneManager : public Debug::IOnDebugable, public IOnUpdatable, public Rendering::IOnRenderable {
  public:
-  virtual ~ISceneManager() = 0;
+  virtual ~ISceneManager() = default;
 
   virtual void Register(
       const std::string& name, SceneFactory factory,
@@ -28,11 +28,6 @@ class ISceneManager : public Debug::IOnDebugable, IOnUpdatable, Rendering::IOnRe
   virtual void SwitchTo(const std::string& name) = 0;
   virtual void Push(const std::string& name) = 0;
   virtual void Pop() = 0;
-
-  virtual void OnUpdate(float deltaTime) = 0;
-  virtual void OnDebugUpdate() const = 0;
-  virtual void OnDebugRender() const = 0;
-  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const = 0;
 };
 }  // namespace Scenes
 }  // namespace Core
diff --git a/src/core/scenes/i-game-scene.hpp b/src/core/scenes/i-scene.hpp
similarity index 52%
rename from src/core/scenes/i-game-scene.hpp
rename to src/core/scenes/i-scene.hpp
index bcdacc3..5beb411 100644
--- a/src/core/scenes/i-game-scene.hpp
+++ b/src/core/scenes/i-scene.hpp
@@ -7,27 +7,20 @@
 #include "core/debug/i-debugable.hpp"
 #include "core/i-updatable.hpp"
 #include "core/rendering/i-render-manager.hpp"
-#include "core/rendering/i-renderable.hpp"
 
 namespace Core {
 namespace Scenes {
 
 struct SceneTransitionContext;
 
-class IGameScene : public IUpdatable, Debug::IDebugable, Rendering::IRenderManager {
+class IScene: public IUpdatable, public Debug::IDebugable, public Rendering::IRenderManager {
  public:
-  virtual ~IGameScene() = default;
+  virtual ~IScene() = default;
 
   virtual void Initialize() = 0;
 
   virtual void OnEnter(SceneTransitionContext context) = 0;
   virtual void OnExit() = 0;
-
-  virtual void Update(float deltaTime) override = 0;
-  virtual void DebugUpdate() const override = 0;
-
-  virtual void OnRender(const Rendering::IRenderer& renderer) const override = 0;
-  virtual void DebugRender() const override = 0;
 };
 
 }  // namespace Scenes
diff --git a/src/core/user-interface/i-game-ui.hpp b/src/core/user-interface/i-game-ui.hpp
index c2791a4..295deb5 100644
--- a/src/core/user-interface/i-game-ui.hpp
+++ b/src/core/user-interface/i-game-ui.hpp
@@ -4,8 +4,6 @@
 
 #pragma once
 
-#include "core/debug/i-debugable.hpp"
-#include "core/i-updatable.hpp"
 #include "core/rendering/components/i-render-component-ui.hpp"
 
 namespace Core {
@@ -17,7 +15,7 @@ class IRenderComponentUI;
 }  // namespace Rendering
 
 namespace UserInterface {
-class IGameUI : public IUpdatable, public Debug::IDebugable {
+class IGameUI {
  public:
   virtual ~IGameUI() = default;
 
diff --git a/src/core/user-interface/user-interface-manager.cpp b/src/core/user-interface/user-interface-manager.cpp
index 56e08e3..634e157 100644
--- a/src/core/user-interface/user-interface-manager.cpp
+++ b/src/core/user-interface/user-interface-manager.cpp
@@ -23,15 +23,15 @@ void UserInterfaceManager::AddGameUI(std::unique_ptr<UserInterface::IGameUI> gam
   this->gameUIs.push_back(std::move(gameUI));
 }
 
-void UserInterfaceManager::OnUpdate(float deltaTime)
-{
-  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
-    if (!gameUI) {
-      continue;
-    }
-    gameUI->Update(deltaTime);
-  }
-}
+// void UserInterfaceManager::OnUpdate(float deltaTime)
+// {
+//   for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
+//     if (!gameUI) {
+//       continue;
+//     }
+//     gameUI->Update(deltaTime);
+//   }
+// }
 
 void UserInterfaceManager::DrawUI() const
 {
@@ -62,24 +62,25 @@ void UserInterfaceManager::OnRender(const Rendering::IRenderer& renderer) const
     gameUI->GetRenderComponentUI().Render(renderer);
   }
 }
-void UserInterfaceManager::OnDebugUpdate() const
-{
-  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
-    if (!gameUI) {
-      continue;
-    }
-    gameUI->DebugUpdate();
-  }
-}
 
-void UserInterfaceManager::OnDebugRender() const
-{
-  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
-    if (!gameUI) {
-      continue;
-    }
-    gameUI->DebugRender();
-  }
-}
+// void UserInterfaceManager::OnDebugUpdate() const
+// {
+//   for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
+//     if (!gameUI) {
+//       continue;
+//     }
+//     gameUI->DebugUpdate();
+//   }
+// }
+//
+// void UserInterfaceManager::OnDebugRender() const
+// {
+//   for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
+//     if (!gameUI) {
+//       continue;
+//     }
+//     gameUI->DebugRender();
+//   }
+// }
 
 }  // namespace Core::UserInterface
diff --git a/src/core/user-interface/user-interface-manager.hpp b/src/core/user-interface/user-interface-manager.hpp
index 7439f1e..2135ff7 100644
--- a/src/core/user-interface/user-interface-manager.hpp
+++ b/src/core/user-interface/user-interface-manager.hpp
@@ -3,9 +3,8 @@
 //
 #pragma once
 
+#include "core/rendering/i-render-component-manager.hpp"
 #include "core/user-interface/i-game-ui.hpp"
-#include "core/debug/i-on-debugable.hpp"
-#include "core/i-on-updatable.hpp"
 #include "core/rendering/i-render-manager.hpp"
 
 #include <string>
@@ -25,21 +24,22 @@ class IRenderer;
 namespace UserInterface {
 class IGameUI;
 
-class UserInterfaceManager final : public IOnUpdatable,
-                                   Debug::IOnDebugable,
-                                   Rendering::IRenderManager {
+class UserInterfaceManager final : Core::Rendering::IRenderManager {
  public:
   explicit UserInterfaceManager();
   ~UserInterfaceManager();
 
   [[nodiscard]] UserInterface::IGameUI* GetGameUIByName(std::string name) const;
   void AddGameUI(std::unique_ptr<UserInterface::IGameUI> gameUI);
-  void OnUpdate(float deltaTime) override;
   void DrawUI() const;
   void DebugDrawUI() const;
+
   void OnRender(const Rendering::IRenderer& renderer) const override;
-  void OnDebugUpdate() const override;
-  void OnDebugRender() const override;
+
+  // void OnUpdate(float deltaTime) override;
+  //
+  // void OnDebugUpdate() const override;
+  // void OnDebugRender() const override;
 
  private:
   std::vector<std::unique_ptr<UserInterface::IGameUI>> gameUIs;
diff --git a/src/debug/debug-hud.cpp b/src/debug/debug-hud.cpp
index 4820dd4..5b3d206 100644
--- a/src/debug/debug-hud.cpp
+++ b/src/debug/debug-hud.cpp
@@ -1,9 +1,8 @@
 #include "debug-hud.hpp"
-#include "debug-node.hpp"
-#include "debug-value.hpp"
+#include "core/debug/debug-node.hpp"
+#include "core/debug//debug-value.hpp"
 
 #include <string_view>
-// #include <fmtmsg.h>
 #include <functional>
 #include <memory>
 #include <utility>
diff --git a/src/debug/debug-hud.hpp b/src/debug/debug-hud.hpp
index 17821ee..afdb3dc 100644
--- a/src/debug/debug-hud.hpp
+++ b/src/debug/debug-hud.hpp
@@ -1,19 +1,15 @@
 #pragma once
 
-#include <format>
-#include <variant>
-#include <type_traits>
-#include <cstddef>
-#include <variant>
 #include <string>
 #include <string_view>
 #include <vector>
-#include <cstddef>
 #include <functional>
-#include "debug-node.hpp"
-#include "debug-value.hpp"
+#include "core/debug/debug-node.hpp"
+#include "core/debug/debug-value.hpp"
 #include "core/debug/i-debug-hud.hpp"
 
+using namespace Core::Debug;
+
 namespace Debug {
 
 class DebugHUD : public Core::Debug::IDebugHUD {
@@ -46,42 +42,6 @@ class DebugHUD : public Core::Debug::IDebugHUD {
   ) const;
 
   static void PrintNode(const std::string& key, DebugNode* node, int indent);
-
-  template <typename... Args>
-  void FormatPathAndSet(
-      std::variant<int, size_t, float, std::string, bool> value,
-      const std::format_string<Args...> format, Args&&... args
-  )
-  {
-    DebugValue debugValue{};
-    std::visit(
-        [&](const auto& x) {
-          using T = std::decay_t<decltype(x)>;
-          if constexpr (std::is_same_v<T, int>) {
-            debugValue = DebugValue::FromNumber(x);
-          }
-          if constexpr (std::is_same_v<T, size_t>) {
-            debugValue = DebugValue::FromNumber(x);
-          }
-          if constexpr (std::is_same_v<T, float>) {
-            debugValue = DebugValue::FromNumber(x);
-          }
-          if constexpr (std::is_same_v<T, double>) {
-            debugValue = DebugValue::FromNumber(x);
-          }
-          if constexpr (std::is_same_v<T, std::string>) {
-            debugValue = DebugValue::FromString(x);
-          }
-          if constexpr (std::is_same_v<T, bool>) {
-            debugValue = DebugValue::FromBool(x);
-          }
-        },
-        value
-    );
-
-    std::string path = std::format(format, std::forward<Args>(args)...);
-    this->Set(path, debugValue);
-  }
 };
 
 }  // namespace Debug
diff --git a/src/engine/application/application.cpp b/src/engine/application/application.cpp
index 1b21773..c014dcc 100644
--- a/src/engine/application/application.cpp
+++ b/src/engine/application/application.cpp
@@ -1,4 +1,5 @@
 #include "application.hpp"
+#include "core/rendering/i-render-component-manager.hpp"
 #include "core/scenes/i-scene-manager.hpp"
 #include "engine/config/project-settings.hpp"
 #include "core/color/color.hpp"
@@ -13,8 +14,9 @@
 #include "engine/scenes/scene-manager.hpp"
 #include "engine/utils/string-utils.hpp"
 #include "platform/input/i-input-backend.hpp"
+#include "renderer-2d/render-component-2d-manager.hpp"
 #include "user-interface/i-user-interface.hpp"
-#include "core/i-dependency-injector.hpp"
+#include "core/dependency-injection/i-dependency-injector.hpp"
 #include "core/logging/log.hpp"
 #include "core/state/i-state-machine.hpp"
 #include "core/events/i-event-bus.hpp"
@@ -42,6 +44,15 @@ Application::~Application() = default;
 
 void Application::Initialize()
 {
+
+  const auto& config = this->GetConfig();
+
+  const auto& debug = config.engine.debug;
+  Debug::System.SetDebugMode(debug.enabled);
+
+  LOG_INIT("log.csv", debug.enabled);
+
+
   LOG_CORE_TRACE("[Application] Initializing");
   this->window = this->injector->Resolve<Platform::Window::IWindow>();
   this->renderer = this->injector->Resolve<Core::Rendering::IRenderer>();
@@ -49,6 +60,8 @@ void Application::Initialize()
   this->input = this->injector->Resolve<Platform::Input::IInputBackend>();
   this->userInterface = this->injector->Resolve<UserInterface::IUserInterface>();
   this->eventBus = this->injector->Resolve<Core::Events::IEventBus>();
+  this->renderComponentManager =
+      this->injector->Resolve<Core::Rendering::IRenderComponentManager>();
   Debug::System.SetActiveDebugHUD(this->injector->Resolve<Core::Debug::IDebugHUD>());
 
   LOG_CORE_TRACE("[Application] Window set to {}", static_cast<void*>(&window));
@@ -67,12 +80,7 @@ void Application::Initialize()
   assert(this->userInterface);
   assert(this->eventBus);
 
-  const auto& config = this->GetConfig();
-
-  const auto& debug = config.engine.debug;
-  Debug::System.SetDebugMode(debug.enabled);
 
-  LOG_INIT("log.csv", debug.enabled);
 
   LOG_CORE_TRACE("[Application] Beginning Application");
   std::string title = config.project.title;
@@ -94,9 +102,8 @@ void Application::Initialize()
 
 void Application::RegisterDependencies()
 {
-
   // Raylib Dependencies as defaults:
-  
+
   // Platform
   this->GetInjector()
       .Register<Platform::Window::IWindow, RaylibFacade::Window::RaylibWindowFacade>();
@@ -114,7 +121,11 @@ void Application::RegisterDependencies()
       Core::UserInterface::IUserInterfaceManager,
       Core::UserInterface::UserInterfaceManager>();
 
-  // Scene Management 
+  // Rendering
+  injector
+      ->Register<Core::Rendering::IRenderComponentManager, Renderer2D::RenderComponent2DManager>();
+
+  // Scene Management
   injector->Register<Core::Scenes::ISceneManager, Engine::Scenes::SceneManager>();
 
   // Debug
@@ -143,13 +154,13 @@ void Application::Run()
     const float deltaTime = elapsedTime.count();
     lastTime = currentTime;
 
-    this->Update(deltaTime);
+    this->OnUpdate(deltaTime);
 
-    this->DebugUpdate();
+    this->OnDebugUpdate();
 
-    this->Render();
+    this->OnRender(*this->renderer);
 
-    this->DebugRender();
+    this->OnDebugRender();
 
     // FINISH:
     this->renderer->EndDrawing();
@@ -158,21 +169,49 @@ void Application::Run()
   this->injector->Teardown();
 }
 
-void Application::Update(float _) {}
+void Application::Configure(Config::ApplicationConfig&) {}
+void Application::OnUpdate(float) {}
 
-void Application::DebugUpdate() {}
+void Application::OnDebugUpdate() const {}
 
-void Application::Render()
+void Application::OnRender(const Core::Rendering::IRenderer& renderer) const
 {
   // RENDERING:
-  this->renderer->BeginDrawing();
-  this->renderer->ClearBackground(Core::Color::Black);
+  renderer.BeginDrawing();
+  renderer.ClearBackground(Core::Color::Black);
+  this->renderComponentManager->OnRender(renderer);
 }
-void Application::DebugRender() {}
+
+void Application::OnDebugRender() const {}
 
 void Application::Shutdown()
 {
   this->window->CloseWindow();
 }
 
+const Config::ApplicationConfig& Application::GetConfig() const
+{
+  return this->config;
+}
+
+Core::IDependencyInjector& Application::GetInjector() const
+{
+  return *this->injector;
+}
+
+Core::Scenes::ISceneManager& Application::GetSceneManager() const
+{
+  return *this->sceneManager;
+}
+
+Core::Events::IEventBus& Application::GetEventBus() const
+{
+  return *this->eventBus;
+}
+
+Core::Rendering::IRenderComponentManager& Application::GetRenderComponentManager() const
+{
+  return *this->renderComponentManager;
+}
+
 }  // namespace Engine
diff --git a/src/engine/application/application.hpp b/src/engine/application/application.hpp
index 678b8d6..d60dc6e 100644
--- a/src/engine/application/application.hpp
+++ b/src/engine/application/application.hpp
@@ -1,11 +1,12 @@
 #pragma once
 #include "core/events/i-event-bus.hpp"
-#include "core/i-application.hpp"
+#include "core/application/i-application.hpp"
+#include "core/rendering/i-render-component-manager.hpp"
 #include "core/scenes/i-scene-manager.hpp"
 #include "core/scenes/i-scene-manager.hpp"
 #include "debug/debug-hud.hpp"
 #include "engine/config/application-config.hpp"
-#include "core/i-dependency-injector.hpp"
+#include "core/dependency-injection/i-dependency-injector.hpp"
 #include "core/debug/i-debug-hud.hpp"
 
 // Main Quest: Move these to core
@@ -57,26 +58,29 @@ class Application : public Core::IApplication {
 
  protected:
   virtual void Initialize() override;
-  virtual void Configure(Config::ApplicationConfig& config) override;
   virtual void RegisterDependencies() override;
-  virtual void Update(float deltaTime) override;
-  virtual void DebugUpdate() override;
-  virtual void Render() override;
-  virtual void DebugRender() override;
+
+  virtual void Configure(Config::ApplicationConfig& config) override;
+  virtual void OnUpdate(float deltaTime) override;
+  virtual void OnDebugUpdate() const override;
+  virtual void OnDebugRender() const override;
+
+  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const override;
   virtual void Shutdown() override;
-  [[nodiscard]] virtual Config::ApplicationConfig& GetConfig() override { return this->config; };
-  [[nodiscard]] virtual Core::IDependencyInjector& GetInjector() const override
-  {
-    return *this->injector;
-  };
+  [[nodiscard]] virtual const Config::ApplicationConfig& GetConfig() const override;
+  [[nodiscard]] virtual Core::IDependencyInjector& GetInjector() const override;
+  [[nodiscard]] virtual Core::Scenes::ISceneManager& GetSceneManager() const override;
+  [[nodiscard]] virtual Core::Events::IEventBus& GetEventBus() const override;
+  [[nodiscard]] virtual Core::Rendering::IRenderComponentManager&
+  GetRenderComponentManager() const override;
 
  private:
   std::unique_ptr<Core::IDependencyInjector> injector;
   std::shared_ptr<Platform::Window::IWindow> window = nullptr;
   std::shared_ptr<Platform::Input::IInputBackend> input = nullptr;
-  std::shared_ptr<Core::Rendering::IRenderer> renderer = nullptr;
+  std::shared_ptr<const Core::Rendering::IRenderer> renderer = nullptr;
   std::shared_ptr<Core::Events::IEventBus> eventBus = nullptr;
-  std::shared_ptr<Core::Rendering::RenderComponent2DManager> renderComponent2dManager;
+  std::shared_ptr<Core::Rendering::IRenderComponentManager> renderComponentManager;
   Config::ApplicationConfig config;
 
   std::unique_ptr<Debug::DebugHUD> debugHUD;
diff --git a/src/engine/config/application-config.hpp b/src/engine/config/application-config.hpp
index 7a088dd..47449f8 100644
--- a/src/engine/config/application-config.hpp
+++ b/src/engine/config/application-config.hpp
@@ -7,12 +7,13 @@
 #include "engine/config/engine-config.hpp"
 #include "engine/config/project-settings.hpp"
 #include "engine/config/game-settings.hpp"
+#include <memory>
 
 namespace Engine::Config {
 
 struct ApplicationConfig {
   EngineConfig engine;
   ProjectSettings project;
-  GameSettings game;
+  std::unique_ptr<GameSettings> game;
 };
 }  // namespace Engine::Config
diff --git a/src/engine/config/game-settings.hpp b/src/engine/config/game-settings.hpp
index 4fc6244..fd34254 100644
--- a/src/engine/config/game-settings.hpp
+++ b/src/engine/config/game-settings.hpp
@@ -6,6 +6,7 @@
 
 namespace Engine::Config {
 struct GameSettings {
+  virtual ~GameSettings() = default;
   struct DebugConfig {
     bool enabled;
     bool showDebugLogs;
diff --git a/src/engine/dependency-injection/dependency-injector.hpp b/src/engine/dependency-injection/dependency-injector.hpp
index 9783192..46e4f20 100644
--- a/src/engine/dependency-injection/dependency-injector.hpp
+++ b/src/engine/dependency-injection/dependency-injector.hpp
@@ -4,7 +4,7 @@
 
 #pragma once
 
-#include "core/i-dependency-injector.hpp"
+#include "core/dependency-injection/i-dependency-injector.hpp"
 
 #include <typeindex>
 #include <any>
diff --git a/src/engine/entities/entity-manager.cpp b/src/engine/entities/entity-manager.cpp
index 9c35626..bb16e10 100644
--- a/src/engine/entities/entity-manager.cpp
+++ b/src/engine/entities/entity-manager.cpp
@@ -19,6 +19,12 @@ EntityManager::EntityManager(Core::Rendering::IRenderComponentManager* renderMan
 
 void EntityManager::AddEntity(Core::Entities::IEntity* entity)
 {
+  // SIDE QUEST: Entity Component Pipeline
+  // AddEntity should only register entities. The engine should handle component
+  // routing automatically via a ComponentDispatcher that inspects each entity's
+  // components on registration and forwards them to the appropriate subsystems
+  // (e.g. IRenderComponent -> RenderComponent2DManager). Scenes stay declarative.
+
   if (!entity) {
     return;
   }
diff --git a/src/engine/entities/entity.cpp b/src/engine/entities/entity.cpp
index dd9463c..17c9042 100644
--- a/src/engine/entities/entity.cpp
+++ b/src/engine/entities/entity.cpp
@@ -32,14 +32,6 @@ Entity::Entity(const EntityParams& params) : active(params.active)
 
 Entity::~Entity() = default;
 
-void Entity::Initialize() {}
-
-void Entity::Update([[maybe_unused]] float deltaTime) {}
-
-void Entity::DebugUpdate() const {}
-
-void Entity::DebugRender() const {}
-
 int Entity::GetID() const
 {
   return this->id;
@@ -73,4 +65,19 @@ Core::Components::IComponent* Entity::GetComponentByType(std::type_index type)
   return nullptr;
 }
 
+Core::Components::TransformComponent2D& Entity::GetTransformComponent()
+{
+  return *this->transformComponent;
+};
+
+const Core::Components::TransformComponent2D& Entity::GetTransformComponent() const
+{
+  return *this->transformComponent;
+};
+
+void Entity::Initialize() {}
+void Entity::Update(float) {}
+void Entity::DebugUpdate() const {}
+void Entity::DebugRender() const {}
+
 }  // namespace Engine::Entities
diff --git a/src/engine/entities/entity.hpp b/src/engine/entities/entity.hpp
index b00d626..9c3a10e 100644
--- a/src/engine/entities/entity.hpp
+++ b/src/engine/entities/entity.hpp
@@ -36,10 +36,10 @@ class Entity : public Core::Entities::IEntity {
   explicit Entity(const EntityParams& params);
   virtual ~Entity() = 0;
 
-  virtual void Initialize() override;
-  virtual void Update([[maybe_unused]] float deltaTime) override;
+  virtual void Update(float deltaTime) override;
   virtual void DebugUpdate() const override;
   virtual void DebugRender() const override;
+  virtual void Initialize() override;
   virtual int GetID() const override;
   virtual bool IsActive() const override;
   virtual void SetActive(bool active) override;
@@ -53,6 +53,7 @@ class Entity : public Core::Entities::IEntity {
   void RemoveComponent();
 
   virtual Core::Components::TransformComponent2D& GetTransformComponent() override;
+  virtual const Core::Components::TransformComponent2D& GetTransformComponent() const override;
 
   // Properties
  protected:
diff --git a/src/engine/entry-point.hpp b/src/engine/entry-point.hpp
index 1a4adba..683179d 100644
--- a/src/engine/entry-point.hpp
+++ b/src/engine/entry-point.hpp
@@ -1,6 +1,6 @@
 #pragma once
 
-#include "core/i-application.hpp"
+#include "core/application/i-application.hpp"
 
 extern Core::IApplication* CreateApplication();
 
diff --git a/src/engine/scenes/scene-manager.cpp b/src/engine/scenes/scene-manager.cpp
index d58c853..608e386 100644
--- a/src/engine/scenes/scene-manager.cpp
+++ b/src/engine/scenes/scene-manager.cpp
@@ -1,15 +1,14 @@
 #include "scene-manager.hpp"
-#include "core/scenes/i-game-scene.hpp"
+#include "core/scenes/i-scene.hpp"
 #include <vector>
 
 using namespace Core::Scenes;
 
 namespace Engine::Scenes {
 
-void SceneManager::Register(
-    const std::string& name, SceneFactory factory,
-    SceneLifetime lifetime
-)
+SceneManager::SceneManager() {}
+
+void SceneManager::Register(const std::string& name, SceneFactory factory, SceneLifetime lifetime)
 {
   this->registry[name] = SceneEntry{std::move(factory), nullptr, lifetime};
 }
@@ -22,8 +21,7 @@ void SceneManager::SwitchTo(const std::string& name)
 
   // Transient Scenes release their instance on exit
   for (auto& [key, entry] : this->registry) {
-    if (entry.instance.get() == activeScene &&
-        entry.lifetime == SceneLifetime::Transient) {
+    if (entry.instance.get() == activeScene && entry.lifetime == SceneLifetime::Transient) {
       entry.instance.reset();
       break;
     }
@@ -55,8 +53,7 @@ void SceneManager::Pop()
 
   // Release if Transient
   for (auto& [key, entry] : this->registry) {
-    if (entry.instance.get() == this->activeScene &&
-        entry.lifetime == SceneLifetime::Transient) {
+    if (entry.instance.get() == this->activeScene && entry.lifetime == SceneLifetime::Transient) {
       entry.instance.reset();
       break;
     }
@@ -94,7 +91,7 @@ void SceneManager::OnRender(const Core::Rendering::IRenderer& renderer) const
   }
 }
 
-IGameScene* SceneManager::ResolveScene(const std::string& name)
+IScene* SceneManager::ResolveScene(const std::string& name)
 {
   auto it = registry.find(name);
   if (it == registry.end()) {
@@ -118,5 +115,4 @@ SceneTransitionContext SceneManager::MakeContext()
       .Pop = [this]() { this->Pop(); },
   };
 }
-
 }  // namespace Engine::Scenes
diff --git a/src/engine/scenes/scene-manager.hpp b/src/engine/scenes/scene-manager.hpp
index 35d0df0..780be51 100644
--- a/src/engine/scenes/scene-manager.hpp
+++ b/src/engine/scenes/scene-manager.hpp
@@ -4,7 +4,7 @@
 
 #pragma once
 
-#include "core/scenes/i-game-scene.hpp"
+#include "core/scenes/i-scene.hpp"
 #include "core/scenes/scene-lifetime.hpp"
 #include "core/scenes/i-scene-manager.hpp"
 #include "core/rendering/i-renderer.hpp"
@@ -49,16 +49,16 @@ class SceneManager : public ISceneManager {
  private:
   struct SceneEntry {
     SceneFactory factory;
-    std::unique_ptr<IGameScene> instance;
+    std::unique_ptr<IScene> instance;
     SceneLifetime lifetime;
   };
 
-  IGameScene* ResolveScene(const std::string& name);
+  IScene* ResolveScene(const std::string& name);
   SceneTransitionContext MakeContext();
 
   std::unordered_map<std::string, SceneEntry> registry;
-  IGameScene* activeScene = nullptr;
-  std::vector<IGameScene*> overlayStack;
+  IScene* activeScene = nullptr;
+  std::vector<IScene*> overlayStack;
 };
 
 }  // namespace Scenes
diff --git a/src/engine/state/state-machine.cpp b/src/engine/state/state-machine.cpp
index c8c06b8..bed69d9 100644
--- a/src/engine/state/state-machine.cpp
+++ b/src/engine/state/state-machine.cpp
@@ -33,7 +33,6 @@ void StateMachine::Update(float deltaTime)
   this->currentState->Update(deltaTime);
 };
 
-void StateMachine::DebugUpdate() {}
 
 IGameState& StateMachine::GetCurrentState()
 {
diff --git a/src/engine/state/state-machine.hpp b/src/engine/state/state-machine.hpp
index 4e858a5..1563d7b 100644
--- a/src/engine/state/state-machine.hpp
+++ b/src/engine/state/state-machine.hpp
@@ -17,8 +17,6 @@ class StateMachine : public IStateMachine {
   StateMachine(std::unique_ptr<IGameState> currentState);
   ~StateMachine() = default;
   virtual void Update(float deltaTime) override;
-  virtual void DebugUpdate() const override;
-  virtual void DebugRender() const override;
   void ChangeState(std::unique_ptr<IGameState> newState) override;
   [[nodiscard]] IGameState& GetCurrentState() override;
 
diff --git a/src/raylib-facade/renderer/raylib-renderer-facade.cpp b/src/raylib-facade/renderer/raylib-renderer-facade.cpp
index 2579acd..0323367 100644
--- a/src/raylib-facade/renderer/raylib-renderer-facade.cpp
+++ b/src/raylib-facade/renderer/raylib-renderer-facade.cpp
@@ -11,21 +11,21 @@ RaylibRendererFacade::RaylibRendererFacade()
 }
 RaylibRendererFacade::~RaylibRendererFacade() = default;
 
-void RaylibRendererFacade::BeginDrawing()
+void RaylibRendererFacade::BeginDrawing() const
 {
   return ::BeginDrawing();
 }
-void RaylibRendererFacade::EndDrawing()
+void RaylibRendererFacade::EndDrawing() const
 {
   return ::EndDrawing();
 }
 
-void RaylibRendererFacade::ClearBackground(const Core::Color::ColorRGBA color)
+void RaylibRendererFacade::ClearBackground(const Core::Color::ColorRGBA color) const
 {
   return ::ClearBackground(ConvertToRaylibColor(color));
 }
 
-Color RaylibRendererFacade::ConvertToRaylibColor(const Core::Color::ColorRGBA color)
+Color RaylibRendererFacade::ConvertToRaylibColor(const Core::Color::ColorRGBA color) 
 {
   return Color(color.red, color.green, color.blue, color.alpha);
 }
diff --git a/src/raylib-facade/renderer/raylib-renderer-facade.hpp b/src/raylib-facade/renderer/raylib-renderer-facade.hpp
index 38db8dc..94d958a 100644
--- a/src/raylib-facade/renderer/raylib-renderer-facade.hpp
+++ b/src/raylib-facade/renderer/raylib-renderer-facade.hpp
@@ -18,11 +18,14 @@ class RaylibRendererFacade final : public Core::Rendering::IRenderer {
   explicit RaylibRendererFacade();
   ~RaylibRendererFacade() override;
 
-  void BeginDrawing() override;
-  void EndDrawing() override;
-  void ClearBackground(Core::Color::ColorRGBA color) override;
+  void BeginDrawing() const override;
+  void EndDrawing() const override;
+  void ClearBackground(Core::Color::ColorRGBA color) const override;
+
+  void DrawRectangle(
+      float x, float y, float width, float height, Core::Color::ColorRGBA
+  ) const override;
 
-  void DrawRectangle(float x, float y, float width, float height, Core::Color::ColorRGBA) const override;
   static Color ConvertToRaylibColor(Core::Color::ColorRGBA color);
 };
 }  // namespace RaylibFacade::Renderer
diff --git a/src/raylib-facade/user-interface/raylib-user-interface-facade.cpp b/src/raylib-facade/user-interface/raylib-user-interface-facade.cpp
index f0947a8..9bbf3d7 100644
--- a/src/raylib-facade/user-interface/raylib-user-interface-facade.cpp
+++ b/src/raylib-facade/user-interface/raylib-user-interface-facade.cpp
@@ -1,6 +1,6 @@
 #include "raylib-user-interface-facade.hpp"
 #include "core/debug/i-debug-hud.hpp"
-#include "debug/debug-node.hpp"
+#include "core/debug/debug-node.hpp"
 #include "raylib.h"
 #include "core/logging/log.hpp"
 #include <string>
@@ -25,7 +25,7 @@ void RaylibUserInterfaceFacade::RenderDebugHUD(const Core::Debug::IDebugHUD& deb
 {
   int y = 10;
   int lineCount = 0;
-  debugHUD.Visit([&](const std::string&, const Debug::DebugNode&, int) { lineCount++; });
+  debugHUD.Visit([&](const std::string&, const Core::Debug::DebugNode&, int) { lineCount++; });
 
   int lineHeight = 20;
   int bgX = 0;
@@ -37,7 +37,7 @@ void RaylibUserInterfaceFacade::RenderDebugHUD(const Core::Debug::IDebugHUD& deb
 
   DrawRectangle(bgX, bgY, bgWidth, bgHeight, bgColor);
 
-  debugHUD.Visit([&](const std::string& key, const Debug::DebugNode& node, int depth) {
+  debugHUD.Visit([&](const std::string& key, const Core::Debug::DebugNode& node, int depth) {
     int x = 10 + depth * 20;
 
     if (node.IsValue()) {
diff --git a/src/renderer-2d/render-component-2d-manager.cpp b/src/renderer-2d/render-component-2d-manager.cpp
index c4a7966..e34b7f6 100644
--- a/src/renderer-2d/render-component-2d-manager.cpp
+++ b/src/renderer-2d/render-component-2d-manager.cpp
@@ -39,10 +39,6 @@ void RenderComponent2DManager::OnRender(const Core::Rendering::IRenderer& render
   }
 
   for (Core::Rendering::Components::IRenderComponent* component : this->renderComponents) {
-    if (!dynamic_cast<Core::Rendering::Components::IRenderComponent2D*>(component)) {
-      continue;
-    }
-
     if (component->GetActive()) {
       component->Render(renderer);
     }
diff --git a/src/snake-game/game-entities/snake-segment.cpp b/src/snake-game/game-entities/snake-segment.cpp
index a7a90c3..349299b 100644
--- a/src/snake-game/game-entities/snake-segment.cpp
+++ b/src/snake-game/game-entities/snake-segment.cpp
@@ -1,12 +1,10 @@
 #include "physics/collision/rectangle-collider-2d.hpp"
 #include "snake-game/game-entities/snake-segment.hpp"
 #include "snake.hpp"
-#include "core/logging/log.hpp"
 #include <memory>
 #include "debug/debug.hpp"
 #include "physics/collision/components/collider-component-2d.hpp"
-#include "game/game-objects/snake-segment.hpp"
-#include "core/entity/game-entity.hpp"
+#include "core/entities/i-entity.hpp"
 #include "core/color/color.hpp"
 #include "core/math/vector-2d.hpp"
 #include "renderer-2d/components/render-component-2d.hpp"
@@ -15,8 +13,7 @@
 
 namespace SnakeGame {
 
-SnakeSegment::SnakeSegment(const SnakeSegmentParams& params)
-    : GameEntity(params), index(params.index)
+SnakeSegment::SnakeSegment(const SnakeSegmentParams& params) : Entity(params), index(params.index)
 {
   this->transformComponent =
       make_unique<Core::Components::TransformComponent2D>(&params.initialTransform);
@@ -41,15 +38,8 @@ void SnakeSegment::Move(const Core::Math::Vector2D newPosition)
   this->GetTransformComponent().GetPosition().y = newPosition.y;
 }
 
-void SnakeSegment::Update(float deltaTime)
-{
-  Engine::Entity::GameEntity::Update(deltaTime);
-}
-void SnakeSegment::Initialize() {}
-
 void SnakeSegment::DebugUpdate() const
 {
-  Engine::Entity::GameEntity::DebugUpdate();
   if (index == 0) {
     UMBRA_DEBUG(this->GetActive(), "Snake/Segment-{}/Active", this->index);
 
diff --git a/src/snake-game/game-entities/snake-segment.hpp b/src/snake-game/game-entities/snake-segment.hpp
index a1a7f3b..4685c1b 100644
--- a/src/snake-game/game-entities/snake-segment.hpp
+++ b/src/snake-game/game-entities/snake-segment.hpp
@@ -37,9 +37,6 @@ class SnakeSegment final : public Engine::Entities::Entity {
   ~SnakeSegment() override;
 
   void DebugUpdate() const override;
-  void DebugRender() const override;
-  virtual void Update(float deltaTime) override;
-  virtual void Initialize() override;
 
   [[nodiscard]] Core::Rendering::Components::IRenderComponent2D& GetRendererComponent2D()
   {
diff --git a/src/snake-game/game-entities/snake.cpp b/src/snake-game/game-entities/snake.cpp
index c5d3035..bf4ef7d 100644
--- a/src/snake-game/game-entities/snake.cpp
+++ b/src/snake-game/game-entities/snake.cpp
@@ -1,8 +1,9 @@
 #include "snake-game/game-entities/snake.hpp"
-#include "snake-game/settings/game-settings.hpp"
+#include "snake-game/settings/snake-game-settings.hpp"
 #include "snake-segment.hpp"
 #include "core/math/vector-2d.hpp"
 #include "core/math/transform-2d.hpp"
+#include "core/components/transform-component-2d.hpp"
 
 #include <cmath>
 #include <memory>
@@ -11,17 +12,19 @@ namespace SnakeGame {
 
 Snake::~Snake() = default;
 
-Snake::Snake(const SnakeParams& snakeParams) : settings(snakeParams.settings)
+Snake::Snake(const SnakeParams& snakeParams)
+    : settings(snakeParams.settings)
+    , screenWidth(snakeParams.screenWidth)
+    , screenHeight(snakeParams.screenHeight)
 {
-  auto snakeSize = static_cast<float>(settings.GetBoxSize());
+  auto snakeSize = static_cast<float>(settings.boxSize);
 
   this->transform = Core::Math::Transform2D({100.f, 100.0f}, 0, {snakeSize, snakeSize});
 }
 
 Snake* Snake::Initialize()
 {
-  this->size = static_cast<float>(this->settings.GetBoxSize());
-
+  this->size = static_cast<float>(this->settings.boxSize);
   this->speed = this->size * 5.0f;
   this->length = this->settings.defaultSnakeLength;
   this->direction = {1.0f, 0.0f};
@@ -110,29 +113,32 @@ void Snake::CheckIfShouldGrow()
 
 void Snake::Teleport() const
 {
-  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());
-  const auto screenHeight = static_cast<float>(this->settings.GetScreenHeight());
+  // SIDE QUEST: BoundaryWrapSystem
+  // Wrapping behaviour should be handled by a dedicated BoundaryWrapSystem in the
+  // game-systems layer rather than the Snake querying screen dimensions directly.
+  // Snake should have no knowledge of screen bounds — the system takes a list of
+  // entities and wraps their positions if they exceed the boundary.
 
   for (auto& segment : this->body) {
     auto& segmentPosition = segment->GetTransformComponent().GetPosition();
-    if (segmentPosition.x > screenWidth) {
+    if (segmentPosition.x > this->screenWidth) {
       segmentPosition.x = 0;
     }
     else if (segmentPosition.x < 0) {
-      segmentPosition.x = screenWidth;
+      segmentPosition.x = this->screenWidth;
     }
-    else if (segmentPosition.y > screenHeight) {
+    else if (segmentPosition.y > this->screenHeight) {
       segmentPosition.y = 0;
     }
     else if (segmentPosition.y < 0) {
-      segmentPosition.y = screenHeight;
+      segmentPosition.y = this->screenHeight;
     }
   }
 }
 
 Core::Math::Vector2D Snake::GetCenter() const
 {
-  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
+  const auto boxSize = static_cast<float>(this->settings.boxSize);
   return {
       this->head->GetTransformComponent().GetPosition().x + boxSize / 2.0f,
       this->head->GetTransformComponent().GetPosition().y + boxSize / 2.0f,
diff --git a/src/snake-game/game-entities/snake.hpp b/src/snake-game/game-entities/snake.hpp
index e07a790..136a5e5 100644
--- a/src/snake-game/game-entities/snake.hpp
+++ b/src/snake-game/game-entities/snake.hpp
@@ -22,7 +22,9 @@ class SnakeSegment;
 struct SnakeGameSettings;
 
 struct SnakeParams {
-  SnakeGameSettings& settings;
+  const SnakeGameSettings& settings;
+  int screenWidth;
+  int screenHeight;
 };
 
 class Snake final {
@@ -44,13 +46,15 @@ class Snake final {
   void SetActive(bool enabled) const;
   void SetDirection(Core::Math::Vector2D direction);
 
-  [[nodiscard]] SnakeGameSettings& GetSnakeGameSettings() const { return this->settings; }
+  [[nodiscard]] const SnakeGameSettings& GetSnakeGameSettings() const { return this->settings; }
 
   SnakeSegment* head{};
   std::deque<std::unique_ptr<SnakeSegment>> body;
 
  private:
-  SnakeGameSettings& settings;
+  const SnakeGameSettings& settings;
+  int screenWidth;
+  int screenHeight;
   float accumulatedDistance = 0.0f;
   bool directionChanged = false;
   float size = {0};
diff --git a/src/snake-game/game-scenes/gameplay-scene.cpp b/src/snake-game/game-scenes/gameplay-scene.cpp
index 66053ac..3b67aa0 100644
--- a/src/snake-game/game-scenes/gameplay-scene.cpp
+++ b/src/snake-game/game-scenes/gameplay-scene.cpp
@@ -1,17 +1,56 @@
 #include "snake-game/game-scenes/gameplay-scene.hpp"
+#include "snake-game/game-entities/apple.hpp"
+#include "snake-game/game-entities/snake.hpp"
+#include "snake-game/settings/snake-game-settings.hpp"
+#include "snake-game/game-entities/snake-segment.hpp"
+#include "snake-game/game-entities/apple.hpp"
+#include "core/math/transform-2d.hpp"
 #include "engine/entities/entity-manager.hpp"
-#include "renderer-2d/render-component-2d-manager.hpp"
 
 namespace SnakeGame {
 
 GameplayScene::GameplayScene(const GameplaySceneParams& params)
-    : renderComponentManager()
+    : renderComponentManager(params.renderComponentManager)
     , entityManager(&this->renderComponentManager)
-    , eventBus(*params.eventBus)
+    , eventBus(params.eventBus)
+    , gameSettings(params.gameSettings)
+    , screenWidth(params.screenWidth)
+    , screenHeight(params.screenHeight)
 {
 }
 
-void GameplayScene::Initialize() {}
+GameplayScene::~GameplayScene() = default;
+
+void GameplayScene::Initialize()
+{
+  // Register Snake:
+
+  SnakeParams snakeParams = {
+      .settings = this->gameSettings,
+      .screenWidth = this->screenWidth,
+      .screenHeight = this->screenHeight
+  };
+
+  auto snake = new Snake(snakeParams);
+  snake->Initialize();
+
+  this->entityManager.AddEntity(snake->head);
+
+  for (auto& segment : snake->body) {
+    this->entityManager.AddEntity(segment.get());
+  }
+
+  // Register Apple
+
+  auto appleTransform =
+      new Core::Math::Transform2D(Core::Math::Vector2D::Zero(), 0, Core::Math::Size2D::Zero());
+
+  AppleParams appleParams = AppleParams(appleTransform);
+
+  auto apple = new Apple(appleParams);
+
+  this->entityManager.AddEntity(apple);
+}
 
 // GameplayScene.cpp
 void GameplayScene::OnEnter(Core::Scenes::SceneTransitionContext ctx)
@@ -22,8 +61,11 @@ void GameplayScene::OnEnter(Core::Scenes::SceneTransitionContext ctx)
 
 void GameplayScene::Update(float deltaTime)
 {
-  stateMachine.Update(deltaTime);
-  entityManager.OnUpdate(deltaTime);
+  // SIDE QUEST: This should probably just be handled in application.
+  // I'm going to need to find an itelligent way to handle update priority
+  // and decide what should update in what order
+  this->stateMachine.Update(deltaTime);
+  this->entityManager.OnUpdate(deltaTime);
 
   // if (stateMachine.IsGameOver()) transition.SwitchTo("mainMenu");
 }
@@ -42,6 +84,9 @@ void GameplayScene::Update(float deltaTime)
 //         transition.Pop();   // returns to gameplay, same instance
 // }
 
+void GameplayScene::OnExit() {}
+void GameplayScene::OnRender(const Core::Rendering::IRenderer&) const {}
+
 void GameplayScene::DebugUpdate() const {}
 void GameplayScene::DebugRender() const {}
 
diff --git a/src/snake-game/game-scenes/gameplay-scene.hpp b/src/snake-game/game-scenes/gameplay-scene.hpp
index 67ae956..1f21de9 100644
--- a/src/snake-game/game-scenes/gameplay-scene.hpp
+++ b/src/snake-game/game-scenes/gameplay-scene.hpp
@@ -4,13 +4,16 @@
 
 #pragma once
 
-#include "core/scenes/i-game-scene.hpp"
+#include "core/rendering/i-render-component-manager.hpp"
+#include "core/scenes/i-scene.hpp"
 #include "core/rendering/i-renderer.hpp"
+#include "snake-game/settings/snake-game-settings.hpp"
 #include "renderer-2d/render-component-2d-manager.hpp"
 #include "snake-game/game-state/gameplay-state-machine.hpp"
 #include "engine/entities/entity-manager.hpp"
 #include "core/events/i-event-bus.hpp"
 #include "core/scenes/scene-transition-context.hpp"
+#include "snake-game/settings/snake-game-settings.hpp"
 
 namespace Core {
 
@@ -23,10 +26,14 @@ namespace SnakeGame {
 class GameplayStateMachine;
 
 struct GameplaySceneParams {
-  Core::Events::IEventBus* eventBus;
+  Core::Events::IEventBus& eventBus;
+  Core::Rendering::IRenderComponentManager& renderComponentManager;
+  const SnakeGameSettings& gameSettings;
+  int screenWidth;
+  int screenHeight;
 };
 
-class GameplayScene : public Core::Scenes::IGameScene {
+class GameplayScene : public Core::Scenes::IScene {
  public:
   GameplayScene(const GameplaySceneParams& params);
   ~GameplayScene();
@@ -40,9 +47,12 @@ class GameplayScene : public Core::Scenes::IGameScene {
 
  private:
   Core::Scenes::SceneTransitionContext transition;
-  Renderer2D::RenderComponent2DManager renderComponentManager;
+  Core::Rendering::IRenderComponentManager& renderComponentManager;
   Engine::Entities::EntityManager entityManager;
   GameplayStateMachine stateMachine;
   Core::Events::IEventBus& eventBus;
+  const SnakeGameSettings& gameSettings;
+  int screenWidth;
+  int screenHeight;
 };
 }  // namespace SnakeGame
diff --git a/src/snake-game/game-state/gameplay-state.cpp b/src/snake-game/game-state/gameplay-state.cpp
index e378b1a..15f7c2a 100644
--- a/src/snake-game/game-state/gameplay-state.cpp
+++ b/src/snake-game/game-state/gameplay-state.cpp
@@ -21,31 +21,7 @@ class IRenderer;
 
 namespace SnakeGame {
 
-GameplayState::GameplayState(GameContext& gameContext) : gameContext(gameContext)
-{
-  // Initialize Snake
-  LOG_TRACE("[GameplayState] Setting up Snake GameObject");
-  const auto snakeParams = SnakeParams{.settings = *gameContext.settings};
-  this->snake = make_unique<Snake>(snakeParams);
-  LOG_DEBUG("[GameplayState] Snake set to [{}]", static_cast<void*>(&snake));
-  this->snake->Initialize();
-
-  //
-  // Initialize Apple
-  //
-
-  AppleParams appleParams = AppleParams(*gameContext.settings);
-  LOG_TRACE("[Game] Setting up Apple GameObject");
-  this->apple = make_unique<Apple>(appleParams);
-  LOG_DEBUG("[Game] Apple set to [{}]", static_cast<void*>(&this->apple));
-
-  // const auto userInterface = this->gameplayStateMachine.GetUserInterface();
-  // gameContext.gameUI = std::make_unique<GameplayUI>(this->gameContext);
-
-  // assert(gameSettings);
-  // assert(userInterface);
-  // this->gameplayUI = new GameplayUI(*userInterface, *gameSettings, score);
-}
+GameplayState::GameplayState(GameContext& gameContext) : gameContext(gameContext) {}
 
 void GameplayState::Enter()
 {
@@ -71,6 +47,11 @@ void GameplayState::Enter()
 
 void GameplayState::Update(float)
 {
+  // MAIN QUEST: Wire input to event bus
+  // Input polling should be replaced with event-driven input. The input system
+  // publishes InputActionEvents onto the event bus when actions are pressed.
+  // Entities and systems subscribe to those events rather than polling directly.
+  // See Engine::Events::IEventBus and Engine::Input::Action for existing pieces.
   if (this->gameContext.input->IsActionPressed(Engine::Input::Action::MoveLeft)) {
     this->snake->SetDirection({-1.0f, 0.0f});
   }
@@ -89,7 +70,8 @@ void GameplayState::Update(float)
           this->apple->GetColliderComponent().GetCollider().GetWorldRect()
       )) {
     LOG_DEBUG("[GameplayState] Snake got the Apple!");
-    this->apple->GetTransformComponent().SetPosition(this->apple->GetNewPosition());
+
+    // this->apple->GetTransformComponent().SetPosition(this->apple->GetNewPosition());
 
     this->gameContext.score += 10;
 
diff --git a/src/snake-game/game-state/main-menu-state.cpp b/src/snake-game/game-state/main-menu-state.cpp
index a5a868f..fdc5ea6 100644
--- a/src/snake-game/game-state/main-menu-state.cpp
+++ b/src/snake-game/game-state/main-menu-state.cpp
@@ -34,6 +34,7 @@ void MainMenuState::Update(float)
 }
 
 void MainMenuState::DebugUpdate() const {}
+void MainMenuState::DebugRender() const {}
 
 void MainMenuState::Exit()
 {
diff --git a/src/snake-game/settings/snake-game-settings.hpp b/src/snake-game/settings/snake-game-settings.hpp
index 85d413d..fb6a111 100644
--- a/src/snake-game/settings/snake-game-settings.hpp
+++ b/src/snake-game/settings/snake-game-settings.hpp
@@ -1,9 +1,7 @@
 #pragma once
 
 #include "engine/config/game-settings.hpp"
-
 #include "core/logging/log.hpp"
-#include <algorithm>
 
 inline constexpr int DefaultBoxSize = 20;
 inline constexpr int DefaultMinBoxSize = 10;
@@ -25,15 +23,16 @@ struct SnakeGameSettings : public Engine::Config::GameSettings {
   int gridWidth = GridColumns;
   int gridHeight = GridRows;
   int defaultSnakeLength = DefaultSnakeLength;
+  int boxSize = DefaultBoxSize;
 
-  [[nodiscard]] int GetBoxSize(int screenWidth, int screenHeight) const
-  {
-    return std::clamp(
-        std::min(screenWidth / this->gridWidth, screenHeight / this->gridHeight),
-        this->minBoxSize,
-        this->maxBoxSize
-    );
-  }
+  // [[nodiscard]] int GetBoxSize(int screenWidth, int screenHeight) const
+  // {
+  //   return std::clamp(
+  //       std::min(screenWidth / this->gridWidth, screenHeight / this->gridHeight),
+  //       this->minBoxSize,
+  //       this->maxBoxSize
+  //   );
+  // }
 
   void Print() const
   {
@@ -50,6 +49,5 @@ struct SnakeGameSettings : public Engine::Config::GameSettings {
   }
 
  private:
-  int boxSize = DefaultBoxSize;
 };
 }  // namespace SnakeGame
diff --git a/src/snake-game/snake-application.cpp b/src/snake-game/snake-application.cpp
index 1520c9a..8b21c74 100644
--- a/src/snake-game/snake-application.cpp
+++ b/src/snake-game/snake-application.cpp
@@ -1,22 +1,24 @@
 #include "snake-application.hpp"
+#include "core/scenes/scene-lifetime.hpp"
 #include "engine/application/application.hpp"
-#include "engine/input/key-code.hpp"
-#include "snake-game/game-state/gameplay-state-machine.hpp"
+#include "core/scenes/scene-lifetime.hpp"
 #include "engine/config/application-config.hpp"
+#include "snake-game/settings/snake-game-settings.hpp"
+#include "snake-game/game-scenes/gameplay-scene.hpp"
+#include <assert.h>
+#include <memory>
 #include <vector>
 
-using KeyCode = Engine::Input::KeyCode;
-
 namespace SnakeGame {
 
-void SnakeApplication::Initialize()
-{
-  Engine::Application::Initialize();
-}
-
 // 1UP: this could just deserialise a json config file. Amanuensis?
 void SnakeApplication::Configure(Engine::Config::ApplicationConfig& config)
 {
+  auto snakeSettings = std::make_unique<SnakeGameSettings>();
+
+  snakeSettings->debug.enabled = false;
+  snakeSettings->debug.showDebugLogs = false;
+
   config = {
       .engine =
           {.window =
@@ -40,21 +42,48 @@ void SnakeApplication::Configure(Engine::Config::ApplicationConfig& config)
                    .showDebugLogs = false,  // Show Core Logging
                }},
       .project = {.title = "Snake"},
-      .game = {.debug{
-          .enabled = false,        // Turn on all Debug options
-          .showDebugLogs = false,  // Show Game Related Logging
-      }}
+      .game = std::move(snakeSettings)
+  };
+}
+
+void SnakeApplication::Initialize()
+{
+  Engine::Application::Initialize();
+
+  GameplaySceneParams gameplaySceneParams = {
+      .eventBus = this->GetEventBus(),
+      .renderComponentManager = this->GetRenderComponentManager(),
+      .gameSettings = this->GetSnakeSettings(),
+      .screenWidth = this->GetConfig().engine.window.GetScreenWidth(),
+      .screenHeight = this->GetConfig().engine.window.GetScreenHeight(),
   };
+
+  this->GetSceneManager().Register(
+      "Gameplay",
+      [gameplaySceneParams]() { return std::make_unique<GameplayScene>(gameplaySceneParams); },
+      Core::Scenes::SceneLifetime::Transient
+  );
+
+  // this->GetSceneManager().Register(
+  //     "MainMenu",
+  //     Engine::Scenes::SceneManager::MakeSceneFactory<MainMenuScene>(),
+  //     SceneLifetime::Transient
+  // );
 }
 
 void SnakeApplication::RegisterDependencies()
 {
   Engine::Application::RegisterDependencies();
 
+  ///
+  /// Register overrides and game-specific dependencies below
+  ///
+}
 
-  // Game
-  this->GetInjector().Register<Core::State::IStateMachine, SnakeGame::GameplayStateMachine>();
-
+const SnakeGame::SnakeGameSettings& SnakeApplication::GetSnakeSettings() const
+{
+  assert(dynamic_cast<SnakeGame::SnakeGameSettings*>(this->GetConfig().game.get()));
+  return static_cast<SnakeGame::SnakeGameSettings&>(*this->GetConfig().game);
 }
 
 }  // namespace SnakeGame
diff --git a/src/snake-game/snake-application.hpp b/src/snake-game/snake-application.hpp
index 781af60..6e324fc 100644
--- a/src/snake-game/snake-application.hpp
+++ b/src/snake-game/snake-application.hpp
@@ -14,6 +14,8 @@ namespace Config {
 }  // namespace Core
 
 namespace SnakeGame {
+struct SnakeGameSettings;
+
 class SnakeApplication : public Engine::Application {
  public:
   SnakeApplication() : Application() {};
@@ -21,5 +23,7 @@ class SnakeApplication : public Engine::Application {
   virtual void Initialize() override;
   virtual void Configure(Engine::Config::ApplicationConfig& config) override;
   virtual void RegisterDependencies() override;
+  [[nodiscard]] const SnakeGameSettings& GetSnakeSettings() const;
 };
+
 }  // namespace SnakeGame
diff --git a/src/snake-game/ui/game-over-ui.cpp b/src/snake-game/ui/game-over-ui.cpp
index 0112a26..fc9058d 100644
--- a/src/snake-game/ui/game-over-ui.cpp
+++ b/src/snake-game/ui/game-over-ui.cpp
@@ -5,26 +5,25 @@
 #include "game-over-ui.hpp"
 
 #include "core/math/vector-2d.hpp"
-#include "game/settings/game-settings.hpp"
 #include "user-interface/i-user-interface.hpp"
 #include <cstdio>
 
 namespace SnakeGame {
 
-GameOverUI::GameOverUI(UserInterface::IUserInterface& ui, GameSettings& settings, int& score)
-    : ui(ui), settings(settings), score(score)
+GameOverUI::GameOverUI(
+    UserInterface::IUserInterface& ui, int screenWidth, int screenHeight, int& score
+)
+    : ui(ui), screenWidth(screenWidth), screenHeight(screenHeight), score(score)
 {
 }
 
 void GameOverUI::OnDrawUI()
 {
-  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());
-
-  this->ui.DrawTextCentered("Game Over", {screenWidth / 2.0f - 40, 40}, 80);
-  this->ui.DrawTextCentered("Press 'Enter' to start", {screenWidth / 2.0f, 200.0f}, 20);
+  this->ui.DrawTextCentered("Game Over", {this->screenWidth / 2.0f - 40, 40}, 80);
+  this->ui.DrawTextCentered("Press 'Enter' to start", {this->screenWidth / 2.0f, 200.0f}, 20);
 
   std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", this->score);
-  this->ui.DrawTextCentered(this->scoreBuffer, {screenWidth / 2.0f, 150.0f}, 20);
+  this->ui.DrawTextCentered(this->scoreBuffer, {this->screenWidth / 2.0f, 150.0f}, 20);
 };
 
 }  // namespace SnakeGame
diff --git a/src/snake-game/ui/game-over-ui.hpp b/src/snake-game/ui/game-over-ui.hpp
index 5db4851..90a9fd5 100644
--- a/src/snake-game/ui/game-over-ui.hpp
+++ b/src/snake-game/ui/game-over-ui.hpp
@@ -14,7 +14,9 @@ namespace SnakeGame {
 struct GameSettings;
 class GameOverUI final : public Core::UserInterface::IGameUI {
  public:
-  explicit GameOverUI(UserInterface::IUserInterface& ui, GameSettings& settings, int& score);
+  explicit GameOverUI(
+      UserInterface::IUserInterface& ui, int screenWidth, int screenHeight, int& score
+  );
   virtual ~GameOverUI() override {};
   virtual void OnDrawUI() override;
 
@@ -27,7 +29,8 @@ class GameOverUI final : public Core::UserInterface::IGameUI {
  private:
   std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> renderComponent;
   UserInterface::IUserInterface& ui;
-  GameSettings& settings;
+  int screenWidth;
+  int screenHeight;
   int& score;
   char scoreBuffer[100] = {0};
 };
diff --git a/src/snake-game/ui/gameplay-ui.cpp b/src/snake-game/ui/gameplay-ui.cpp
index 6c77865..30bc511 100644
--- a/src/snake-game/ui/gameplay-ui.cpp
+++ b/src/snake-game/ui/gameplay-ui.cpp
@@ -15,9 +15,9 @@ GameplayUI::GameplayUI(GameContext& gameContext) : gameContext(gameContext) {}
 
 void GameplayUI::OnDrawUI()
 {
-  const auto textPosition = Core::Math::Vector2D{80.f, 30.f};
-  constexpr int fontSize = 20;
-  std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->gameContext.score);
+  // const auto textPosition = Core::Math::Vector2D{80.f, 30.f};
+  // constexpr int fontSize = 20;
+  // std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->gameContext.score);
 
   // MAIN QUEST: Change how this works so that the GameUI can simply layout the UI how it wants and
   // have the engine handle everything else 
diff --git a/src/snake-game/ui/main-menu-ui.cpp b/src/snake-game/ui/main-menu-ui.cpp
index 957e1f3..5c445e1 100644
--- a/src/snake-game/ui/main-menu-ui.cpp
+++ b/src/snake-game/ui/main-menu-ui.cpp
@@ -5,24 +5,30 @@
 #include "main-menu-ui.hpp"
 
 #include "core/math/vector-2d.hpp"
-#include "game/settings/game-settings.hpp"
 #include "user-interface/i-user-interface.hpp"
 
 namespace SnakeGame {
 
-MainMenuUI::MainMenuUI(UserInterface::IUserInterface& ui, GameSettings& settings)
-    : settings(settings), ui(ui)
+MainMenuUI::MainMenuUI(UserInterface::IUserInterface& ui, int screenWidth, int screenHeight)
+    : ui(ui), screenWidth(screenWidth), screenHeight(screenHeight)
 {
 }
+
 MainMenuUI::~MainMenuUI() = default;
 
-void MainMenuUI::Render()
-{
-  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());
+void MainMenuUI::OnDebugDrawUI() {}
 
+void MainMenuUI::OnDrawUI()
+{
   this->ui.DrawTextCentered("Snake", Core::Math::Vector2D{screenWidth / 2.0f, 40.0f}, 80);
   this->ui.DrawTextCentered(
       "Press 'Enter' to start", Core::Math::Vector2D{screenWidth / 2.0f, 200.0f}, 20
   );
 }
-}  // namespace Snake
+
+Core::Rendering::Components::IRenderComponentUI& MainMenuUI::GetRenderComponentUI() const
+{
+  return *this->renderComponent;
+}
+
+}  // namespace SnakeGame
diff --git a/src/snake-game/ui/main-menu-ui.hpp b/src/snake-game/ui/main-menu-ui.hpp
index 0ab8832..a4acacf 100644
--- a/src/snake-game/ui/main-menu-ui.hpp
+++ b/src/snake-game/ui/main-menu-ui.hpp
@@ -4,6 +4,7 @@
 
 #pragma once
 #include "core/user-interface/i-game-ui.hpp"
+#include <memory>
 
 namespace UserInterface {
 class IUserInterface;
@@ -14,22 +15,20 @@ struct GameSettings;
 
 class MainMenuUI final : public Core::UserInterface::IGameUI {
  public:
-  explicit MainMenuUI(UserInterface::IUserInterface& ui, GameSettings& settings);
+  explicit MainMenuUI(UserInterface::IUserInterface& ui, int screenWidth, int screenHeight);
   ~MainMenuUI() override;
 
   void OnDrawUI() override;
   void OnDebugDrawUI() override;
 
-  [[maybe_unused]] virtual void Update([[maybe_unused]] float deltaTime) override;
-  [[maybe_unused]] virtual void DebugRender() const override;
-  [[maybe_unused]] virtual void DebugUpdate() const override;
   [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI&
   GetRenderComponentUI() const override;
 
  private:
-  char scoreBuffer[100] = {0};
-  GameSettings& settings;
   UserInterface::IUserInterface& ui;
+  std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> renderComponent;
+  int screenWidth;
+  int screenHeight;
 };
 
 }  // namespace SnakeGame
