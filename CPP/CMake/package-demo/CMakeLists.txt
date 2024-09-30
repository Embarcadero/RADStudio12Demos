cmake_minimum_required(VERSION 3.30)
project(CBuilderTestVCLPackage)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_library(Package1 SHARED ${SOURCES})

add_library(Package1_static STATIC ${SOURCES})
set_target_properties(Package1_static PROPERTIES OUTPUT_NAME "Package1")

set_embt_target(Package1 VCL Package)
set_embt_target(Package1_static VCL Package)

target_include_directories(Package1 PRIVATE "${CMAKE_SOURCE_DIR}")
target_include_directories(Package1_static PRIVATE "${CMAKE_SOURCE_DIR}")

target_link_libraries(Package1 PRIVATE "${CMAKE_SOURCE_DIR}/Package1.res")

install(TARGETS Package1 Package1_static
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
