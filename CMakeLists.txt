cmake_minimum_required(VERSION 3.30)
project(CMakeTemplate VERSION 1.0.0 LANGUAGES CXX)

option(WITHOUT_TESTS "Disable building unit tests" OFF)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_C_FLAGS_PROFILE --coverage)
SET(CMAKE_CXX_FLAGS_PROFILE --coverage)

add_library(example STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/meta.cpp
    lib/example/main.cpp
)
target_include_directories(example PUBLIC include)
target_include_directories(example PRIVATE lib)

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/lib/example/meta.cpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/meta.cpp
    @ONLY
)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE example)

if(NOT(WITHOUT_TESTS))

enable_testing()
include(CTest)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(alltests
    test-src/test_main.cpp
)

target_link_libraries(alltests PRIVATE example GTest::gtest GTest::gtest_main)
gtest_discover_tests(alltests)

add_custom_target(coverage
    mkdir -p coverage
	COMMAND ./alltests
	COMMAND gcovr --html-details coverage/example.html -r ${CMAKE_CURRENT_LIST_DIR} -e ${CMAKE_CURRENT_LIST_DIR}/test -e ${CMAKE_CURRENT_LIST_DIR}/src 
)
add_dependencies(coverage alltests)

endif()
