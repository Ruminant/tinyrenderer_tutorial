cmake_minimum_required(VERSION 3.12)
project(softrender
  VERSION 1.0
  LANGUAGES CXX
)

add_subdirectory(dependencies)

add_library(tinyrenderer 
  src/image.h
  src/image.cpp
  src/line.h
  src/line.cpp
  src/model.h
  src/model.cpp
  src/triangle.h
  src/triangle.cpp
)
target_link_libraries(tinyrenderer PRIVATE PixelToaster)
target_include_directories(tinyrenderer 
  PUBLIC src
  PRIVATE dependencies/pixeltoaster)

add_executable(helloworld src/helloworld.cpp)
target_link_libraries(helloworld PRIVATE PixelToaster)
target_include_directories(helloworld PRIVATE dependencies/pixeltoaster)

add_executable(linedrawing src/linedrawing.cpp)
target_link_libraries(linedrawing PRIVATE tinyrenderer)

add_executable(modeldraw src/modeldraw.cpp)
target_link_libraries(modeldraw PRIVATE tinyrenderer)
target_compile_features(modeldraw PRIVATE cxx_std_17)

add_executable(tridraw src/tridraw.cpp)
target_link_libraries(tridraw PRIVATE tinyrenderer)
