#include "AST.hpp"

namespace AST{
	struct PrintVisitor: public Visitor {
		PrintVisitor( std::ostream& out ): out( out ){}
#define ELEMENT( e ) virtual void visit( e* );
		ELEMENTS
#undef ELEMENT

		std::ostream& out;
		size_t ident_amount = 0;
	};
}
