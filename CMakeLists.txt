cmake_minimum_required(VERSION 3.12)
project(softrender
  VERSION 1.0
  LANGUAGES CXX
)

add_subdirectory(dependencies)

add_executable(helloworld src/helloworld.cpp)
target_link_libraries(helloworld PRIVATE PixelToaster)
target_include_directories(helloworld PRIVATE dependencies/pixeltoaster)