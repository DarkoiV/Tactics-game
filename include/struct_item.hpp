#pragma once

#include "enums.hpp"
#include <string>

// Struct holding information about item
struct sItem{
	std::string id;
	eITEM       type;
	int         level;
};
