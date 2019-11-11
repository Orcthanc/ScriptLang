#pragma once

#include <fstream>

#include "Tokens.hpp"

namespace Compiler {

	struct Tokenizer {
		public:
			Tokenizer( std::ifstream&& file );
			Tokenizer( Tokenizer&& );

			~Tokenizer();

			Tokenizer& operator=( Tokenizer&& );

			ParsedToken next_tok();
			ParsedToken curr_tok();
			ParsedToken peek_tok();

		private:
			void calc_next_tok();
			void add_char_to_history( char c );
			void handle_escape_sequence();

			ParsedToken current_tok, future_tok;
			std::ifstream file;
			char* history;
			unsigned hist_len;
			unsigned hist_i;
			char read;
			unsigned int line = 1;
	};
}
