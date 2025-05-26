#include "logging.hpp"

static logging::Logger logger{logging::Level::Trace, "example.log"};

int main() {
  logger.trace("function {} entered", "main");
  logger.debug("x = {}", 42);
  logger.info("application started, pid = {}", 1234);
  logger.warn("config file {} not found", "settings.json");
  logger.error("failed to connect to {}", "database");
  logger.critical("system shutting down due to error code {}", -1);

  return 0;
}
