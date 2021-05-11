cmake_minimum_required(VERSION 3.16)

project( LuaLib )

set( LUA_INCLUDES
	"lua.hpp"
	"lua.h"
	"lauxlib.h"
	"lualib.h"
	"luaconf.h")

set( LUA_CORE
	"lapi.c"      "lapi.h"
	"lcode.c"     "lcode.h"
	"lctype.c"    "lctype.h"
	"ldebug.c"    "ldebug.h"
	"ldo.c"       "ldo.h"
	"ldump.c"
	"lfunc.c"     "lfunc.h"
	"lgc.c"       "lgc.c"
	              "ljumptab.h"
	"llex.c"      "llex.h"
	              "llimits.h"
	"lmem.c"      "lmem.h"
	"lobject.c"   "lobject.h"
	"lopcodes.c"  "lopcodes.h"
	              "lopnames.h"
	"lparser.c"   "lparser.h"
	              "lprefix.h"
	"lstate.c"    "lstate.h"
	"lstring.c"   "lstring.h"
	"ltable.c"    "ltable.h"
	"ltm.c"       "ltm.h"
	"lundump.c"   "lundump.h"
	"lvm.c"       "lvm.h"
	"lzio.c"      "lzio.h")

set( LUA_LIBRARIES
	"lauxlib.c"
	"lbaselib.c"
	"lcorolib.c"
	"ldblib.c"
	"liolib.c"
	"lmathlib.c"
	"loadlib.c"
	"loslib.c"
	"lstrlib.c"
	"ltablib.c"
	"lutf8lib.c"
	"linit.c")
 
add_library( LuaLib "${LUA_INCLUDES}" "${LUA_CORE}" "${LUA_LIBRARIES}")

target_include_directories ( LuaLib PUBLIC "./")
