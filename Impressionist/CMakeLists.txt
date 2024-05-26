CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(Impressionist CXX)

set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")

add_subdirectory(../fltk ThirdParty/fltk)

# fltk_all: headers, libraries
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE ../fltk ${CMAKE_CURRENT_BINARY_DIR}/fltk)
target_link_libraries(fltk_all INTERFACE fltk fltk_gl fltk_images)

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
  src/scatteredPointBrush.cpp
  src/scatteredCircleBrush.cpp
)

add_executable(Impressionist ${Impressionist_SRC})
target_include_directories(Impressionist PRIVATE include/)
target_link_libraries(Impressionist PRIVATE fltk_all)

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Impressionist)

