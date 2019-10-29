#include "AST.hpp"

using namespace AST;

#define ELEMENT( name )							\
void name::accept( Visitor& v ){				\
	v.visit( this );							\
}

ELEMENTS
#undef ELEMENT
