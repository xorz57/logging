#include "logging.hpp"

#include <chrono>
#include <thread>

static logging::Logger logger{logging::Level::Trace, "fibonacci.log"};

std::int64_t fibonacci(std::int64_t n) {
  logger.trace("fibonacci({}) called", n);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  if (n < 0) {
    logger.error("invalid input: n < 0");
    return -1;
  }

  if (n == 0) {
    logger.debug("fibonacci(0) = 0");
    return 0;
  }
  if (n == 1) {
    logger.debug("fibonacci(1) = 1");
    return 1;
  }

  std::int64_t a = fibonacci(n - 1);
  std::int64_t b = fibonacci(n - 2);
  std::int64_t result = a + b;

  logger.info("fibonacci({}) = {} ({} + {})", n, result, a, b);
  return result;
}

int main() {
  logger.info("fibonacci calculation started");

  for (int i = 0; i <= 10; ++i) {
    int result = fibonacci(i);
    logger.warn("fibonacci({}) computed as {}", i, result);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  logger.info("fibonacci calculation finished");

  return 0;
}
