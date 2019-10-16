#include "Operator.hpp"

#include <stdexcept>

using namespace Compiler;

const char* Compiler::op_to_string( Operator o ){
	switch( o ){
#define OPERATOR( e ) case e: return #e;
		OPERATORS
#undef OPERATOR
		default:
			throw std::runtime_error( "Could not convert operator to string" );
	}
}

size_t Compiler::precedence( Operator o ){
	switch( o ){
		case op_scope_res:
			return 0;
		case op_post_inc:
		case op_post_dec:
		case op_call:
		case op_array:
		case op_member:
			return 1;
		case op_pre_inc:
		case op_pre_dec:
		case op_plus:
		case op_minus:
		case op_not:
			return 2;
		case op_mul:
		case op_div:
		case op_mod:
			return 3;
		case op_add:
		case op_sub:
			return 4;
		case op_shift_left:
		case op_shift_right:
			return 5;
		case op_lt:
		case op_le:
		case op_gt:
		case op_ge:
			return 6;
		case op_eq:
		case op_ne:
			return 7;
		case op_and:
			return 8;
		case op_xor:
			return 9;
		case op_ior:
			return 10;
		case op_asg:
		case op_asg_add:
		case op_asg_sub:
		case op_asg_mul:
		case op_asg_div:
		case op_asg_mod:
		case op_asg_and:
		case op_asg_xor:
		case op_asg_ior:
			return 11;
		default:
			return -1;
	}
}

bool Compiler::left_to_right( Operator o ){
	switch( o ){
		case op_scope_res:
		case op_post_inc:
		case op_post_dec:
		case op_call:
		case op_array:
		case op_member:
		case op_mul:
		case op_div:
		case op_mod:
		case op_add:
		case op_sub:
		case op_shift_left:
		case op_shift_right:
		case op_lt:
		case op_le:
		case op_gt:
		case op_ge:
		case op_eq:
		case op_ne:
		case op_and:
		case op_xor:
		case op_ior:
			return true;
		default:
			return false;
	}
}
