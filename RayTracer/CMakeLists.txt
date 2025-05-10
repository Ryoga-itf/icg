CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(RayTracer CXX)

set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
if(APPLE)
  add_compile_options(-include "${CMAKE_CURRENT_SOURCE_DIR}/include/mac_fixes.h")
  find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)
  find_library(COREGRAPHICS_FRAMEWORK CoreGraphics REQUIRED)
  find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
  find_library(APPLICATIONSERVICES_FRAMEWORK ApplicationServices REQUIRED)
  find_library(CARBON_FRAMEWORK Carbon REQUIRED)
  find_library(CORESERVICES_FRAMEWORK CoreServices REQUIRED)
  find_library(COREFOUNDATION_FRAMEWORK CoreFoundation REQUIRED)
  find_library(COREVIDEO_FRAMEWORK CoreVideo REQUIRED)
  find_library(QUARTZ_FRAMEWORK Quartz REQUIRED)
  find_library(UNIFORMTYPEIDENTIFIERS_FRAMEWORK UniformTypeIdentifiers QUIET)
  set(EXTRA_LIBS 
      ${OPENGL_FRAMEWORK} 
      ${COREGRAPHICS_FRAMEWORK} 
      ${COCOA_FRAMEWORK} 
      ${APPLICATIONSERVICES_FRAMEWORK}
      ${CARBON_FRAMEWORK}
      ${CORESERVICES_FRAMEWORK}
      ${COREFOUNDATION_FRAMEWORK}
      ${COREVIDEO_FRAMEWORK}
      ${QUARTZ_FRAMEWORK}
  )
  if(UNIFORMTYPEIDENTIFIERS_FRAMEWORK)
    list(APPEND EXTRA_LIBS ${UNIFORMTYPEIDENTIFIERS_FRAMEWORK})
  endif()
else()
  set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")
  set(EXTRA_LIBS "")
endif()

add_subdirectory(../fltk ThirdParty/fltk)

# fltk_all: headers, libraries
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE ../fltk ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/fltk)
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
if(APPLE)
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  find_package(X11 QUIET)
  target_include_directories(RayTracer PRIVATE
    include/
    ${X11_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
    ${JPEG_INCLUDE_DIRS}
  )
  target_link_libraries(RayTracer PRIVATE
    ${X11_LIBRARIES}
    ${PNG_LIBRARIES}
    ${JPEG_LIBRARIES}
  )
else()
  target_include_directories(RayTracer PRIVATE include/)
endif()
target_link_libraries(RayTracer PRIVATE fltk_all ${EXTRA_LIBS})

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RayTracer)
