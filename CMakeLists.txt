cmake_minimum_required(VERSION 3.28)
project(tomson_task)

set(CMAKE_CXX_STANDARD 17)

add_executable(tomson_task src/main.cpp
        src/Calculate/calculate_classes.h
        src/Calculate/calculate_classes.cpp
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Renderer/Renderer.cpp)


add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

target_link_libraries(tomson_task glfw)
target_link_libraries(tomson_task glad)
target_link_libraries(tomson_task glm)