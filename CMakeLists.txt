cmake_minimum_required(VERSION 3.16)
project(banana-engine)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(glfw3 3.3 REQUIRED)


# Create your game executable target as usual
add_executable(
		${PROJECT_NAME}
		main.cpp
		glad/glad.h
		KHR/khrplatform.h
		glad.c
		banana_engine.cpp
		shader.h
)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
