#include "Lexer.hpp"

#include <string.h>

#include <iostream>

using namespace Compiler;

Tokenizer::Tokenizer( std::ifstream&& file ): current_tok( tok_error, "", 0 ), future_tok( tok_error, "", 0 ), file( std::move( file )){
	history = (char*)malloc( 16 );
	hist_len = 16;
	do {
		read = this->file.get();
	} while( isspace( read ));
	calc_next_tok();
}

Tokenizer::Tokenizer( Tokenizer&& tok ): current_tok( std::move( tok.current_tok )), future_tok( std::move( tok.future_tok )), file( std::move( tok.file )), history( std::move( tok.history )), hist_len( std::move( tok.hist_len )), read( tok.read ){
	tok.history = nullptr;
}

Tokenizer& Tokenizer::operator=( Tokenizer&& tok ){
	current_tok = std::move( tok.current_tok );
	future_tok = std::move( tok.future_tok );
	file = std::move( tok.file );
	history = tok.history;
	tok.history = nullptr;
	hist_len = tok.hist_len;
	read = tok.read;
	return *this;
}

Tokenizer::~Tokenizer(){
	free( history );
}

ParsedToken Tokenizer::next_tok(){
	calc_next_tok();
	return current_tok;
}

ParsedToken Tokenizer::peek_tok(){
	return future_tok;
}

ParsedToken Tokenizer::curr_tok(){
	return current_tok;
}

void Tokenizer::calc_next_tok(){

	if( future_tok.token == tok_eof ){
		current_tok = { tok_eof, "", line };
		return;
	}


	while( isspace( read )){
		if( read == '\n' )
			++line;
		read = file.get();
	}

	current_tok = std::move( future_tok );

#ifndef CRTOKEN
#define CRTOKEN( tok ) { tok, "", line }
#endif

#ifndef CRMTOKEN
#define CRMTOKEN( tok, m ) { tok, m, "", line }
#endif

	switch( read ){
		case EOF:
			future_tok = CRTOKEN( tok_eof );
			break;
		case '+':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_add );
				break;
			} else if( file.peek() == '+' ){
				file.get();
				future_tok = CRTOKEN( tok_inc );
				break;
			}
			future_tok = CRTOKEN( tok_add );
			break;
		case '-':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_sub );
				break;
			} else if( file.peek() == '-' ){
				file.get();
				future_tok = CRTOKEN( tok_dec );
				break;
			}
			future_tok = CRTOKEN( tok_sub );
			break;
		case '*':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_mul );
				break;
			}
			future_tok = CRTOKEN( tok_mul );
			break;
		case '/':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_div );
				break;
			}
			future_tok = CRTOKEN( tok_div );
			break;
		case '%':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_mod );
				break;
			}
			future_tok = CRTOKEN( tok_mod );
			break;
		case '&':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_and );
				break;
			}
			future_tok = CRTOKEN( tok_and );
			break;
		case '^':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_xor );
				break;
			}
			future_tok = CRTOKEN( tok_xor );
			break;
		case '|':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_asg_ior );
				break;
			}
			future_tok = CRTOKEN( tok_ior );
			break;
		case '~':
			future_tok = CRTOKEN( tok_not );
			break;
		case '!':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_ne );
				break;
			}
			future_tok = CRTOKEN( tok_logic_not );
			break;
		case '=':
			if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_eq );
				break;
			}
			future_tok = CRTOKEN( tok_asg );
			break;
		case '(':
			future_tok = CRTOKEN( tok_brak_round_open );
			break;
		case ')':
			future_tok = CRTOKEN( tok_brak_round_close );
			break;
		case '[':
			future_tok = CRTOKEN( tok_brak_square_open );
			break;
		case ']':
			future_tok = CRTOKEN( tok_brak_square_close );
			break;
		case '{':
			future_tok = CRTOKEN( tok_brak_curly_open );
			break;
		case '}':
			future_tok = CRTOKEN( tok_brak_curly_close );
			break;
		case ';':
			future_tok = CRTOKEN( tok_semicolon );
			break;
		case '.':
			future_tok = CRTOKEN( tok_dot );
			break;
		case '<':
			if( file.peek() == '<' ){
				file.get();
				future_tok = CRTOKEN( tok_left_shift );
				break;
			} else if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_le );
				break;
			}
			future_tok = CRTOKEN( tok_lt );
			break;
		case '>':
			if( file.peek() == '>' ){
				file.get();
				future_tok = CRTOKEN( tok_right_shift );
				break;
			} else if( file.peek() == '=' ){
				file.get();
				future_tok = CRTOKEN( tok_ge );
				break;
			}
			future_tok = CRTOKEN( tok_gt );
			break;
		case '"':
		{
			read = file.get();
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
				if( read == EOF )
					std::cout << "Missing \"" << std::endl;
			} while( read != '"' );
			history[i] = '\0';

			future_tok = CRMTOKEN( tok_str_lit, std::unique_ptr<Metadata>( new MetadataString( history )));
			break;

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
				future_tok = CRMTOKEN( tok_num_lit, std::unique_ptr<Metadata>( new MetadataNum( val )));
				return;
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

#define KEYWORD( k ) if( !strcmp( history, #k )) { future_tok = CRTOKEN( tok_##k ); return; }
				KEYWORD( true )
				KEYWORD( false )
				KEYWORD( for )
				KEYWORD( while )
				KEYWORD( null )
#undef KEYWORD

				future_tok = CRMTOKEN( tok_id, std::unique_ptr<Metadata>( new MetadataString( history )));
				return;
			}
			future_tok = CRTOKEN( tok_error );
			break;
	}
	read = file.get();

#undef CRTOKEN
#undef CRMTOKEN

	//while( isspace( read ))
	//	read = file.get();
}
