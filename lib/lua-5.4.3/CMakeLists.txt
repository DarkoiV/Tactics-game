cmake_minimum_required(VERSION 3.16)

project( LuaLib )

file( GLOB LUA_RUNTIME_SOURCES "src/*.c" "src/*.hpp" "src/*.h")
  
add_library( LuaLib ${LUA_RUNTIME_SOURCES} )

target_include_directories ( LuaLib PUBLIC "src/")
