#include <fstream>

#include "Tokens.hpp"

namespace Compiler {

	struct Tokenizer {
		public:
			Tokenizer( std::ifstream&& file );
			~Tokenizer();

			ParsedToken next_tok();

		private:
			std::ifstream file;
			char* history;
			unsigned hist_len;
			char read;
	};
}
