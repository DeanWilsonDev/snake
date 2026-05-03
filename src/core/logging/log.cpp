//
// Created by Dean Wilson on 2025/01/20
//

#include "log.hpp"
#include "adapters/firefly-logger-adapter.hpp"
#include "firefly/log-registry.hpp"
#

namespace Core {
namespace Logging {

constexpr std::string CORE_LOGGER_NAME = "Umbra";
constexpr std::string CLIENT_LOGGER_NAME = "Client";

static std::unique_ptr<ILogger> coreLogger;
static std::unique_ptr<ILogger> clientLogger;

void Log::Init(bool enableClientDebugLogging)
{
  Firefly::LogRegistry::RegisterLogger(CORE_LOGGER_NAME, true);
  Firefly::LogRegistry::RegisterLogger(CLIENT_LOGGER_NAME, enableClientDebugLogging);

  coreLogger = std::make_unique<FireflyLoggerAdapter>(Firefly::LogRegistry::GetLogger(CORE_LOGGER_NAME));
  clientLogger = std::make_unique<FireflyLoggerAdapter>(Firefly::LogRegistry::GetLogger(CLIENT_LOGGER_NAME));
}

void Log::Init(const std::string& fileName, bool enableClientDebugLogging)
{
  Firefly::LogRegistry::RegisterLogger(CORE_LOGGER_NAME, fileName, true);
  Firefly::LogRegistry::RegisterLogger(CLIENT_LOGGER_NAME, fileName, enableClientDebugLogging);

  coreLogger = std::make_unique<FireflyLoggerAdapter>(Firefly::LogRegistry::GetLogger(CORE_LOGGER_NAME));
  clientLogger = std::make_unique<FireflyLoggerAdapter>(Firefly::LogRegistry::GetLogger(CLIENT_LOGGER_NAME));
}


ILogger& Log::GetCoreLogger() { return *coreLogger; }
ILogger& Log::GetClientLogger() { return *clientLogger; }

}  // namespace Logging
}  // namespace Core
