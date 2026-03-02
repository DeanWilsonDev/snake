//
// Created by Dean Wilson on 12/7/2025.
//

#include "dependency-injector.hpp"

namespace Engine {

DependencyInjector::~DependencyInjector()
{
  Teardown();
}

void DependencyInjector::Teardown()
{
  instances.clear();
  factories.clear();
}

}  // namespace Engine
