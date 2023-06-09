#include "./compiler.hpp"

#include "../lexer/lexer.hpp"

#include "../bytecode/bytecode.hpp"

namespace cow
{

namespace compiler
{

std::string compile( const std::string& source )
{
	const std::vector<lexer::token> tokens = lexer::tokenize( source );

	serializer serializer;

	return serializer.serialize( tokens );
}

} // namespace compiler

} // namespace cow