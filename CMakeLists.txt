cmake_minimum_required(VERSION 3.30)

project(logging LANGUAGES CXX)

add_library(logging INTERFACE)

target_include_directories(logging INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/logging>
  $<INSTALL_INTERFACE:include/logging>  # <prefix>/include/logging
)

add_subdirectory(examples)
