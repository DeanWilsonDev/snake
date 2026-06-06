#pragma once
#include "core/logging/log.hpp"
#include "firefly/log-levels/log-level-debug.hpp"
#include "firefly/log-levels/log-level-error.hpp"
#include "firefly/log-levels/log-level-fatal.hpp"
#include "firefly/log-levels/log-level-warning.hpp"
#include <firefly/log-registry.hpp>
#include <firefly/logger.hpp>
#include <firefly/log-levels.hpp>
#include <memory>
#include <string>

using namespace Firefly;

namespace Core::Logging {

class FireflyLoggerAdapter : public ILogger {
 public:
  explicit FireflyLoggerAdapter(std::shared_ptr<Logger> fireflyLogger)
      : fireflyLogger(std::move(fireflyLogger))
  {
  }

 protected:
  void TraceImpl(const std::string& message) override
  {
    fireflyLogger->Log<LogLevels::Trace>("{}", message);
  }

  void DebugImpl(const std::string& message) override
  {
    fireflyLogger->Log<LogLevels::Debug>("{}", message);
  }

  void InfoImpl(const std::string& message) override
  {
    fireflyLogger->Log<LogLevels::Info>("{}", message);
  }

  void WarningImpl(const std::string& message) override
  {
    fireflyLogger->Log<LogLevels::Warning>("{}", message);
  }

  void ErrorImpl(const std::string& message) override
  {
    fireflyLogger->Log<LogLevels::Error>("{}", message);
  }

  void FatalImpl(const std::string& message) override
  {
    fireflyLogger->Log<LogLevels::Fatal>("{}", message);
  }

 private:
  std::shared_ptr<Logger> fireflyLogger;
};

}  // namespace Core::Logging
