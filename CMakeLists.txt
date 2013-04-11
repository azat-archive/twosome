
#
# Cmake rules for twosome project
#

cmake_minimum_required(VERSION 2.6)
project(twosome CXX C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

include(AddCompilerFlags)
include(CheckCXXCompilerFlag)
include(FindLibrariesOrFatalError)
include(AddFilesGlobRecursiveToList)

message(STATUS "Making ${PROJECT_NAME} on ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")

find_package(Boost REQUIRED COMPONENTS program_options log system)

FindLibrariesOrFatalError("boost_program_options boost_log boost_system")

# The version number.
set(twosome_VERSION_MAJOR 0)
set(twosome_VERSION_MINOR 10)

# Directories
set(TWOSOME_ROOT_DIR "${CMAKE_SOURCE_DIR}")
set(TWOSOME_BINARY_DIR "${TWOSOME_ROOT_DIR}/build")
set(TWOSOME_BUILD_DIR "${TWOSOME_ROOT_DIR}/build")
set(TWOSOME_SOURCE_DIR "${TWOSOME_ROOT_DIR}/src")
set(TWOSOME_LIBRARY_DIR "${TWOSOME_ROOT_DIR}/lib")
set(TWOSOME_EXECUTABLE_OUTPUT_PATH ${TWOSOME_BUILD_DIR} CACHE PATH "Build directory" FORCE)
set(TWOSOME_LIBRARY_OUTPUT_PATH ${TWOSOME_BUILD_DIR} CACHE PATH "Build directory" FORCE)

# Include paths
include_directories(${TWOSOME_SOURCE_DIR})
include_directories(${TWOSOME_BINARY_DIR})

AddCompilerFlags(FLAGS -Wall -Wextra -Werror -g -rdynamic LANGUAGES C CXX)
AddCompilerFlags(FAIL_ON_ERROR FLAGS -std=c++11 LANGUAGES CXX)
add_definitions(-D_REENTRANT -DTHREAD_SAFE -D_GNU_SOURCE -DDEBUG)

# twosome sources
AddFilesGlobRecursiveToList(TWOSOME_SOURCES "${TWOSOME_SOURCE_DIR}/kernel/*.cpp")
AddFilesGlobRecursiveToList(TWOSOME_SOURCES "${TWOSOME_SOURCE_DIR}/util/*.cpp")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
    "${TWOSOME_SOURCE_DIR}/config.h.in"
    "${TWOSOME_BINARY_DIR}/config.h"
)

# twosome server
file(GLOB_RECURSE TWOSOME_SERVER_SOURCES "${TWOSOME_SOURCE_DIR}/server/*.cpp")
list(APPEND TWOSOME_SERVER_SOURCES ${TWOSOME_SOURCES})
add_executable(twosomed ${TWOSOME_SERVER_SOURCES})
target_link_libraries(twosomed ${LIBS})