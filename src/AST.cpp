#include "AST.hpp"

using namespace AST;

void Boolean::accept( Visitor& v ){
	v.visit( this );
}

void StmtExprSemicolon::accept( Visitor& v ){
	v.visit( this );
}

void Identifier::accept( Visitor& v ){
	v.visit( this );
}

void Function::accept( Visitor& v ){
	v.visit( this );
}

void Number::accept( Visitor& v ){
	v.visit( this );
}

void String::accept( Visitor& v ){
	v.visit( this );
}
