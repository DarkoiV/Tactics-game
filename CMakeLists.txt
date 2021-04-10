cmake_minimum_required(VERSION 3.16) 
project(TacticsGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Enable multithreading
find_package(Threads REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories("${SDL2_INCLUDE_DIRS}" "${SDL2_IMAGE_INCLUDE_DIRS}")

file(GLOB SOURCES "src/*.cpp")
add_executable(TacticsGame "${SOURCES}")
target_link_libraries(TacticsGame "${SDL2_LIBRARIES}" "${SDL2_IMAGE_LIBRARIES}")
target_link_libraries(TacticsGame "${CMAKE_THREAD_LIBS_INIT}")
