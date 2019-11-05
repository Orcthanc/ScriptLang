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
	out << "( ";
	elem->lhs->accept( *this );
	out << " " << Compiler::op_to_symbol( elem->op ) << " ";
	elem->rhs->accept( *this );
	out << " )";
}
void PrintVisitor::visit( CallOp* elem ){
	elem->id->accept( *this );
	switch( elem->op ){
		case Compiler::op_call:
			out << "( ";
			break;
		case Compiler::op_array:
			out << "[ ";
			break;
		default:
			throw std::runtime_error( std::string( "Invalid op in syntaxtree " ) + op_to_symbol( elem->op ));
	}
	elem->args->accept( *this );
	switch( elem->op ){
		case Compiler::op_call:
			out << " )";
			break;
		case Compiler::op_array:
			out << " ]";
			break;
		default:
			throw std::runtime_error( std::string( "Invalid op in syntaxtree " ) + op_to_symbol( elem->op ));
	}

}
void PrintVisitor::visit( Unop* elem ){
	out << "( ";
	if( Compiler::left_to_right( elem->op )){
		elem->val->accept( *this );
		out << Compiler::op_to_symbol( elem->op );
	}else {
		out << Compiler::op_to_symbol( elem->op );
		elem->val->accept( *this );
	}
	out << " )";
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
