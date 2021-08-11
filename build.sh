#!/bin/bash

# Method for cheking if command exists
require () {
	if ! command -v $1; then
		echo "$1 is required"
		exit 1
	fi
	echo "$1 was found"
	echo
}

echo
echo "------------------------------"
echo "        Starting build"
echo "------------------------------"
echo

# check for cmake
require cmake	

# check for ~ LUA ~
if test -f "./lib/Lua5.4/lua.hpp"; then
	echo "LUA is present"
else
	echo "Downloading LUA"
	require curl
	require tar

	echo "LUA is not present, downloading"
	curl https://www.lua.org/ftp/lua-5.4.3.tar.gz -o lua-5.4.3.tar.gz
	if test $? -ne 0; then
		echo "curl ended with non zero"
		exit 1
	fi
	echo

	echo "Unpacking LUA"
	tar -xzf lua-5.4.3.tar.gz
	if test $? -ne 0; then
		echo "tar ended with non zero"
		exit 1
	fi

	mv lua-5.4.3/src/* lib/Lua5.4
	echo

	echo "Deleting remaing files after LUA download"
	rm -r lua-5.4.3*
fi
echo

# check for build directory
if ! test -d "./build"; then
	mkdir build
fi

cd build

cmake ..
if test $? -ne 0; then
	echo "Cmake ended with non zero"
	exit 1
fi
echo 

make
