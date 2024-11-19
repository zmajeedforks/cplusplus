# 20240910_chrono_afraid_to_ask/CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

project(chrono_afraid_to_ask)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG master
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(fmt)

add_executable(create_times create_times.cpp)

target_compile_options(create_times PRIVATE -Wall -Werror -Wextra -O0 -ggdb3 -gdwarf-5 -std=c++23)

target_link_libraries(create_times fmt)

