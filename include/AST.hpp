#pragma once

#include <memory>
#include <vector>

namespace AST {

#define UNOPS										\
	UNOP( PostInc );								\
	UNOP( PostDec );								\
	UNOP( PreInc );									\
	UNOP( PreDec );									\
	UNOP( Plus );									\
	UNOP( Minus );									\
	UNOP( Not );

#define BINOPS					\
	BINOP( Asg )				\
	BINOP( Add )				\
	BINOP( Sub )				\
	BINOP( Mul )				\
	BINOP( Div )				\
	BINOP( And )				\
	BINOP( Xor )				\
	BINOP( Ior )				\
								\
	BINOP( AsgAdd )				\
	BINOP( AsgSub )				\
	BINOP( AsgMul )				\
	BINOP( AsgDiv )				\
	BINOP( AsgAnd )				\
	BINOP( AsgXor )				\
	BINOP( AsgIor )


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
		virtual ~Binop() = default;
		virtual void accept( Visitor& v ) = 0;

		std::unique_ptr<Node> lhs;
		std::unique_ptr<Node> rhs;
	};
#define BINOP( name )								\
	struct name: public Binop {						\
		virtual ~name() = default;					\
		virtual void accept( Visitor& v );			\
	};
	BINOPS
#undef BINOP


	struct Unop: public Expr {
		Unop( std::unique_ptr<Expr>&& val ): val( move( val )){}
		virtual ~Unop() = default;
		virtual void accept( Visitor& v ) = 0;

		std::unique_ptr<Expr> val;
	};


#define UNOP( name )												\
	struct name: public Unop {										\
		name( std::unique_ptr<Expr>( val )): Unop( move( val )){}	\
		virtual ~name() = default;									\
		virtual void accept( Visitor& v );							\
	};
	UNOPS
#undef UNOP


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

	struct Function: public Node {
		virtual ~Function() = default;
		virtual void accept( Visitor& v );

		std::vector<std::unique_ptr<Stmt>> stmts;
	};

	struct Visitor {
#define UNOP( name )					\
		ELEMENT( name )
#define BINOP( name )					\
		ELEMENT( name )

#define ELEMENTS						\
		UNOPS							\
		BINOPS							\
		ELEMENT( Node )					\
		ELEMENT( OpExpr )				\
		ELEMENT( Expr )					\
		ELEMENT( Number )				\
		ELEMENT( Identifier )			\
		ELEMENT( String )				\
		ELEMENT( Boolean )				\
		ELEMENT( Binop )				\
		ELEMENT( Stmt )					\
		ELEMENT( StmtExprSemicolon )	\
		ELEMENT( Function )
#define ELEMENT( e ) virtual void visit( e* ) = 0;
		ELEMENTS
#undef ELEMENT
	};
}
