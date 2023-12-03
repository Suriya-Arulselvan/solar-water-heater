# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SolarWaterHeaterSimulator")

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SolarWaterHeaterSimulator)

# Include sub-projects.
add_subdirectory ("SolarWaterHeaterSimulator")