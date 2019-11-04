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
		unexpected_tok( tokenizer.curr_tok(), "\"{\"" );
		return nullptr;
	}

	while( !check( tokenizer.next_tok(), tok_brak_curly_close )){
		Stmt* stmt = parseStmt();
		if( stmt == nullptr ){
			return nullptr;
		}
		node->stmts.emplace_back( stmt );
	}

	return node;
}

Stmt* Parser::parseStmt() {
	
	curr_precedence = 12;
	auto tmp = parseExpr();
	std::cout << "  stmtend" << std::endl;
	if( check( tokenizer.curr_tok(), tok_semicolon ))
		return new StmtExprSemicolon{ std::unique_ptr<Expr>( tmp )};
	else {
		unexpected_tok( tokenizer.curr_tok(), "\";\"" );
		return nullptr;
	}
}

Expr* Parser::parseExpr() {
	Expr* ret;
	ParsedToken tok = tokenizer.curr_tok();

	std::cout << "    " << tok_to_string( tok.token ) << std::endl;

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
			{
				unsigned short temp_prec = curr_precedence;
				curr_precedence = 12;
				tokenizer.next_tok();
				ret = parseExpr();
				if( !check( tokenizer.curr_tok(), tok_brak_round_close )){
					unexpected_tok( tokenizer.curr_tok(), "\")\"" );
				}
				curr_precedence = temp_prec;
			}
			break;
		default:
			if( tok_to_op( tok.token, false ) != op_error ){
				ret = parsePreUnop();
				goto LPreUnop;
			}
			std::cout << "asdf " << tok_to_string( tok.token ) << std::endl;
			return nullptr;
	}

	std::cout << tok_to_string( tokenizer.peek_tok().token ) << std::endl;
	tokenizer.next_tok();
	//Every path exept default needs the next_tok call
LPreUnop:
	Operator op;
	while(( op = tok_to_op( tokenizer.curr_tok().token, true )) != op_error ){
		std::cout << precedence( op ) << " " << curr_precedence << std::endl;
		if( precedence( op ) < curr_precedence ){
			unsigned short temp_prec = curr_precedence;
			curr_precedence = precedence( op );
			ret = parseOp( ret );
			curr_precedence = temp_prec;
		}
		else if( precedence( op ) == curr_precedence && !left_to_right( op ))
			ret = parseOp( ret );
		else
			break;
	}

	return ret;
}

Expr* Parser::parseOp( Expr* lhs ) {
	Token temp = tokenizer.curr_tok().token;
	Operator op = tok_to_op( temp, true );
	if( unop( op )){
		tokenizer.next_tok();
		lhs = new Unop( std::unique_ptr<Expr>( lhs ), op );
		if( tokenizer.curr_tok().token == tok_semicolon )
			return lhs;
		return parseOp( lhs );
	}
	tokenizer.next_tok();
	return new Binop( std::unique_ptr<Expr>( lhs ), std::unique_ptr<Expr>( parseExpr()), op );
}

Expr* Parser::parsePreUnop() {
	Token temp = tokenizer.curr_tok().token;
	tokenizer.next_tok();
	unsigned short temp_prec = curr_precedence;
	curr_precedence = precedence( tok_to_op( temp, false ));
	Expr* ex = new Unop( std::unique_ptr<Expr>( parseExpr()), tok_to_op( temp, false ));
	curr_precedence = temp_prec;

	std::cout << "a " << tok_to_string( tokenizer.curr_tok().token ) << std::endl;

	return ex;

}
