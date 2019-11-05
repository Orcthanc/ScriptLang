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

const char* Compiler::tok_to_string( ParsedToken t ){
	return tok_to_string( t.token );
}

const Operator Compiler::tok_to_op( Token t, bool lhs ){
	switch( t ){
		case tok_scope_res:
			if( lhs )
				return op_scope_res;
			goto lerr;

		case tok_inc:
			if( lhs )
				return op_post_inc;
			else
				return op_pre_inc;

		case tok_dec:
			if( lhs )
				return op_post_dec;
			else
				return op_pre_dec;

		case tok_brak_round_open:
			if( lhs )
				return op_call;
			goto lerr;

		case tok_brak_square_open:
			if( lhs )
				return op_array;
			goto lerr;

		case tok_dot:
			if( lhs )
				return op_member;
			goto lerr;

		case tok_add:
			if( lhs )
				return op_add;
			else
				return op_plus;

		case tok_sub:
			if( lhs )
				return op_sub;
			else
				return op_minus;

		case tok_not:
			if( !lhs )
				return op_not;
			goto lerr;

		case tok_mul:
			if( lhs )
				return op_mul;
			goto lerr;

		case tok_div:
			if( lhs )
				return op_div;
			goto lerr;

		case tok_mod:
			if( lhs )
				return op_mod;
			goto lerr;

		case tok_left_shift:
			if( lhs )
				return op_left_shift;
			goto lerr;

		case tok_right_shift:
			if( lhs )
				return op_right_shift;
			goto lerr;

		case tok_lt:
			if( lhs )
				return op_lt;
			goto lerr;

		case tok_le:
			if( lhs )
				return op_le;
			goto lerr;

		case tok_gt:
			if( lhs )
				return op_gt;
			goto lerr;

		case tok_ge:
			if( lhs )
				return op_ge;
			goto lerr;

		case tok_eq:
			if( lhs )
				return op_eq;
			goto lerr;

		case tok_ne:
			if( lhs )
				return op_ne;
			goto lerr;

		case tok_and:
			if( lhs )
				return op_and;
			goto lerr;

		case tok_xor:
			if( lhs )
				return op_xor;
			goto lerr;

		case tok_ior:
			if( lhs )
				return op_ior;
			goto lerr;

		case tok_asg:
			if( lhs )
				return op_asg;
			goto lerr;

		case tok_asg_add:
			if( lhs )
				return op_asg_add;
			goto lerr;

		case tok_asg_and:
			if( lhs )
				return op_asg_and;
			goto lerr;

		case tok_asg_div:
			if( lhs )
				return op_asg_div;
			goto lerr;

		case tok_asg_ior:
			if( lhs )
				return op_asg_ior;
			goto lerr;

		case tok_asg_mod:
			if( lhs )
				return op_asg_mod;
			goto lerr;

		case tok_asg_mul:
			if( lhs )
				return op_asg_mul;
			goto lerr;

		case tok_asg_sub:
			if( lhs )
				return op_asg_sub;
			goto lerr;

		case tok_asg_xor:
			if( lhs )
				return op_asg_xor;
			goto lerr;

		case tok_brak_curly_close:
		case tok_brak_curly_open:
		case tok_brak_round_close:
		case tok_brak_square_close:
		case tok_comma:
		case tok_eof:
		case tok_error:
		case tok_false:
		case tok_for:
		case tok_id:
		case tok_logic_not:
		case tok_null:
		case tok_num_lit:
		case tok_semicolon:
		case tok_str_lit:
		case tok_true:
		case tok_while:
			goto lerr;
	}

lerr:
	return op_error;
}


const Operator Compiler::tok_to_op( ParsedToken t, bool lhs ){
	return tok_to_op( t.token, lhs );
}
