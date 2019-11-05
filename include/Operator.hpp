#pragma once

#include <string>

namespace Compiler {
#define OPERATORS										\
	OPERATOR( op_error )								\
	OPERATOR( op_scope_res )				/* :: */	\
	OPERATOR( op_post_inc )					/* ++ */	\
	OPERATOR( op_post_dec )					/* -- */	\
	OPERATOR( op_call )						/* f() */	\
	OPERATOR( op_array )					/* a[] */	\
	OPERATOR( op_member )					/* . */		\
														\
	OPERATOR( op_pre_inc )					/* ++ */	\
	OPERATOR( op_pre_dec )					/* -- */	\
	OPERATOR( op_plus )						/* + */		\
	OPERATOR( op_minus )					/* - */		\
	OPERATOR( op_not )						/* ~ */		\
														\
	OPERATOR( op_mul )						/* * */		\
	OPERATOR( op_div )						/* / */		\
	OPERATOR( op_mod )						/* % */		\
														\
	OPERATOR( op_add )						/* + */		\
	OPERATOR( op_sub )						/* - */		\
														\
	OPERATOR( op_left_shift )				/* << */	\
	OPERATOR( op_right_shift )				/* >> */	\
														\
	OPERATOR( op_lt )						/* < */		\
	OPERATOR( op_le )						/* <= */	\
	OPERATOR( op_gt )						/* > */		\
	OPERATOR( op_ge )						/* >= */	\
														\
	OPERATOR( op_eq )						/* == */	\
	OPERATOR( op_ne )						/* != */	\
														\
	OPERATOR( op_and )						/* & */		\
	OPERATOR( op_xor )						/* ^ */		\
	OPERATOR( op_ior )						/* | */		\
														\
	OPERATOR( op_asg )						/* = */		\
	OPERATOR( op_asg_add )					/* += */	\
	OPERATOR( op_asg_sub )					/* -= */	\
	OPERATOR( op_asg_mul )					/* *= */	\
	OPERATOR( op_asg_div )					/* /= */	\
	OPERATOR( op_asg_mod )					/* %= */	\
	OPERATOR( op_asg_and )					/* &= */	\
	OPERATOR( op_asg_xor )					/* ^= */	\
	OPERATOR( op_asg_ior )					/* |= */	\
														\
	OPERATOR( op_comma )

	enum Operator {
#define OPERATOR( e ) e,
		OPERATORS
#undef OPERATOR
	};

	extern const char* op_to_string( Operator o );
	extern const char* op_to_symbol( Operator o );
	extern size_t precedence( Operator o );
	extern bool left_to_right( Operator o );
	extern bool unop( Operator o );
}
