add_library(Simulation "")

target_sources(Simulation
  PRIVATE
    ${SOURCE_PATH}/Simulation/Simulation.cpp
    ${SOURCE_PATH}/Simulation/SimulationSystem.cpp

  PUBLIC
    ${SOURCE_PATH}/Simulation/Simulation.h
    ${SOURCE_PATH}/Simulation/SimulationSystem.h
)

if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS}) 
target_link_libraries(Simulation ${Boost_LIBRARIES})
endif()

target_include_directories(Simulation
  PUBLIC
    ${SOURCE_PATH}
  )