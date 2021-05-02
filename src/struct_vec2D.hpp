#pragma once

#include <iostream>

struct vec2D{
	int x;
	int y;
};

inline std::ostream& operator << (std::ostream &os, const vec2D &s){
	return (os << s.x << "x" << s.y);
}
