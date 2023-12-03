add_library(UnitOperation "")

target_sources(UnitOperation
  PRIVATE
    ${SOURCE_PATH}/UnitOperation/UnitOperation.cpp
    ${SOURCE_PATH}/UnitOperation/StorageTank.cpp
    ${SOURCE_PATH}/UnitOperation/SolarWaterHeater.cpp
    ${SOURCE_PATH}/UnitOperation/Pump.cpp
  PUBLIC
    ${SOURCE_PATH}/UnitOperation/UnitOperation.h
    ${SOURCE_PATH}/UnitOperation/UnitOperationFactory.h
    ${SOURCE_PATH}/UnitOperation/Pump.h
    ${SOURCE_PATH}/UnitOperation/StorageTank.h
    ${SOURCE_PATH}/UnitOperation/SolarWaterHeater.h
)

target_include_directories(UnitOperation
  PUBLIC
    ${SOURCE_PATH}
  )