cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(projectName battle-city)
project(${projectName})

add_executable(${projectName} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${projectName} glfw)

add_subdirectory(external/glad)
target_link_libraries(${projectName} glad)