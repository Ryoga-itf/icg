CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(Modeler CXX)

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

# GL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_subdirectory(../fltk ThirdParty/fltk)

# fltk_all: headers, libraries
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE ../fltk ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/fltk)
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
if(APPLE)
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  find_package(X11 QUIET)
  target_include_directories(Modeler PRIVATE
    include/
    ${X11_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
    ${JPEG_INCLUDE_DIRS}
  )
  target_link_libraries(Modeler PRIVATE
    ${X11_LIBRARIES}
    ${PNG_LIBRARIES}
    ${JPEG_LIBRARIES}
  )
else()
  target_include_directories(Modeler PRIVATE include/)
endif()
target_link_libraries(Modeler PRIVATE fltk_all OpenGL::GLU ${EXTRA_LIBS})

add_executable(Robotarm ${Robotarm_SRC})
if(APPLE)
  find_package(X11 QUIET)
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  target_include_directories(Robotarm PRIVATE
    include/
    ${X11_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
    ${JPEG_INCLUDE_DIRS}
  )
  target_link_libraries(Robotarm PRIVATE
    ${X11_LIBRARIES}
    ${PNG_LIBRARIES}
    ${JPEG_LIBRARIES}
  )
else()
  target_include_directories(Robotarm PRIVATE include/)
endif()
target_link_libraries(Robotarm PRIVATE fltk_all OpenGL::GLU ${EXTRA_LIBS})

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Modeler)
