# logging

[![CMake on multiple platforms](https://github.com/xorz57/logging/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/xorz57/logging/actions/workflows/cmake-multi-platform.yml)

A header-only C++ logging library.

## Examples

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -S .
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
```
