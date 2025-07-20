//
// Created by Dean Wilson on 12/7/2025.
//

#pragma once

namespace Engine::Config {

struct ProjectSettings {
 public:
  explicit ProjectSettings(const char* title):title(title){}
  [[nodiscard]] const char* GetTitle() const { return this->title; }

 private:
  const char* title = nullptr;
};

}  // namespace Engine::Config
