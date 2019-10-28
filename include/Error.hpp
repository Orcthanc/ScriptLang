#pragma once

#include <string>
#include <stdexcept>

inline void error( std::string message ){
	throw new std::runtime_error( message );
}
