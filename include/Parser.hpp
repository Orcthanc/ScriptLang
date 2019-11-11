/*
 * 	binop ->
 * 		|	tok_add			//+
 * 		|	...
 * 		|	tok_asg			//=
 * 		|	tok_asg_add		//+=
 * 		|	...
 *
 * 	unop ->
 * 		|	tok_add			//+
 * 		|	tok_not			//~
 * 		|	...
 *
 *	expr ->
 *		|	tok_str_lit																						// "asdf"				//parseExpr()
 *		|	tok_num_lit																						// 1.3					//parseExpr()
 *		|	tok_id																							// variablename			//parseExpr()
 *		|	tok_true																						// true					//parseExpr()
 *		|	tok_false																						// false				//parseExpr()
 *		|	tok_brak_round_open expr tok_brak_round_close													// ( expr )				//parseExpr()
 *		|	expr binop expr																					// 3 * 2				//parseExpr() -> parseOp()
 *		|	unop expr																						// -12					//parseExpr() -> parsePreUnop()
 *		|	expr unop																						// i++					//parseExpr() -> parseOp()
 *		|	tok_id tok_brak_(round|square)_open expr? (tok_semicolon expr)* tok_brak_(round|square)_close	// func( 12, "asfd" )	//parseExpr()
 *
 *	stmt ->
 *		|	expr tok_semicolon																				// asdf;				//parseStmt()
 *		|	tok_brak_curly_open stmt* tok_brak_curly_close													// { asdf; jkl; }		//parseStmt() -> parseStmtList()
 *
 *	func ->
 *		|	tok_func tok_id tok_brak_round_open ((tok_id tok_comma)*)? tok_brak_round_close stmt			// func name( par1, par2 ){ stmt* }
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
			AST::StmtList* parseStmtList();
			AST::Stmt* parseStmt();
			AST::Expr* parseExpr();
			unsigned short curr_precedence = 0;
			AST::Expr* parseOp( AST::Expr* lhs );
			AST::Expr* parsePreUnop();
	};
}
