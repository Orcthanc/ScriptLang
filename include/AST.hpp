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

	struct Asg: public Binop {
		virtual ~Asg() = default;
		virtual void accept( Visitor& v );
	};

	struct Add: public Binop {
		virtual ~Add() = default;
		virtual void accept( Visitor& v );
	};
	struct Sub: public Binop {
		virtual ~Sub() = default;
		virtual void accept( Visitor& v );
	};
	struct Mul: public Binop {
		virtual ~Mul() = default;
		virtual void accept( Visitor& v );
	};
	struct Div: public Binop {
		virtual ~Div() = default;
		virtual void accept( Visitor& v );
	};
	struct And: public Binop {
		virtual ~And() = default;
		virtual void accept( Visitor& v );
	};
	struct Xor: public Binop {
		virtual ~Xor() = default;
		virtual void accept( Visitor& v );
	};
	struct Ior: public Binop {
		virtual ~Ior() = default;
		virtual void accept( Visitor& v );
	};

	struct AsgAdd: public Binop {
		virtual ~AsgAdd() = default;
		virtual void accept( Visitor& v );
	};
	struct AsgSub: public Binop {
		virtual ~AsgSub() = default;
		virtual void accept( Visitor& v );
	};
	struct AsgMul: public Binop {
		virtual ~AsgMul() = default;
		virtual void accept( Visitor& v );
	};
	struct AsgDiv: public Binop {
		virtual ~AsgDiv() = default;
		virtual void accept( Visitor& v );
	};
	struct AsgAnd: public Binop {
		virtual ~AsgAnd() = default;
		virtual void accept( Visitor& v );
	};
	struct AsgXor: public Binop {
		virtual ~AsgXor() = default;
		virtual void accept( Visitor& v );
	};
	struct AsgIor: public Binop {
		virtual ~AsgIor() = default;
		virtual void accept( Visitor& v );
	};


	struct Unop: public Expr {
		virtual ~Unop() = default;
		virtual void accept( Visitor& v ) = 0;

		std::unique_ptr<Node> val;
	};


#define UNOP( name )								\
	struct name: public Unop {						\
		virtual ~name() = default;					\
		virtual void accept( Visitor& v );			\
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

#define ELEMENTS						\
		UNOPS							\
		ELEMENT( Node )					\
		ELEMENT( OpExpr )				\
		ELEMENT( Expr )					\
		ELEMENT( Number )				\
		ELEMENT( Identifier )			\
		ELEMENT( String )				\
		ELEMENT( Boolean )				\
		ELEMENT( Binop )				\
		ELEMENT( Asg )					\
		ELEMENT( Add )					\
		ELEMENT( Sub )					\
		ELEMENT( Mul )					\
		ELEMENT( Div )					\
		ELEMENT( And )					\
		ELEMENT( Xor )					\
		ELEMENT( Ior )					\
		ELEMENT( AsgAdd )				\
		ELEMENT( AsgSub )				\
		ELEMENT( AsgMul )				\
		ELEMENT( AsgDiv )				\
		ELEMENT( AsgAnd )				\
		ELEMENT( AsgXor )				\
		ELEMENT( AsgIor )				\
		ELEMENT( Stmt )					\
		ELEMENT( StmtExprSemicolon )	\
		ELEMENT( Function )
#define ELEMENT( e ) virtual void visit( e* ) = 0;
		ELEMENTS
#undef ELEMENT
	};
}
