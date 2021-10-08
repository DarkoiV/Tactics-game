#!/bin/sh

# Method for cheking if command exists
require () {
	if ! command -v $1; then
		echo "$1 is required"
		exit 1
	fi
	echo "$1 was found"
	echo
}

# Exit if command fails
must () {
	$1
	if test $? -ne 0; then
		echo
		echo "command \" $1 \" ended with non zero"
		exit $?
	fi
	echo
}

echo
echo "------------------------------"
echo "        Starting build"
echo "------------------------------"
echo

# default build folder
BUILD_FOLDER=linux_build

# check for cmake
require "cmake"

# -w enables web build mode
if test "$1" = "-w"; then
	BUILD_FOLDER=web_build
	require "emcc"
	require "emcmake" 
	require "emmake"
fi

# check for ~ LUA ~
if test -f "./lib/Lua5.4/lua.hpp"; then
	echo "LUA source found"
else
	echo "Downloading LUA source"
	require "curl"
	require "tar"

	must "curl https://www.lua.org/ftp/lua-5.4.3.tar.gz -o lua-5.4.3.tar.gz"

	echo "Unpacking LUA"
	must "tar -xzf lua-5.4.3.tar.gz"

	must "mv lua-5.4.3/src/* lib/Lua5.4"

	echo "Deleting remaing files after LUA download"
	rm -r lua-5.4.3*
fi
echo

# check for build directory
if ! test -d "./$BUILD_FOLDER"; then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
if test "$1" = "-w"; then
	must "emcmake cmake .."
	must "emmake make"
else
	must "cmake .."
	must "make"
fi

echo
echo "------------------------------"
echo "        BUILD COMPLETED"
echo "------------------------------"
echo
