cmake_minimum_required(VERSION 3.16) 
project(TacticsGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Create compile comands
set(CMAKE_EXPORT_COMPILE_COMMANDS)

# Enable multithreading
find_package(Threads REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories("${SDL2_INCLUDE_DIRS}" "${SDL2_IMAGE_INCLUDE_DIRS}")

# Add source libs
add_subdirectory("lib/lua-5.4.3")

# build
file(GLOB SOURCES "src/*.cpp")
add_executable(TacticsGame "${SOURCES}")
target_link_libraries(TacticsGame 
    "${SDL2_LIBRARIES}" 
    "${SDL2_IMAGE_LIBRARIES}"
    "${CMAKE_THREAD_LIBS_INIT}"
    "LuaLib")
