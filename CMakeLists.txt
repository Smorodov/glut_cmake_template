cmake_minimum_required(VERSION 3.12)
project(main)

# Set C++ version
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_DEBUG_POSTFIX _d)


# Find OpenGL package
find_package(OpenGL REQUIRED)

# Add FreeGLUT dependency
include(FetchContent)
FetchContent_Declare(
  freeglut
  GIT_REPOSITORY https://github.com/dcnieho/FreeGLUT.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(freeglut)

# Add GLEW dependency
FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        glew-cmake-2.1.0
)
FetchContent_MakeAvailable(glew)

# Add include directories for OpenGL headers
include_directories(
${OPENGL_INCLUDE_DIRS}
${freeglut_SOURCE_DIR}/include
${glew_SOURCE_DIR}/include
)

# Add your source files
set(SOURCES 
    main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE freeglut_static ${OPENGL_LIBRARIES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
