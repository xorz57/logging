#include "logging.hpp"

#include <thread>

static logging::Logger logger{logging::Level::Trace, "factorial.log"};

int factorial(int n) {
  logger.trace("factorial({}) called", n);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  if (n < 0) {
    logger.error("invalid input: n < 0");
    return -1;
  }

  if (n == 0 || n == 1) {
    logger.debug("factorial({}) = 1", n);
    return 1;
  }

  int prev = factorial(n - 1);
  int result = n * prev;

  logger.info("factorial({}) = {} ({} * {})", n, result, n, prev);
  return result;
}

int main() {
  logger.info("factorial calculation started");

  for (int i = 0; i <= 10; ++i) {
    int result = factorial(i);
    logger.warn("factorial({}) computed as {}", i, result);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  logger.info("factorial calculation finished");

  return 0;
}
