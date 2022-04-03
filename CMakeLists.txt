cmake_minimum_required(VERSION 3.21)
project(cookie-factory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

#
# External libraries
#
include(support/cmake/CPM.cmake)
CPMAddPackage(
        NAME inja
        VERSION 3.3.0
        GITHUB_REPOSITORY pantor/inja
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext/inja"
        DOWNLOAD_ONLY True
)

CPMAddPackage(
        NAME cxxopts
        GITHUB_REPOSITORY jarro2783/cxxopts
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext/cxxopts"
        VERSION 3.0.0
        DOWNLOAD_ONLY True
)

CPMAddPackage(
        NAME fmt
        GIT_TAG 8.1.1
        GITHUB_REPOSITORY fmtlib/fmt
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext/fmt"
        OPTIONS
        "FMT_TEST Off"
        "FMT_DOC Off"
)


add_library(cxxopts INTERFACE IMPORTED)
target_include_directories(cxxopts INTERFACE "${cxxopts_SOURCE_DIR}/include")

add_subdirectory(src)
