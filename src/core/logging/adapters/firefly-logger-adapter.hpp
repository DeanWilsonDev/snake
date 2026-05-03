#pragma once
#include "core/logging/log.hpp"
#include <firefly/log-registry.hpp>
#include <firefly/logger.hpp>
#include <memory>
#include <string>

namespace Core::Logging {

class FireflyLoggerAdapter : public ILogger {
 public:
  explicit FireflyLoggerAdapter(std::shared_ptr<Firefly::Logger> fireflyLogger)
      : fireflyLogger(std::move(fireflyLogger))
  {
  }

 protected:
  void TraceImpl(const std::string& message) override { fireflyLogger->Trace("{}", message); }
  void DebugImpl(const std::string& message) override { fireflyLogger->Debug("{}", message); }
  void InfoImpl(const std::string& message) override { fireflyLogger->Info("{}", message); }
  void WarningImpl(const std::string& message) override { fireflyLogger->Warning("{}", message); }
  void ErrorImpl(const std::string& message) override { fireflyLogger->Error("{}", message); }
  void FatalImpl(const std::string& message) override { fireflyLogger->Fatal("{}", message); }

 private:
  std::shared_ptr<Firefly::Logger> fireflyLogger;
};

}  // namespace Core::Logging
