#include "Parser.hpp"

#include <iostream>

#include "Error.hpp"

using namespace Compiler;
using namespace AST;

static bool check( const ParsedToken& tok, Token against ) noexcept{
	return tok.token == against;
}

std::unique_ptr<Node> Parser::operator()(){
	return { std::unique_ptr<Node>( parseFunction() )};
}

Function* Parser::parseFunction() noexcept{
	//TODO func tok_id( parameters )
	
	Function* node = new Function;
	// {
	if( !check( tokenizer.next_tok(), tok_brak_curly_open )){
		std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \"{\"" << std::endl;
		return nullptr;
	}

	while( !check( tokenizer.next_tok(), tok_brak_curly_close )){
		Stmt* stmt = parseStatement();
		if( stmt == nullptr ){
			std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\"" << std::endl;
			return nullptr;
		}
		node->stmts.emplace_back( stmt );
	}

	return node;
}

Stmt* Parser::parseStatement() noexcept {
	auto tmp = parseBinopExpr();
	if( check( tokenizer.curr_tok(), tok_semicolon ))
		return new StmtExprSemicolon{ std::unique_ptr<Expr>( tmp )};
	else {
		std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \";\"" << std::endl;
		return nullptr;
	}
}

Expr* Parser::parseBinopExpr() noexcept {
	Expr* ret;
	ParsedToken tok = tokenizer.curr_tok();

	std::cout << tok_to_string( tok.token ) << std::endl;

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
			ret = parseBinopExpr();
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

Expr* Parser::parseExpression() noexcept {
#if 0
	Expr* ret;
	//TODO Replace with curr_tok
	auto tok = tokenizer.peek_tok();

	std::cout << tok_to_string( tok.token ) << std::endl;
	switch( tok.token ){
		case tok_brak_round_open:
			tokenizer.next_tok();
			ret = parseExpression();
			if( tokenizer.peek_tok().token != tok_brak_round_close ){
				std::cout << "Unexpected token \"" << tok_to_string( tokenizer.peek_tok().token ) << "\" expected \")\"" << std::endl;
			} else
				tokenizer.next_tok();
			break;
		case tok_str_lit:
			ret = new String( std::static_pointer_cast<MetadataString>( tok.metadata )->string );
			tokenizer.next_tok();
			break;
		case tok_id:
			ret = new Identifier( std::static_pointer_cast<MetadataString>( tok.metadata )->string );
			tokenizer.next_tok();
			break;
		case tok_num_lit:
			ret = new Number( std::static_pointer_cast<MetadataNum>( tok.metadata )->number );
			tokenizer.next_tok();
			break;
		case tok_true:
			ret = new Boolean( true );
			tokenizer.next_tok();
			break;
		case tok_false:
			ret = new Boolean( false );
			tokenizer.next_tok();
			break;
		default:
			{
				if( tok_to_op( tok.token, false ) != op_error ){
					//TODO complete and move to parseBinopExpr
					std::cout << "Found unop (unimplemented)" << std::endl;
					tokenizer.next_tok();
					return parseExpression();
				}
				return nullptr;
			}
	}
	return ret;
#endif
	return nullptr;
}

Expr* Parser::parseOp( Expr* lhs ) noexcept {
	//TODO
	std::cout << op_to_string( tok_to_op( tokenizer.curr_tok().token, true )) << std::endl;
	if( unop( tok_to_op( tokenizer.curr_tok().token, true ))){
		tokenizer.next_tok();
		if( tokenizer.curr_tok().token == tok_semicolon )
			return lhs;
		return parseOp( lhs );
	}
	tokenizer.next_tok();
	delete lhs;
	return parseBinopExpr();
}

Expr* Parser::parsePreUnop() noexcept {
	//TODO
	tokenizer.next_tok();
	return parseBinopExpr();
}
