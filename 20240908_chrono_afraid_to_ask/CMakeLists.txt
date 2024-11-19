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

add_executable(chrono_afraid_to_ask chrono_afraid_to_ask.cpp)

target_compile_options(chrono_afraid_to_ask PRIVATE -Wall -Werror -Wextra -O0 -ggdb3 -gdwarf-5 -std=c++23)
target_link_options(chrono_afraid_to_ask PRIVATE -export-dynamic)

target_link_libraries(chrono_afraid_to_ask fmt)
# target_link_libraries(chrono_afraid_to_ask)

# create dynamic targets example_0, example_1, ..., example_100
foreach(i RANGE 0 100)
  add_custom_target("example_${i}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/chrono_afraid_to_ask "example_${i}" DEPENDS chrono_afraid_to_ask)
endforeach()
