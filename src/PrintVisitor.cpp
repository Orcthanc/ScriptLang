#include "PrintVisitor.hpp"

#include <iostream>

using namespace AST;

static inline void ident( size_t amount, std::ostream& os ){
	for( size_t i = 0; i < amount; ++i )
		os << "\t";
}

void PrintVisitor::visit( PostInc* elem ){
	elem->val->accept( *this );
	out << "++";
}
void PrintVisitor::visit( PostDec* elem ){
	elem->val->accept( *this );
	out << "--";
}
void PrintVisitor::visit( PreInc* elem ){
	out << "++";
	elem->val->accept( *this );
}
void PrintVisitor::visit( PreDec* elem ){
	out << "--";
	elem->val->accept( *this );
}
void PrintVisitor::visit( Plus* elem ){
	out << "+";
	elem->val->accept( *this );
}
void PrintVisitor::visit( Minus* elem ){
	out << "-";
	elem->val->accept( *this );
}
void PrintVisitor::visit( Not* elem ){
	out << "~";
	elem->val->accept( *this );
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
	throw std::runtime_error( "Unexcpected class in syntax tree" );
}
void PrintVisitor::visit( Asg* elem ){
	elem->lhs->accept( *this );
	out << " = ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Add* elem ){
	elem->lhs->accept( *this );
	out << " + ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Sub* elem ){
	elem->lhs->accept( *this );
	out << " - ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Mul* elem ){
	elem->lhs->accept( *this );
	out << " * ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Div* elem ){
	elem->lhs->accept( *this );
	out << " / ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( And* elem ){
	elem->lhs->accept( *this );
	out << " & ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Xor* elem ){
	elem->lhs->accept( *this );
	out << " ^ ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( Ior* elem ){
	elem->lhs->accept( *this );
	out << " | ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgAdd* elem ){
	elem->lhs->accept( *this );
	out << " += ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgSub* elem ){
	elem->lhs->accept( *this );
	out << " -= ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgMul* elem ){
	elem->lhs->accept( *this );
	out << " *= ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgDiv* elem ){
	elem->lhs->accept( *this );
	out << " /= ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgAnd* elem ){
	elem->lhs->accept( *this );
	out << " &= ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgXor* elem ){
	elem->lhs->accept( *this );
	out << " ^= ";
	elem->rhs->accept( *this );
}
void PrintVisitor::visit( AsgIor* elem ){
	elem->lhs->accept( *this );
	out << " |= ";
	elem->rhs->accept( *this );
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
