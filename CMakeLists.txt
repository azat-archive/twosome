
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

find_package(Boost REQUIRED COMPONENTS log system)

FindLibrariesOrFatalError("boost_log boost_system sctp")

# The version number.
set(twosome_VERSION_MAJOR 0)
set(twosome_VERSION_MINOR 10)

# Directories
set(TWOSOME_ROOT_DIR "${CMAKE_SOURCE_DIR}")
set(TWOSOME_BINARY_DIR "${TWOSOME_ROOT_DIR}/build")
set(TWOSOME_BUILD_DIR "${TWOSOME_ROOT_DIR}/build")
set(TWOSOME_SOURCE_DIR "${TWOSOME_ROOT_DIR}/src")
set(TWOSOME_THIRD_PARTY_SOURCE_DIR "${TWOSOME_ROOT_DIR}/src/third_party")
set(TWOSOME_LIBRARY_DIR "${TWOSOME_ROOT_DIR}/lib")
set(TWOSOME_EXECUTABLE_OUTPUT_PATH ${TWOSOME_BUILD_DIR} CACHE PATH "Build directory" FORCE)
set(TWOSOME_LIBRARY_OUTPUT_PATH ${TWOSOME_BUILD_DIR} CACHE PATH "Build directory" FORCE)

# Include paths
include_directories(${TWOSOME_SOURCE_DIR})
include_directories(${TWOSOME_BINARY_DIR})
include_directories("${TWOSOME_THIRD_PARTY_SOURCE_DIR}/boostasiosctp")

AddCompilerFlags(FLAGS -Wall -Wextra -Werror -g -rdynamic LANGUAGES C CXX)
AddCompilerFlags(FAIL_ON_ERROR FLAGS -std=c++11 LANGUAGES CXX)
add_definitions(-D_REENTRANT -DTHREAD_SAFE -D_GNU_SOURCE -DDEBUG)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
    "${TWOSOME_SOURCE_DIR}/config.h.in"
    "${TWOSOME_BINARY_DIR}/config.h"
)

# twosome server
set(TWOSOME_SERVER_SOURCES
    "${TWOSOME_SOURCE_DIR}/kernel/net/chatserver.cpp"
    "${TWOSOME_SOURCE_DIR}/kernel/net/session.cpp"
    "${TWOSOME_SOURCE_DIR}/server/twosomed.cpp")
add_executable(twosomed ${TWOSOME_SERVER_SOURCES})
target_link_libraries(twosomed ${LIBS})

# twosome client
set(TWOSOME_CLIENT_SOURCES
    "${TWOSOME_SOURCE_DIR}/kernel/net/chatclient.cpp"
    "${TWOSOME_SOURCE_DIR}/client/twosome.cpp")
add_executable(twosome ${TWOSOME_CLIENT_SOURCES})
target_link_libraries(twosome ${LIBS})