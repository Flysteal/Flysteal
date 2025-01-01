cmake_minimum_required(VERSION 3.5.0)
project(SKY_LANDS VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GLFW
find_package(glfw3 REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include directories
include_directories(include)
include_directories(HeaderFiles)

# file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")      ${SOURCES}

# Add the executable target
#add_executable(SKY_LANDS src/main.cpp  src/glad.c)
add_executable(SKY_LANDS src/main.cpp src/ShaderClass.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp src/glad.c)

# Link OpenGL and GLFW to the executable
target_link_libraries(SKY_LANDS ${OPENGL_LIBRARIES} glfw)

message(STATUS "include  paths: $(CMAKE_ICLUDE_PATH")
