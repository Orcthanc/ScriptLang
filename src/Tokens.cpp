#include "Tokens.hpp"

const char* Compiler::tok_to_string( Token t ){
#define TOKEN( t ) case t: return #t;
	switch( t ){
		TOKENS
	}
#undef TOKEN

	throw std::runtime_error( "Could not convert token to string" );
}

