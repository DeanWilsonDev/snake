//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once

namespace UserInterface {

class IGameUI {
 public:
  virtual ~IGameUI() = default;
  virtual void Render() = 0;
};

}  // namespace UserInterface
