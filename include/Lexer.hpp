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

			ParsedToken current_tok, future_tok;
			std::ifstream file;
			char* history;
			unsigned hist_len;
			char read;
	};
}
