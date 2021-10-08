cmake_minimum_required(VERSION 3.16) 
project(TacticsGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Create compile comands
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}) 

# Enable multithreading
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set(USE_FLAGS "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='['png']' --preload-file ../data -O3")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
	set(CMAKE_EXECUTABLE_SUFFIX .html)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/web) 
else()
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	include_directories("${SDL2_INCLUDE_DIRS}" "${SDL2_IMAGE_INCLUDE_DIRS}")
endif()

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")

# Add source libs
add_subdirectory("lib/Lua5.4")

# build
include_directories("include")
file(GLOB SOURCES "src/*.cpp")
add_executable(game "${SOURCES}")
target_link_libraries(game 
    "${SDL2_LIBRARIES}" 
    "${SDL2_IMAGE_LIBRARIES}"
    "${CMAKE_THREAD_LIBS_INIT}"
    "LuaLib")
