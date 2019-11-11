#pragma once

#include <memory>
#include <vector>

#include "Operator.hpp"

namespace AST {

	struct Visitor;

	struct Node {
		virtual ~Node() = default;
		virtual void accept( Visitor& v ) = 0;
	};

	struct Expr: public Node {
		virtual ~Expr() = default;
		virtual void accept( Visitor& v ) = 0;
	};

	struct OpExpr: public Node {
		virtual ~OpExpr() = default;
		virtual void accept( Visitor& v );

		std::unique_ptr<Expr> expr;
	};

	struct Number: public Expr {
		Number( double number ): value( number ){}
		virtual ~Number() = default;
		virtual void accept( Visitor& v );

		double value;
	};
	struct Identifier: public Expr {
		Identifier( std::string str ): name( str ){}
		virtual ~Identifier() = default;
		virtual void accept( Visitor& v );

		std::string name;
	};
	struct String: public Expr {
		String( std::string str ): value( str ){}
		virtual ~String() = default;
		virtual void accept( Visitor& v );

		std::string value;
	};
	struct Boolean: public Expr {
		Boolean( bool value ): value( value ){}
		virtual ~Boolean() = default;
		virtual void accept( Visitor& v );

		bool value;
	};

	struct Binop: public Expr {
		Binop( std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs, Compiler::Operator op ): lhs( std::move( lhs )), rhs( std::move( rhs )), op( op ){}
		virtual ~Binop() = default;
		virtual void accept( Visitor& v );

		std::unique_ptr<Node> lhs;
		std::unique_ptr<Node> rhs;
		Compiler::Operator op;
	};

	struct CallOp: public Expr {
		CallOp( std::unique_ptr<Identifier> identifier, std::unique_ptr<Expr> args, Compiler::Operator op ): id( std::move( identifier )), args( std::move( args )), op( op ){}
		virtual ~CallOp() = default;
		virtual void accept( Visitor& v );

		std::unique_ptr<Identifier> id;
		std::unique_ptr<Expr> args;
		Compiler::Operator op;
	};

	struct Unop: public Expr {
		Unop( std::unique_ptr<Expr>&& val, Compiler::Operator op ): val( move( val )), op( op ){}
		virtual ~Unop() = default;
		virtual void accept( Visitor& v );

		std::unique_ptr<Expr> val;
		Compiler::Operator op;
	};


	struct Stmt: public Node {
		virtual ~Stmt() = default;
		virtual void accept( Visitor& v ) = 0;
	};

	// Stmt -> Expr ';'
	struct StmtExprSemicolon: public Stmt {
		StmtExprSemicolon( std::unique_ptr<Expr>&& expr ): expr( move( expr )){}
		virtual ~StmtExprSemicolon() = default;
		virtual void accept( Visitor& v );

		std::unique_ptr<Expr> expr;
	};

	struct StmtList: public Stmt {
		virtual ~StmtList() = default;
		virtual void accept( Visitor& v );

		std::vector<std::unique_ptr<Stmt>> stmts;
	};

	struct Visitor {

#define ELEMENTS						\
		ELEMENT( Node )					\
		ELEMENT( OpExpr )				\
		ELEMENT( Expr )					\
		ELEMENT( Number )				\
		ELEMENT( Identifier )			\
		ELEMENT( String )				\
		ELEMENT( Boolean )				\
		ELEMENT( Binop )				\
		ELEMENT( CallOp )				\
		ELEMENT( Unop )					\
		ELEMENT( Stmt )					\
		ELEMENT( StmtExprSemicolon )	\
		ELEMENT( StmtList )
#define ELEMENT( e ) virtual void visit( e* ) = 0;
		ELEMENTS
#undef ELEMENT
	};
}
