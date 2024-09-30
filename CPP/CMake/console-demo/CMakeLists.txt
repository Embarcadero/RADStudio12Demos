cmake_minimum_required(VERSION 3.30)
project(CBuilderTestConsole)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(Project4 ${SOURCES})

set_embt_target(Project4 RTL)

target_include_directories(Project4 PRIVATE "${CMAKE_SOURCE_DIR}")

target_link_libraries(Project4 PRIVATE "${CMAKE_SOURCE_DIR}/Project4.res")

install(TARGETS Project4
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
