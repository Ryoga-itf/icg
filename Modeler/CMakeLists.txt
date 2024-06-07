CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(Modeler CXX)

set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")

# GL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_subdirectory(../fltk ThirdParty/fltk)

# fltk_all: headers, libraries
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE ../fltk ${CMAKE_CURRENT_BINARY_DIR}/fltk)
target_link_libraries(fltk_all INTERFACE fltk fltk_gl fltk_images)

# Modeler
set(Modeler_SRC
  src/animatoruiwindows.cxx
  src/camera.cpp
  src/curve.cpp
  src/curveevaluator.cpp
  src/graphwidget.cpp
  src/imageio.cpp
  src/indicatorwindow.cpp
  src/linearcurveevaluator.cpp
  src/main.cpp
  src/modelerapp.cpp
  src/modelerdraw.cpp
  src/modelerui.cpp
  src/modelerview.cpp
  src/particleSystem.cpp
  src/point.cpp
  src/rect.cpp
  src/rulerwindow.cpp
)

# Robotarm
set(Robotarm_SRC
  src/animatoruiwindows.cxx
  src/camera.cpp
  src/curve.cpp
  src/curveevaluator.cpp
  src/graphwidget.cpp
  src/imageio.cpp
  src/indicatorwindow.cpp
  src/linearcurveevaluator.cpp
  src/modelerapp.cpp
  src/modelerdraw.cpp
  src/modelerui.cpp
  src/modelerview.cpp
  src/particleSystem.cpp
  src/point.cpp
  src/rect.cpp
  src/robotarm.cpp
  src/rulerwindow.cpp
)

add_executable(Modeler ${Modeler_SRC})
target_include_directories(Modeler PRIVATE include/)
target_link_libraries(Modeler PRIVATE fltk_all)
target_link_libraries(Modeler PRIVATE OpenGL::GLU)

add_executable(Robotarm ${Robotarm_SRC})
target_include_directories(Robotarm PRIVATE include/)
target_link_libraries(Robotarm PRIVATE fltk_all)
target_link_libraries(Robotarm PRIVATE OpenGL::GLU)

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Modeler)
