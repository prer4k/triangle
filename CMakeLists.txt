cmake_minimum_required(VERSION 3.16)
project(triangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
include_directories(include)
include_directories(src)

add_executable(main 
src/main.cpp src/glad.c src/core/Shader.cpp src/graphics/Mesh.cpp src/core/Window.cpp src/animation/Animation.cpp
src/math/Transform.cpp src/renderer/Renderer.cpp src/scene/Object.cpp src/camera/Camera.cpp src/scene/Scene.cpp src/core/Input.cpp)
target_link_libraries(main
    OpenGL::GL
    glfw
)
