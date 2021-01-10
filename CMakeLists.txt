cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
  SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(boost-filesystem)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
#add_subdirectory(third_party/googletest)

hunter_add_package(Boost COMPONENTS system filesystem regex)
find_package(Boost CONFIG REQUIRED system filesystem regex)

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)
target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(dir_parser STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/directory_parser.cpp)
target_include_directories(dir_parser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dir_parser Boost::filesystem Boost::system Boost::regex)
target_link_libraries(main dir_parser Boost::filesystem)


add_executable(tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)
target_include_directories(tests
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(tests GTest::gtest_main Boost::filesystem dir_parser)

enable_testing()
add_test(NAME unit_tests COMMAND tests) 

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  add_coverage(dir_parser)
  add_coverage(tests)
  add_coverage(main)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
