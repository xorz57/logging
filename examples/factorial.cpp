#include "logging.hpp"

#include <string>
#include <thread>

static logging::Logger logger{logging::Level::Trace, "factorial.log"};

std::uint64_t factorial(std::uint64_t n) {
  logger.trace("factorial({}) called", n);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  if (n == 0 || n == 1) {
    logger.debug("factorial({}) = 1", n);
    return 1;
  }

  const std::uint64_t prev{factorial(n - 1)};
  const std::uint64_t result{n * prev};

  logger.info("factorial({}) = {} ({} * {})", n, result, n, prev);
  return result;
}

int main(int argc, const char *argv[]) {
  if (argc != 2)
    return -1;

  logger.info("factorial calculation started");

  const std::uint64_t n{std::stoull(argv[1])};

  for (std::uint64_t i = 0; i <= n; ++i) {
    std::uint64_t result = factorial(i);
    logger.warn("factorial({}) computed as {}", i, result);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  logger.info("factorial calculation finished");

  return 0;
}
