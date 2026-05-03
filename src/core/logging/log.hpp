#pragma once
#include <string>
#include <format>

namespace Core::Logging {

class ILogger {
 public:
  virtual ~ILogger() = default;

  template <typename... TArgs>
  void Trace(std::format_string<TArgs...> fmt, TArgs&&... args)
  {
    TraceImpl(std::format(fmt, std::forward<TArgs>(args)...));
  }

  template <typename... TArgs>
  void Debug(std::format_string<TArgs...> fmt, TArgs&&... args)
  {
    DebugImpl(std::format(fmt, std::forward<TArgs>(args)...));
  }

  template <typename... TArgs>
  void Info(std::format_string<TArgs...> fmt, TArgs&&... args)
  {
    InfoImpl(std::format(fmt, std::forward<TArgs>(args)...));
  }

  template <typename... TArgs>
  void Warning(std::format_string<TArgs...> fmt, TArgs&&... args)
  {
    WarningImpl(std::format(fmt, std::forward<TArgs>(args)...));
  }

  template <typename... TArgs>
  void Error(std::format_string<TArgs...> fmt, TArgs&&... args)
  {
    ErrorImpl(std::format(fmt, std::forward<TArgs>(args)...));
  }

  template <typename... TArgs>
  void Fatal(std::format_string<TArgs...> fmt, TArgs&&... args)
  {
    FatalImpl(std::format(fmt, std::forward<TArgs>(args)...));
  }

 protected:
  virtual void TraceImpl(const std::string& message) = 0;
  virtual void DebugImpl(const std::string& message) = 0;
  virtual void InfoImpl(const std::string& message) = 0;
  virtual void WarningImpl(const std::string& message) = 0;
  virtual void ErrorImpl(const std::string& message) = 0;
  virtual void FatalImpl(const std::string& message) = 0;
};

class Log {
 public:
  static void Init(bool enableClientDebugLogging = true);
  static void Init(const std::string& fileName, bool enableClientDebugLogging = true);

  static ILogger& GetCoreLogger();
  static ILogger& GetClientLogger();
};

}  // namespace Core::Logging


#define LOG_INIT(...) ::Core::Logging::Log::Init(__VA_ARGS__)

#define LOG_TRACE(...) ::Core::Logging::Log::GetClientLogger().Trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::Core::Logging::Log::GetClientLogger().Debug(__VA_ARGS__)
#define LOG_INFO(...) ::Core::Logging::Log::GetClientLogger().Info(__VA_ARGS__)
#define LOG_WARNING(...) ::Core::Logging::Log::GetClientLogger().Warning(__VA_ARGS__)
#define LOG_ERROR(...) ::Core::Logging::Log::GetClientLogger().Error(__VA_ARGS__)
#define LOG_FATAL(...) ::Core::Logging::Log::GetClientLogger().Fatal(__VA_ARGS__)

#define LOG_CORE_TRACE(...) ::Core::Logging::Log::GetCoreLogger().Trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) ::Core::Logging::Log::GetCoreLogger().Debug(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::Core::Logging::Log::GetCoreLogger().Info(__VA_ARGS__)
#define LOG_CORE_WARNING(...) ::Core::Logging::Log::GetCoreLogger().Warning(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Core::Logging::Log::GetCoreLogger().Error(__VA_ARGS__)
#define LOG_CORE_FATAL(...) ::Core::Logging::Log::GetCoreLogger().Fatal(__VA_ARGS__)
