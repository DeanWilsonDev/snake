//
// Created by Dean Wilson on 28/5/2025.
//

#ifndef IRENDERABLE_H
#define IRENDERABLE_H

class IDrawable {
public:
  virtual ~IDrawable() = default;
  virtual void Draw() = 0;
};
#endif //IRENDERABLE_H
