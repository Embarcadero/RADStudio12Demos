cmake_minimum_required(VERSION 3.30)
project(CBuilderTestFMXDynamic)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(Project2 WIN32 ${SOURCES})

set_embt_target(Project2 FMX DynamicRuntime)

target_include_directories(Project2 PRIVATE "${CMAKE_SOURCE_DIR}")

target_link_libraries(Project2 PRIVATE "${CMAKE_SOURCE_DIR}/Project2.res")

install(TARGETS Project2
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
