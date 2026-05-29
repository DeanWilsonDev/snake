#include "scene-manager.hpp"
#include "core/scenes/i-game-scene.hpp"
#include <vector>

using namespace Core::Scenes;

namespace Engine::Scenes {

void SceneManager::Register(
    const std::string& name, SceneFactory factory,
    SceneLifetime lifetime
)
{
  this->registry[name] = SceneEntry{std::move(factory), nullptr, lifetime};
}

void SceneManager::SwitchTo(const std::string& name)
{
  if (this->activeScene) {
    this->activeScene->OnExit();
  }

  // Transient Scenes release their instance on exit
  for (auto& [key, entry] : this->registry) {
    if (entry.instance.get() == activeScene &&
        entry.lifetime == SceneLifetime::Transient) {
      entry.instance.reset();
      break;
    }
  }

  this->activeScene = ResolveScene(name);
  this->activeScene->OnEnter(MakeContext());
}

void SceneManager::Push(const std::string& name)
{
  // Pause but don't exit the active scene
  if (this->activeScene) {
    this->overlayStack.push_back(activeScene);
  }
  this->activeScene = ResolveScene(name);
  this->activeScene->OnEnter(MakeContext());
}

void SceneManager::Pop()
{
  if (this->overlayStack.empty()) {
    return;
  }

  if (this->activeScene) {
    this->activeScene->OnExit();
  }

  // Release if Transient
  for (auto& [key, entry] : this->registry) {
    if (entry.instance.get() == this->activeScene &&
        entry.lifetime == SceneLifetime::Transient) {
      entry.instance.reset();
      break;
    }
  }

  activeScene = this->overlayStack.back();
  this->overlayStack.pop_back();
}

void SceneManager::OnUpdate(float deltaTime)
{
  if (this->activeScene) {
    this->activeScene->Update(deltaTime);
  }
}

void SceneManager::OnDebugUpdate() const
{
  if (this->activeScene) {
    this->activeScene->DebugUpdate();
  }
};

void SceneManager::OnDebugRender() const
{
  if (this->activeScene) {
    this->activeScene->DebugRender();
  }
};

void SceneManager::OnRender(const Core::Rendering::IRenderer& renderer) const
{
  if (this->activeScene) {
    this->activeScene->OnRender(renderer);
  }
}

IGameScene* SceneManager::ResolveScene(const std::string& name)
{
  auto it = registry.find(name);
  if (it == registry.end()) {
    throw std::runtime_error("Scene not registered: " + name);
  }

  auto& entry = it->second;

  if (!entry.instance) {
    entry.instance = entry.factory();
  }

  return entry.instance.get();
}

SceneTransitionContext SceneManager::MakeContext()
{
  return {
      .SwitchTo = [this](const std::string& name) { this->SwitchTo(name); },
      .Push = [this](const std::string& name) { this->Push(name); },
      .Pop = [this]() { this->Pop(); },
  };
}

}  // namespace Engine::Scenes
