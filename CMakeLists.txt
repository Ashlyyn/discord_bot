cmake_minimum_required (VERSION 3.6)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(bot)

add_executable(bot_test main.cpp)
add_subdirectory(deps/sleepy-discord)
target_link_libraries(bot_test sleepy-discord)
