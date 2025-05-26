#include "logging.hpp"

#include <chrono>
#include <cstdint>
#include <random>
#include <thread>

static logging::Logger s_logger{logging::Level::Info, "example.log"};

int main(int argc, char *argv[]) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(25, 100);

  for (std::uint32_t i = 0; i < 100; ++i) {
    s_logger.info("i");
    s_logger.info("i = " + std::to_string(i));
    s_logger.info("i = {}", i);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
  }

  return 0;
}
