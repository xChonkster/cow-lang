#include "./compiler.hpp"

#include "../lexer/lexer.hpp"
#include "../bytecode/bytecode.hpp"
#include "../parser/parser.hpp"

// write new parser class, parser takes in tokens and serializer, does the work and serializes it (gg loops)

namespace cow::compiler
{

std::string compile( const std::string& source )
{
	const std::vector<lexer::token> tokens = lexer::tokenize( source );

	serializer serializer;

	parser parser{ tokens, serializer };

	try
	{
		parser.get_loop_information();
		parser.parse();

		return serializer.finalize();
	}
	catch ( parser_error message )
	{
		return parser.error( message );
	}
}

} // namespace cow::compiler

