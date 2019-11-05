#include <iostream>

#include "Lexer.hpp"
#include "PrintVisitor.hpp"
#include "Parser.hpp"
#include "Operator.hpp"

using namespace Compiler;

int main( int argc, char** argv ){
	if( argc < 2 ){
		std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
		return EXIT_FAILURE;
	}

	Compiler::Tokenizer tokenizer{ std::ifstream( argv[1] )};

#if 0
	for( Compiler::ParsedToken temp = tokenizer.next_tok(); temp.token != Compiler::tok_eof; temp = tokenizer.next_tok() ){
		switch( temp.token ){
			case Compiler::tok_num_lit:
				std::cout << "{ " << tok_to_string( temp.token ) << ", " << ((Compiler::MetadataNum*)&*temp.metadata )->number << " }" << std::endl;
				break;
			case Compiler::tok_str_lit:
			case Compiler::tok_id:
				std::cout << "{ " << tok_to_string( temp.token ) << ", " << ((Compiler::MetadataString*)&*temp.metadata )->string << " }" << std::endl;
				break;
			default:
				std::cout << "{ " << tok_to_string( temp.token ) << ", } " << std::endl;
				break;
		}
	}
#else

	Parser pars( std::move( tokenizer ));

	auto ast = pars();

	AST::PrintVisitor pv( std::cout );
	ast->accept( pv );
#endif
}
