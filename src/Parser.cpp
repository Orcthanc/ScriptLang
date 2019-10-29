#include "Parser.hpp"

#include <iostream>

#include "Error.hpp"

using namespace Compiler;
using namespace AST;

static bool check( const ParsedToken& tok, Token against ){
	return tok.token == against;
}

std::unique_ptr<Node> Parser::operator()(){
	return { std::unique_ptr<Node>( parseFunc() )};
}

Function* Parser::parseFunc(){
	//TODO func tok_id( parameters )

	Function* node = new Function;
	// {
	if( !check( tokenizer.next_tok(), tok_brak_curly_open )){
		std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \"{\"" << std::endl;
		return nullptr;
	}

	while( !check( tokenizer.next_tok(), tok_brak_curly_close )){
		Stmt* stmt = parseStmt();
		if( stmt == nullptr ){
			std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\"" << std::endl;
			return nullptr;
		}
		node->stmts.emplace_back( stmt );
	}

	return node;
}

Stmt* Parser::parseStmt() {
	auto tmp = parseExpr();
	if( check( tokenizer.curr_tok(), tok_semicolon ))
		return new StmtExprSemicolon{ std::unique_ptr<Expr>( tmp )};
	else {
		std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \";\"" << std::endl;
		return nullptr;
	}
}

Expr* Parser::parseExpr() {
	Expr* ret;
	ParsedToken tok = tokenizer.curr_tok();

	switch( tok.token ){
		case tok_str_lit:
			ret = new String( std::static_pointer_cast<MetadataString>( tok.metadata )->string );
			break;
		case tok_id:
			ret = new Identifier( std::static_pointer_cast<MetadataString>( tok.metadata )->string );
			break;
		case tok_num_lit:
			ret = new Number( std::static_pointer_cast<MetadataNum>( tok.metadata )->number );
			break;
		case tok_true:
			ret = new Boolean( true );
			break;
		case tok_false:
			ret = new Boolean( false );
			break;
		case tok_brak_round_open:
			tokenizer.next_tok();
			ret = parseExpr();
			if( !check( tokenizer.curr_tok(), tok_brak_round_close )){
				std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \")\"" << std::endl;
			}
			break;
		default:
			if( tok_to_op( tok.token, false ) != op_error ){
				return parsePreUnop();
			}
			std::cout << "asdf " << tok_to_string( tok.token ) << std::endl;
			return nullptr;
	}

	if( tok_to_op( tokenizer.next_tok().token, true ) != op_error ){
		std::cout << "Found op \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" (unimplemented)"  << std::endl;
		ret = parseOp( ret );
	}

	return ret;
}

Expr* Parser::parseOp( Expr* lhs ) {
	//TODO
	//std::cout << op_to_string( tok_to_op( tokenizer.curr_tok().token, true )) << std::endl;
	Token temp = tokenizer.curr_tok().token;
	if( unop( tok_to_op( temp, true ))){
		tokenizer.next_tok();
		switch( tok_to_op( temp, true )){
			case op_post_inc:
				lhs = new PostInc( std::unique_ptr<Expr>( lhs ));
				break;
			case op_post_dec:
				lhs = new PostDec( std::unique_ptr<Expr>( lhs ));
				break;
			default:
				std::cout << "Invalid post-unop \"" << tok_to_op( tokenizer.curr_tok().token, false ) << "\"";
		}
		if( tokenizer.curr_tok().token == tok_semicolon )
			return lhs;
		return parseOp( lhs );
	}
	tokenizer.next_tok();
	delete lhs;
	return parseExpr();
}

Expr* Parser::parsePreUnop() {
	Token temp = tokenizer.curr_tok().token;
	tokenizer.next_tok();
	switch( tok_to_op( temp, false )){
		case op_pre_inc:
			return new PreInc( std::unique_ptr<Expr>( parseExpr()));
		case op_pre_dec:
			return new PreDec( std::unique_ptr<Expr>( parseExpr()));
		case op_plus:
			return new Plus( std::unique_ptr<Expr>( parseExpr()));
		case op_minus:
			return new Minus( std::unique_ptr<Expr>( parseExpr()));
		case op_not:
			return new Not( std::unique_ptr<Expr>( parseExpr()));
		default:
			std::cout << "Invalid pre-unop \"" << tok_to_op( tokenizer.curr_tok().token, false ) << "\"";
	}
	return nullptr;
}
