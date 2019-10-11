#include "Lexer.hpp"

#include <string.h>

using namespace Compiler;

Tokenizer::Tokenizer( std::ifstream&& file ): file( std::move( file )){
	history = (char*)malloc( 16 );
	hist_len = 16;
}

Tokenizer::~Tokenizer(){
	free( history );
}

ParsedToken Tokenizer::next_tok(){
	read = file.get();

	while( isspace( read ))
		read = file.get();

	switch( read ){
		case EOF:
			return { tok_eof, nullptr };
		case '+':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_add;
			}
			return tok_add;
		case '-':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_sub;
			}
			return tok_sub;
		case '*':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_mul;
			}
			return tok_mul;
		case '/':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_div;
			}
			return tok_div;
		case '&':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_and;
			}
			return tok_and;
		case '^':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_xor;
			}
			return tok_xor;
		case '|':
			if( file.peek() == '=' ){
				file.get();
				return tok_asg_ior;
			}
			return tok_ior;
		case '(':
			return tok_brak_round_open;
		case ')':
			return tok_brak_round_close;
		case '[':
			return tok_brak_square_open;
		case ']':
			return tok_brak_square_close;
		case '{':
			return tok_brak_curly_open;
		case '}':
			return tok_brak_curly_close;
		case '"':
		{
			unsigned i = 0;
			do {
				if( i >= hist_len ){
					char* temp_history = (char*)malloc( hist_len * 2 );
					strncpy( temp_history, history, hist_len );
					free( history );
					history = temp_history;
					hist_len *= 2;
				}
				history[i++] = read;
				read = file.get();
				//TODO \"
			} while( read != '"' );
			history[i] = '\0';

			return { tok_str_lit, std::unique_ptr<Metadata>( new MetadataString( history ))};

		}
		default:
			if( isdigit( read ) || read == '.' ){
				unsigned i = 0;
				do {
					if( i >= hist_len ){
						char* temp_history = (char*)malloc( hist_len * 2 );
						strncpy( temp_history, history, hist_len );
						free( history );
						history = temp_history;
						hist_len *= 2;
					}
					history[i++] = read;
					read = file.get();
				} while( isdigit( read ) || read == '.' );
				history[i] = '\0';
				double val = strtod( history, nullptr );
				return { tok_num_lit, std::unique_ptr<Metadata>( new MetadataNum( val ))};
			}
			else if( isalpha( read )){
				unsigned i = 0;
				do {
					if( i >= hist_len ){
						char* temp_history = (char*)malloc( hist_len * 2 );
						strncpy( temp_history, history, hist_len );
						free( history );
						history = temp_history;
						hist_len *= 2;
					}
					history[i++] = read;
					read = file.get();
				} while( isalnum( read ));
				history[i] = '\0';

#define KEYWORD( k ) if( !strcmp( history, #k )) return { tok_##k, nullptr };
				KEYWORD( true )
				KEYWORD( false )
				KEYWORD( for )
				KEYWORD( while )
				KEYWORD( null )
#undef KEYWORD

				return { tok_id, std::unique_ptr<Metadata>( new MetadataString( history ))};
			}
			return tok_error;
	}
}
