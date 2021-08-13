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

# Exit if program fails
must () {
	$1
	if test $? -ne 0; then
		echo
		echo "command \" $1 \" ended with non zero"
		exit 1
	fi
	echo
}

echo
echo "------------------------------"
echo "        Starting build"
echo "------------------------------"
echo

# check for cmake
require "cmake"

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
if ! test -d "./build"; then
	mkdir build
fi

cd build

must "cmake .."

must "make"

echo
echo "------------------------------"
echo "        BUILD COMPLETED"
echo "------------------------------"
echo
