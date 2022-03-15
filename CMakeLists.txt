cmake_minimum_required(VERSION 3.11)
project(nped LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

include(FetchContent)
FetchContent_Declare(
    libtins
    GIT_REPOSITORY    https://github.com/mfontanini/libtins.git
    )
FetchContent_Declare(
    catch2
    GIT_REPOSITORY    https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.0-preview4
    )
message(STATUS "Fetching libtins...")
FetchContent_MakeAvailable(libtins)
message(STATUS "Fetching Catch2...")
FetchContent_MakeAvailable(catch2)

add_subdirectory(src)
