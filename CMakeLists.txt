cmake_minimum_required(VERSION 3.30)

project(logging LANGUAGES CXX)

add_executable(example example.cpp)
target_compile_features(example PRIVATE cxx_std_20)
