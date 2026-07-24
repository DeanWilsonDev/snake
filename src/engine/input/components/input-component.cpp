//
// Created by Dean Wilson 24th July 2026
//

#include "input-component.hpp"
#include "core/input/action-router.hpp"
#include <cassert>

namespace Engine::Input::Components {

InputComponent::InputComponent() {};

void InputComponent::Bind(const std::string& name, std::function<void()> callback)
{
  assert(this->router && "InputComponent::Bind called before AttachRouter. bind in BeginPlay()");
  this->handles.push_back(this->router->Bind(name, std::move(callback)));
};

void InputComponent::BindAxis(
    const std::string& name, std::function<void(Core::Input::ActionValue)> callback, float threshold
)
{
  assert(this->router && "InputComponent::Bind called before AttachRouter. bind in BeginPlay()");
  this->handles.push_back(this->router->BindAxis(name, std::move(callback), threshold));
};

void InputComponent::AttachRouter(Core::Input::ActionRouter& attachedRouter)
{
  this->router = &attachedRouter;
}

}  // namespace Engine::Input::Components
