#pragma once

#include <format>
#include <fstream>
#include <mutex>

namespace logging {
enum class Level { Trace, Debug, Info, Warn, Error, Critical, Off };

class Logger {
public:
  Logger(Level level, const char *filename) : m_level(level), m_ofstream(filename, std::ios::app) {};

  void setLevel(Level level) { m_level = level; }

  Level getLevel() const { return m_level; }

  void trace(const char *str) { write(Level::Trace, str); }

  void debug(const char *str) { write(Level::Debug, str); }

  void info(const char *str) { write(Level::Info, str); }

  void warn(const char *str) { write(Level::Warn, str); }

  void error(const char *str) { write(Level::Error, str); }

  void critical(const char *str) { write(Level::Critical, str); }

  void trace(const std::string &str) { write(Level::Trace, str); }

  void debug(const std::string &str) { write(Level::Debug, str); }

  void info(const std::string &str) { write(Level::Info, str); }

  void warn(const std::string &str) { write(Level::Warn, str); }

  void error(const std::string &str) { write(Level::Error, str); }

  void critical(const std::string &str) { write(Level::Critical, str); }

  template <typename... Args> void trace(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Trace, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void debug(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Debug, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void info(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Info, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void warn(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Warn, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void error(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Error, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args> void critical(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Critical, fmt, std::forward<Args>(args)...);
  }

private:
  std::string getTimeStamp() {
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &itt);
#else
    localtime_r(&itt, &tm);
#endif

    auto ms = duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1'000;

    char buffer[24]; // YYYY-MM-DD HH:MM:SS.mmm + '\0'
    std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d.%03d", tm.tm_year + 1900, tm.tm_mon + 1,
                  tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, static_cast<int>(ms.count()));

    return std::string(buffer);
  }

  constexpr std::string_view toStringView(Level level) {
    switch (level) {
    case Level::Trace:
      return "TRACE";
    case Level::Debug:
      return "DEBUG";
    case Level::Info:
      return "INFO";
    case Level::Warn:
      return "WARN";
    case Level::Error:
      return "ERROR";
    case Level::Critical:
      return "CRITICAL";
    case Level::Off:
      return "OFF";
    default:
      return "UNKNOWN";
    }
  }

  void write(Level level, const char *str) {
    if (level < m_level)
      return;
    m_ofstream << "[" << getTimeStamp() << "] " << "[" << toStringView(level) << "] " << str << std::endl;
  }

  void write(Level level, const std::string &str) {
    if (level < m_level)
      return;
    m_ofstream << "[" << getTimeStamp() << "] " << "[" << toStringView(level) << "] " << str << std::endl;
  }

  template <typename... Args> void write(Level level, std::format_string<Args...> fmt, Args &&...args) {
    if (level < m_level)
      return;
    m_ofstream << "[" << getTimeStamp() << "] " << "[" << toStringView(level) << "] "
               << std::format(fmt, std::forward<Args>(args)...) << std::endl;
  }

  Level m_level;
  std::ofstream m_ofstream;
  std::mutex m_mutex;
};
} // namespace logging
