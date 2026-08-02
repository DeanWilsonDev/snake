//
// Created by Dean Wilson 2nd August 2026
//

#pragma once

#include <vector>
#include <memory>

#include "core/entities/i-component-registrar.hpp"

namespace Core::Entities {

using EntityComponentRegistrars = std::vector<std::unique_ptr<Core::Entities::IComponentRegistrar>>;
}
