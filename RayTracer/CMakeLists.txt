CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(RayTracer CXX)

set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")

add_subdirectory(../fltk ThirdParty/fltk)

# fltk_all: headers, libraries
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE ../fltk ${CMAKE_CURRENT_BINARY_DIR}/fltk)
target_link_libraries(fltk_all INTERFACE fltk fltk_gl fltk_images)

# RayTracer
set(RayTracer_SRC
# main
  src/main.cpp
  src/getopt.cpp
  src/RayTracer.cpp
# parser
  src/parser/Parser.cpp
  src/parser/ParserException.cpp
  src/parser/Token.cpp
  src/parser/Tokenizer.cpp
# scene
  src/scene/camera.cpp
  src/scene/light.cpp
  src/scene/material.cpp
  src/scene/ray.cpp
  src/scene/scene.cpp
# ui
  src/ui/CommandLineUI.cpp
  src/ui/debuggingView.cpp
  src/ui/debuggingWindow.cxx
  src/ui/glObjects.cpp
  src/ui/GraphicalUI.cpp
  src/ui/ModelerCamera.cpp
  src/ui/TraceGLWindow.cpp
# object
  src/object/Box.cpp
  src/object/Cone.cpp
  src/object/Cylinder.cpp
  src/object/Sphere.cpp
  src/object/Square.cpp
  src/object/trimesh.cpp
# fileio
  src/fileio/buffer.cpp
  src/fileio/imageio.cpp
)

add_executable(RayTracer ${RayTracer_SRC})
target_include_directories(RayTracer PRIVATE include/)
target_link_libraries(RayTracer PRIVATE fltk_all)

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RayTracer)
