#include "Parser.hpp"

#include <iostream>

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
	if( check( tokenizer.peek_tok(), tok_brak_curly_open )){
		tokenizer.next_tok();
	} else {
		std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \"{\"" << std::endl;
		return nullptr;
	}

	while( !check( tokenizer.peek_tok(), tok_brak_curly_close )){
		std::cout << "stmt" << tok_to_string( tokenizer.peek_tok().token ) << std::endl;
		Stmt* stmt = parseStatement();
		if( stmt == nullptr ){
			std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\"" << std::endl;
			return nullptr;
		}
		node->stmts.emplace_back( stmt );
	}

	return node;
}

Stmt* Parser::parseStatement() noexcept{
	std::cout << "a" << tok_to_string( tokenizer.peek_tok().token ) << std::endl;
	auto tmp = parseExpression();
	if( check( tokenizer.next_tok(), tok_semicolon ))
		return new StmtExprSemicolon{ std::unique_ptr<Expr>( tmp )};
	else {
		std::cout << "Unexpected token \"" << tok_to_string( tokenizer.curr_tok().token ) << "\" expected \";\"" << std::endl;
		return nullptr;
	}
}

Expr* Parser::parseExpression() noexcept{
	Expr* ret;
	auto tok = tokenizer.peek_tok();

	std::cout << tok_to_string( tokenizer.peek_tok().token ) << std::endl;
	switch( tok.token ){
		case tok_brak_round_open:
			//TODO
			ret = nullptr;
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
		//TODO expr binop expr
		default:
			return nullptr;
	}
	return ret;
}
