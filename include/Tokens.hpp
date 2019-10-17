#pragma once

#include <string>
#include <memory>

#include "Operator.hpp"

namespace Compiler {

#define TOKENS 															\
	/* Base */															\
	TOKEN( tok_eof )						/* end of file */			\
	TOKEN( tok_error )						/* errornous token */		\
	TOKEN( tok_num_lit )					/* number literal */		\
	TOKEN( tok_str_lit )					/* string literal */		\
	TOKEN( tok_id )							/* identifier */			\
	TOKEN( tok_asg )						/* = */						\
	TOKEN( tok_semicolon )					/* ; */						\
	TOKEN( tok_comma )						/* , */						\
	TOKEN( tok_scope_res )					/* :: */					\
	TOKEN( tok_dot )						/* . */						\
																		\
	/* Math */															\
	/* Arithmetic */													\
	TOKEN( tok_add )						/* + */						\
	TOKEN( tok_sub )						/* - */						\
	TOKEN( tok_mul )						/* * */						\
	TOKEN( tok_div )						/* / */						\
	TOKEN( tok_mod )						/* % */						\
	/* Bitwise */														\
	TOKEN( tok_not )						/* ~ */						\
	TOKEN( tok_and )						/* & */						\
	TOKEN( tok_xor )						/* ^ */						\
	TOKEN( tok_ior )						/* | */						\
	/* Assign */														\
	TOKEN( tok_asg_add )					/* += */					\
	TOKEN( tok_asg_sub )					/* -= */					\
	TOKEN( tok_asg_mul )					/* *= */					\
	TOKEN( tok_asg_div )					/* /= */					\
	TOKEN( tok_asg_mod )					/* %= */					\
	TOKEN( tok_asg_and )					/* &= */					\
	TOKEN( tok_asg_xor )					/* ^= */					\
	TOKEN( tok_asg_ior )					/* |= */					\
	/* Shortcut */														\
	TOKEN( tok_inc )						/* ++ */					\
	TOKEN( tok_dec )						/* -- */					\
	TOKEN( tok_left_shift )					/* << */					\
	TOKEN( tok_right_shift )				/* >> */					\
																		\
	/* Logic */															\
	TOKEN( tok_eq )							/* == */					\
	TOKEN( tok_ne )							/* != */					\
	TOKEN( tok_gt )							/* > */						\
	TOKEN( tok_ge )							/* >= */					\
	TOKEN( tok_lt )							/* < */						\
	TOKEN( tok_le )							/* <= */					\
	TOKEN( tok_logic_not )					/* ! */						\
																		\
	/* Brackets */														\
	TOKEN( tok_brak_round_open )			/* ( */						\
	TOKEN( tok_brak_round_close )			/* ) */						\
	TOKEN( tok_brak_square_open )			/* [ */						\
	TOKEN( tok_brak_square_close )			/* ] */						\
	TOKEN( tok_brak_curly_open )			/* { */						\
	TOKEN( tok_brak_curly_close )			/* } */						\
																		\
	/* Keywords */														\
	TOKEN( tok_true )						/* true */					\
	TOKEN( tok_false )						/* false */					\
	TOKEN( tok_for )						/* for */					\
	TOKEN( tok_while )						/* while */					\
	TOKEN( tok_null )						/* null */


#define TOKEN( t ) t,
	enum Token {
		TOKENS
	};
#undef TOKEN

	extern const char* tok_to_string( Token t );
	//lhs and rhs indicate if there are expressions to the left/right of the op, or if the operator is unary
	//tok_add, true, true -> op_add
	//tok_add, false, true -> op_plus
	extern const Operator tok_to_op( Token t, bool lhs, bool rhs );

	struct Metadata{};

	struct MetadataNum: public Metadata {
		MetadataNum( double val ): number( val ){}

		double number;
	};

	struct MetadataString: public Metadata {
		MetadataString( std::string s ): string( s ){}

		std::string string;
	};

	struct ParsedToken {
		ParsedToken( Token tok, std::unique_ptr<Metadata>&& metadata ): token( tok ), metadata( std::move( metadata )){}
		ParsedToken( Token tok ): token( tok ), metadata( nullptr ){}

		Token token;
		std::shared_ptr<Metadata> metadata;
	};
}
