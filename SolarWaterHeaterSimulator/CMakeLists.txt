# CMakeList.txt : CMake project for SolarWaterHeaterSimulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT boost_1_82_0)
SET(BOOST_INCLUDEDIR boost_1_82_0/boost)
SET(BOOST_LIBRARYDIR boost_1_82_0/libs)


find_package(Boost 1.82.0)


# Add source to this project's executable.
add_executable (SolarWaterHeaterSimulator "SolarWaterHeaterSimulator.cpp" "SolarWaterHeaterSimulator.h")

add_subdirectory(UnitOperation)
add_subdirectory(Simulation)

target_link_libraries(SolarWaterHeaterSimulator
PRIVATE
UnitOperation
Simulation
)

target_compile_features(SolarWaterHeaterSimulator PRIVATE cxx_std_17)


if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS}) 
target_link_libraries(SolarWaterHeaterSimulator ${Boost_LIBRARIES})
endif()

set_target_properties(SolarWaterHeaterSimulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SOURCE_PATH}/SolarWaterHeaterSimulatorBuild")

# TODO: Add tests and install targets if needed.
