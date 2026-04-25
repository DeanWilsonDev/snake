//
// Created by Dean Wilson on 2025/01/20
//

#include <firefly/log-registry.hpp>
#include "log.hpp"
#include <string>

namespace Umbra {
namespace Core {
namespace Logging {

void Log::Init(bool enableClientDebugLogging)
{
  Firefly::LogRegistry::RegisterLogger(CORE_LOGGER_NAME, true);
  Firefly::LogRegistry::RegisterLogger(CLIENT_LOGGER_NAME, enableClientDebugLogging);
}

void Log::Init(const std::string& fileName, bool enableClientDebugLogging)
{
  Firefly::LogRegistry::RegisterLogger(CORE_LOGGER_NAME, fileName, true);
  Firefly::LogRegistry::RegisterLogger(CLIENT_LOGGER_NAME, fileName, enableClientDebugLogging);
}
}  // namespace Logging
}  // namespace Core
}  // namespace Umbra
