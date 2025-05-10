CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(Impressionist CXX)

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
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE ../fltk ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/fltk)
target_link_libraries(fltk_all INTERFACE fltk fltk_gl fltk_images)

# fltk_hello
add_executable(fltk_hello fltk_hello.cpp)
target_link_libraries(fltk_hello PRIVATE fltk_all ${EXTRA_LIBS})

set(Impressionist_SRC
  src/impressionist.cpp
  src/bitmap.cpp
  src/FltDesignUI.cpp
  src/impBrush.cpp
  src/impressionistDoc.cpp
  src/impressionistUI.cpp
  src/originalView.cpp
  src/paintView.cpp
  src/pointBrush.cpp
  src/triangleBrush.cpp
  src/circleBrush.cpp
  src/lineBrush.cpp
  src/starBrush.cpp
  src/heartBrush.cpp
  src/scatteredPointBrush.cpp
  src/scatteredCircleBrush.cpp
)

add_executable(Impressionist ${Impressionist_SRC})
target_include_directories(Impressionist PRIVATE include/)
target_link_libraries(Impressionist PRIVATE fltk_all ${EXTRA_LIBS})

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Impressionist)