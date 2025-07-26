//
// Created by Dean Wilson on 12/7/2025.
//

#include "dependency-injector.hpp"

#include "log.h"

#include <core.h>

namespace Core {

DependencyInjector::~DependencyInjector()
{
  Teardown();
}


void DependencyInjector::Teardown()
{
  instances.clear();
  factories.clear();
}


}  // namespace Core