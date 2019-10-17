#include "Tokens.hpp"

#include <iostream>

using namespace Compiler;

const char* Compiler::tok_to_string( Token t ){
#define TOKEN( t ) case t: return #t;
	switch( t ){
		TOKENS
	}
#undef TOKEN

	throw std::runtime_error( "Could not convert token to string" );
}
inline static void err( Token t ){
	std::cout << "Missing expression for operator \"" << tok_to_string( t ) << "\"" << std::endl;
}

Operator tok_to_op( Token t, bool lhs, bool rhs ){
	if( !lhs && !rhs )

	switch( t ){
		case tok_scope_res:
			if( lhs && rhs )
				return op_scope_res;
			goto lerr;
		case tok_inc:
			if( lhs && !rhs )
				return op_post_inc;
			else if( !lhs && rhs )
				return op_pre_inc;
			goto lerr;
		case tok_dec:
			if( lhs && !rhs )
				return op_post_dec;
			else if( !lhs && rhs )
				return op_pre_dec;
			goto lerr;
		case tok_brak_round_open:
			if( lhs && rhs )
				return op_call;
			goto lerr;
		case tok_brak_square_open:
			if( lhs && rhs )
				return op_array;
			goto lerr;
		case tok_dot:
			if( lhs && rhs )
				return op_member;
			goto lerr;
		case tok_add:
			if( lhs && rhs )
				return op_add;
			else if( !lhs && rhs )
				return op_plus;
			goto lerr;
		case tok_sub:
			if( lhs && rhs )
				return op_sub;
			else if( !lhs && rhs )
				return op_minus;
			goto lerr;
		case tok_not:
			if( !lhs && rhs )
				return op_not;
			goto lerr;
			//TODO Operator.hpp:21
	}

lerr:
	err( t );
	return op_error;
}
