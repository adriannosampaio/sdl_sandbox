# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e inclua subprojetos aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("Lightning")



if(DEFINED ENV{CONDA_PREFIX_1})
    # A conda environment is defined and active
    message(STATUS "Conda environment detected...")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")

set(CONDA_LIB_DIR "$ENV{CONDA_PREFIX_1}/Library")
set(CONDA_INCLUDE_DIR "${CONDA_LIB_DIR}/include")
set(CONDA_LINK_DIR "${CONDA_LIB_DIR}/lib")

message(STATUS "source dir ${CMAKE_SOURCE_DIR}")
message(STATUS "$${CMAKE_MODULE_PATH}")

include_directories(${CONDA_LIB_INCLUDE_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CONDA_LIB_DIR})
#include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Inclua subprojetos.
add_subdirectory ("Lightning")