#include "logging.hpp"

#include <chrono>
#include <string>
#include <thread>

static logging::Logger logger{logging::Level::Trace, "fibonacci.log"};

std::uint64_t fibonacci(std::uint64_t n) {
  logger.trace("fibonacci({}) called", n);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  if (n == 0) {
    logger.debug("fibonacci(0) = 0");
    return 0;
  }
  if (n == 1) {
    logger.debug("fibonacci(1) = 1");
    return 1;
  }

  const std::uint64_t a{fibonacci(n - 1)};
  const std::uint64_t b{fibonacci(n - 2)};
  const std::uint64_t result{a + b};

  logger.info("fibonacci({}) = {} ({} + {})", n, result, a, b);
  return result;
}

int main(int argc, const char *argv[]) {
  if (argc != 2)
    return -1;

  logger.info("fibonacci calculation started");

  const std::uint64_t n{std::stoull(argv[1])};

  for (std::uint64_t i = 0; i <= n; ++i) {
    std::uint64_t result{fibonacci(i)};
    logger.warn("fibonacci({}) computed as {}", i, result);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  logger.info("fibonacci calculation finished");

  return 0;
}
