#pragma once

#include <firefly/log-registry.hpp>
#include <firefly/logger.hpp>
#include <string>
#include <memory>

namespace Umbra {
namespace Core {
namespace Logging {

#ifdef UMBRA_ENGINE_PLATFORM_MACOS
#define UMBRA_ENGINE_API __attribute__((visibility("default")))
#elif UMBRA_ENGINE_PLATFORM_WINDOWS
#define UMBRA_ENGINE_API __declspec(dllexport)
#else
#define UMBRA_ENGINE_API
#endif

#define CORE_LOGGER_NAME "Umbra"
#define CLIENT_LOGGER_NAME "Client"

class Log {
 public:
  UMBRA_ENGINE_API static void Init(bool enableClientDebugLogging = true);
  UMBRA_ENGINE_API static void Init(std::string& fileName, bool enableClientDebugLogging = true);

  UMBRA_ENGINE_API inline static std::shared_ptr<Firefly::Logger>& GetCoreLogger()
  {
    return Firefly::LogRegistry::GetLogger(CORE_LOGGER_NAME);
  };
  UMBRA_ENGINE_API inline static std::shared_ptr<Firefly::Logger>& GetClientLogger()
  {
    return Firefly::LogRegistry::GetLogger(CLIENT_LOGGER_NAME);
  }
};
}  // namespace Logging
}  // namespace Core

// Client Log Macros
#define LOG_TRACE(...) Umbra::Logging::Log::getClientLogger()->Trace(__VA_ARGS__)
#define LOG_DEBUG(...) Umbra::Logging::Log::getClientLogger()->Debug(__VA_ARGS__)
#define LOG_INFO(...) Umbra::Logging::Log::getClientLogger()->Info(__VA_ARGS__)
#define LOG_WARNING(...) Umbra::Logging::Log::getClientLogger()->Warning(__VA_ARGS__)
#define LOG_ERROR(...) Umbra::Logging::Log::getClientLogger()->Error(__VA_ARGS__)
#define LOG_FATAL(...) Umbra::Logging::Log::getClientLogger()->Fatal(__VA_ARGS__)

// Core Log Macros
#define LOG_CORE_TRACE(...) Umbra::Logging::Log::getCoreLogger()->Trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) Umbra::Logging::Log::getCoreLogger()->Debug(__VA_ARGS__)
#define LOG_CORE_INFO(...) Umbra::Logging::Log::getCoreLogger()->Info(__VA_ARGS__)
#define LOG_CORE_WARNING(...) Umbra::Logging::Log::getCoreLogger()->Warning(__VA_ARGS__)
#define LOG_CORE_ERROR(...) Umbra::Logging::Log::getCoreLogger()->Error(__VA_ARGS__)
#define LOG_CORE_FATAL(...) Umbra::Logging::Log::getCoreLogger()->Fatal(__VA_ARGS__)

}  // namespace Umbra
