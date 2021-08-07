#!/bin/bash

echo
echo "------------------------------"
echo "        Starting build"
echo "------------------------------"
echo

# check for cmake
if ! command -v cmake; then
	echo "CMake is required for this build!"
	exit 1
fi
echo "CMake was found"
echo
	

# check for ~ LUA ~
if test -f "./lib/Lua5.4/lua.hpp"; then
	echo "LUA is present"
else
	# Check for curl in PATH
	if ! command -v curl; then
		echo "Lua is not present" 
		echo "For auto download curl is required!"
		exit 1
	fi

	# Check for tar in PATH
	if ! command -v tar; then
		echo "Lua is not present" 
		echo "For auto download tar is required!"
		exit 1
	fi

	echo "LUA is not present, downloading"
	curl https://www.lua.org/ftp/lua-5.4.3.tar.gz -o lua-5.4.3.tar.gz
	echo

	echo "Unpacking LUA"
	tar -xzf lua-5.4.3.tar.gz
	mv lua-5.4.3/src/* lib/Lua5.4
	echo

	echo "Deleting reaming files after LUA download"
	rm -r lua-5.4.3*
fi
echo

# check for build directory
if ! test -d "./build"; then
	mkdir build
fi

cd build

cmake ..
echo 

make
