cmake_minimum_required(VERSION 3.20)

project(healthcare_management LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HCO_CORE_SOURCES
    Aide.cpp
    CaseManager.cpp
    Date.cpp
    Employee.cpp
    Equipment.cpp
    MobilityEquipment.cpp
    MonitorEquipment.cpp
    Nurse.cpp
    Patient.cpp
    Service.cpp
    Visit.cpp
)

add_library(hco_core STATIC ${HCO_CORE_SOURCES})
target_include_directories(hco_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(healthcare_management Main.cpp)
target_link_libraries(healthcare_management PRIVATE hco_core)

foreach(target hco_core healthcare_management)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()

file(GLOB HCO_RUNTIME_DATA CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.txt")
list(REMOVE_ITEM HCO_RUNTIME_DATA "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
foreach(data_file IN LISTS HCO_RUNTIME_DATA)
    add_custom_command(TARGET healthcare_management POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${data_file}"
            "$<TARGET_FILE_DIR:healthcare_management>"
    )
endforeach()

include(CTest)
if(BUILD_TESTING)
    add_executable(hco_tests tests/CoreTests.cpp)
    target_link_libraries(hco_tests PRIVATE hco_core)
    if(MSVC)
        target_compile_options(hco_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(hco_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME hco_core_tests COMMAND hco_tests)
endif()
