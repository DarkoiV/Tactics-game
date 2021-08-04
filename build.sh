#!/bin/bash

echo "--------------"
echo "Starting build"
echo "--------------"
echo

# check for ~ LUA ~
if test -f "./lib/Lua5.4/lua.hpp"; then
	echo "LUA is present"
else
	echo "LUA is not present, downloading"
	curl https://www.lua.org/ftp/lua-5.4.3.tar.gz -o lua-5.4.3.tar.gz
	echo

	echo "Unpacking LUA"
	tar -xzf lua-5.4.3.tar.gz
	mv lua-5.4.3/src/* lib/Lua5.4
	echo

	echo "Deleting reaming files from LUA download"
	rm -r lua-5.4.3*
	echo
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
