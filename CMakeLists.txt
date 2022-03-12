# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e inclua subprojetos aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("Lightning")

# Conda search and configure
if(DEFINED ENV{CONDA_PREFIX_1})
    # A conda environment is defined and active
    message(STATUS "Conda environment detected...")
    set(CONDA_LIB_DIR "$ENV{CONDA_PREFIX_1}/Library")
    set(CONDA_INCLUDE_DIR "${CONDA_LIB_DIR}/include")
    set(CONDA_LINK_DIR "${CONDA_LIB_DIR}/lib")
    include_directories(${CONDA_LIB_INCLUDE_DIR})
    list(APPEND CMAKE_PREFIX_PATH ${CONDA_LIB_DIR})
else()
    message(FATAL_ERROR "Conda environment not detected...")
endif()

# Add folder to search cmake libs files
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")

# find relevant packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add code sources
add_subdirectory ("src")