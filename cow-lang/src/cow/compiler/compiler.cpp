#include "./compiler.hpp"

#include "../lexer/lexer.hpp"
#include "../bytecode/bytecode.hpp"
#include "../parser/parser.hpp"

namespace cow::compiler
{

std::string compile( const std::string& source )
{
	std::vector<lexer::token> tokens = lexer::tokenize( source );

	serializer serializer;

	parser parser{ tokens, serializer };

	try
	{
		parser.get_arith_information();
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

