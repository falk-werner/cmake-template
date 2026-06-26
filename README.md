# CMake Template

CMake Template Repository.

## Build

```bash
cmake -B build
cmake --build build
```

## Run Unit Tests

```bash
cmake --build build --target test
```

## Create Coverage Report

```bash
cmake -B build -D CMAKE_BUILD_TYPE=PROFILE
cmake --build build
cmake --build build --target coverage
```

Find the coverage report in `build/coverage/example.html`.
