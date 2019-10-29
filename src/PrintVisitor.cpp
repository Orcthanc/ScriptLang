#include "PrintVisitor.hpp"

#include <iostream>

using namespace AST;

static inline void ident( size_t amount, std::ostream& os ){
	for( size_t i = 0; i < amount; ++i )
		os << "\t";
}

void PrintVisitor::visit( Node* elem ){
	throw std::runtime_error( "Unexcpected class in syntax tree" );
}
void PrintVisitor::visit( OpExpr* elem ){
	throw std::runtime_error( "Unexcpected class in syntax tree" );
}
void PrintVisitor::visit( Expr* elem ){
	throw std::runtime_error( "Unexcpected class in syntax tree" );
}
void PrintVisitor::visit( Number* elem ){
	out << elem->value;
}
void PrintVisitor::visit( Identifier* elem ){
	out << elem->name;
}
void PrintVisitor::visit( String* elem ){
	out << "\"" << elem->value << "\"";
}
void PrintVisitor::visit( Boolean* elem ){
	out << ( elem->value ? "true" : "false" );
}
void PrintVisitor::visit( Binop* elem ){
	elem->lhs->accept( *this );
	out << Compiler::op_to_symbol( elem->op );
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Unop* elem ){
	if( Compiler::left_to_right( elem->op )){
		elem->val->accept( *this );
		out << Compiler::op_to_symbol( elem->op );
	}else {
		out << Compiler::op_to_symbol( elem->op );
		elem->val->accept( *this );
	}
}

void PrintVisitor::visit( Stmt* elem ){
	throw std::runtime_error( "Unexcpected class in syntax tree" );
}
void PrintVisitor::visit( StmtExprSemicolon* elem ){
	elem->expr->accept( *this );
	out << ";";
}
void PrintVisitor::visit( Function* elem ){
	ident( ident_amount++, out );
	out << "{\n";
	for( auto& e: elem->stmts ){
		ident( ident_amount, out );
		e->accept( *this );
		out << "\n";
	}
	ident( --ident_amount, out );
	out << "}\n";
}
