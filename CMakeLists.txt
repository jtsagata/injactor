cmake_minimum_required(VERSION 3.18)

project(injactor
        VERSION "0.0.1"
        LANGUAGES CXX
        HOMEPAGE_URL https://github.com/jtsagata/cookie-factory
        DESCRIPTION "Generate a list of files from a set of templates. Using a JSON file to specify parameters")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

#
# External libraries
#
include(support/cmake/CPM.cmake)

CPMAddPackage(NAME fmt GIT_TAG 8.1.1 GITHUB_REPOSITORY fmtlib/fmt
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext/fmt"
        OPTIONS "FMT_TEST Off" "FMT_DOC Off")

add_subdirectory(src)
