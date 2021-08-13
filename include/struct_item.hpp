#pragma once

#include "enums.hpp"
#include <string>

// Struct holding information about item
struct sItem{
	std::string name;
	eITEM       type;
	int         level;
};
