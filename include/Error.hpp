#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

#include "Tokens.hpp"

inline void error( std::string message ){
	throw new std::runtime_error( message );
}

inline void unexpected_tok( Compiler::ParsedToken tok, const std::string& expected ){
	std::cout << "Unexpected token \"" << tok_to_string( tok.token ) << "\" on line " << tok.line_number << ". Expected " << expected << "." << std::endl;
}
