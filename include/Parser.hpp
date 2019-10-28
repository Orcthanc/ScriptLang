/*
 * 	binop ->
 * 		|	tok_add			//+
 * 		|	...
 * 		|	tok_asg			//=
 * 		|	tok_asg_add		//+=
 * 		|	...
 *
 *	expr ->
 *		|	tok_str_lit					// "asdf"
 *		|	tok_num_lit					// 1.3
 *		|	tok_identifier				// variablename
 *		|	tok_true					// true
 *		|	tok_false					// false
 *		|	tok_brak_round_open expr tok_brak_round_close		// ( expr )
 *		|	expr binop expr
 *
 *	stmt ->
 *		|	expr tok_semicolon			// ;
 *
 *	func ->
 *		|	tok_func tok_id tok_brak_round_open ((tok_id tok_comma)*)? tok_brak_round_close tok_brak_curly_open stmt* tok_brak_curly_close				// func name( par1, par2 ){ stmt* }
 */

#pragma once

#include "Tokens.hpp"
#include "Lexer.hpp"
#include "AST.hpp"

namespace Compiler {
	struct Parser {
		public:
			Parser( Tokenizer&& tokenizer ): tokenizer( std::move( tokenizer )){}

			std::unique_ptr<AST::Node> operator()();

		private:
			Tokenizer tokenizer;

			//AST::Node parseFileStart();
			//AST::Node parseNameSpace();
			//TODO
			AST::Function* parseFunc();
			AST::Stmt* parseStmt();
			AST::Expr* parseExpr();
			AST::Expr* parseOp( AST::Expr* lhs );
			AST::Expr* parsePreUnop();
	};
}
