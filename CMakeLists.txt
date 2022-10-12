cmake_minimum_required(VERSION 3.2.0)

project(LaminarOS C CXX)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Interface/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers/${FAMILY_NAME}_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers/CMSIS/Device/ST/${FAMILY_NAME}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers/CMSIS/Include
)

set(HAL_DRIVERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Drivers)
set(HAL_DRIVERS_C_SOURCES "${HAL_DRIVERS_DIR}/${FAMILY_NAME}_HAL_Driver/Src/*.c")

set(HAL_CORE ${CMAKE_CURRENT_SOURCE_DIR}/boardfiles/${FOLDER_NAME}/Core)
set(HAL_CORE_C_SOURCES "${HAL_CORE}/Src/*.c")
set(HAL_CORE_CXX_SOURCES "${HAL_CORE}/Src/*.cpp")

set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Interface)
set(INTERFACE_C_SOURCES "${INTERFACE_DIR}/Src/*.c")
set(INTERFACE_CXX_SOURCES "${INTERFACE_DIR}/Src/*.cpp")

set(DRIVERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Drivers)
set(DRIVERS_C_SOURCES "${DRIVERS_DIR}/Src/*.c")
set(DRIVERS_CXX_SOURCES "${DRIVERS_DIR}/Src/*.cpp")

set(CORE_Dir ${CMAKE_CURRENT_SOURCE_DIR}/Core)
set(CORE_C_SOURCES "${CORE_Dir}/Src/*.c")
set(CORE_CXX_SOURCES "${CORE_Dir}/Src/*.cpp")

file(GLOB_RECURSE C_SOURCES ${HAL_DRIVERS_C_SOURCES}
                            ${HAL_CORE_C_SOURCES}
                            ${INTERFACE_CXX_SOURCES}
                            ${DRIVERS_CXX_SOURCES}
                            ${CORE_CXX_SOURCES})                            
message("MESSAGE: ${C_SOURCES}")                         
file(GLOB_RECURSE CXX_SOURCES ${HAL_CORE_CXX_SOURCES} 
                              ${INTERFACE_CXX_SOURCES}
                              ${DRIVERS_CXX_SOURCES}
                              ${CORE_CXX_SOURCES})

add_library(${PROJECT_NAME} ${C_SOURCES} ${CXX_SOURCES})
