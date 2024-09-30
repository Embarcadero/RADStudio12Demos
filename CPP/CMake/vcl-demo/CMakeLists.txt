cmake_minimum_required(VERSION 3.30)
project(CBuilderTestVCL)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(Project1 WIN32 ${SOURCES})

set_embt_target(Project1 VCL)

target_include_directories(Project1 PRIVATE "${CMAKE_SOURCE_DIR}")

target_link_libraries(Project1 PRIVATE "${CMAKE_SOURCE_DIR}/Project1.res")

install(TARGETS Project1
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
