// MIT License
//
// Copyright (c) 2025 Georgios Fotopoulos
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <chrono>
#include <ctime>
#include <format>
#include <fstream>
#include <mutex>

namespace logging {
enum class Level { Trace,
                   Debug,
                   Info,
                   Warn,
                   Error,
                   Critical,
                   Off };

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

  template <typename... Args>
  void trace(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Trace, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Debug, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void info(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Info, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warn(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Warn, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Error, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void critical(std::format_string<Args...> fmt, Args &&...args) {
    write(Level::Critical, fmt, std::forward<Args>(args)...);
  }

private:
  std::string getTimeStamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &time_t_now);
#else
    localtime_r(&time_t_now, &tm);
#endif

    auto ms = duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1'000;

    return std::format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}.{:03}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, static_cast<int>(ms.count()));
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

  template <typename... Args>
  void write(Level level, std::format_string<Args...> fmt, Args &&...args) {
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
