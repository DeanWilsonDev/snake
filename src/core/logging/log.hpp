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
  UMBRA_ENGINE_API static void Init(const std::string& fileName, bool enableClientDebugLogging = true);

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

// Log Init Macros

#define LOG_INIT(...) Umbra::Core::Logging::Log::Init(__VA_ARGS__)

// Client Log Macros
#define LOG_TRACE(...) Umbra::Core::Logging::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define LOG_DEBUG(...) Umbra::Core::Logging::Log::GetClientLogger()->Debug(__VA_ARGS__)
#define LOG_INFO(...) Umbra::Core::Logging::Log::GetClientLogger()->Info(__VA_ARGS__)
#define LOG_WARNING(...) Umbra::Core::Logging::Log::GetClientLogger()->Warning(__VA_ARGS__)
#define LOG_ERROR(...) Umbra::Core::Logging::Log::GetClientLogger()->Error(__VA_ARGS__)
#define LOG_FATAL(...) Umbra::Core::Logging::Log::GetClientLogger()->Fatal(__VA_ARGS__)

// Core Log Macros
#define LOG_CORE_TRACE(...) Umbra::Core::Logging::Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) Umbra::Core::Logging::Log::GetCoreLogger()->Debug(__VA_ARGS__)
#define LOG_CORE_INFO(...) Umbra::Core::Logging::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define LOG_CORE_WARNING(...) Umbra::Core::Logging::Log::GetCoreLogger()->Warning(__VA_ARGS__)
#define LOG_CORE_ERROR(...) Umbra::Core::Logging::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define LOG_CORE_FATAL(...) Umbra::Core::Logging::Log::GetCoreLogger()->Fatal(__VA_ARGS__)

}  // namespace Umbra
