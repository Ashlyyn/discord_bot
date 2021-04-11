cmake_minimum_required (VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wno-overloaded-virtual -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wno-overloaded-virtual -Wno-deprecated-declarations")
project(bot)

add_executable(bot_test main.cpp bot_client.cpp command.cpp mention.cpp server_bot_settings.cpp)
add_subdirectory(deps/sleepy-discord)
target_link_libraries(bot_test sleepy-discord)

