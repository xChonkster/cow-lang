#include "./lexer.hpp"

namespace cow
{

namespace lexer
{

std::vector<token> tokenize( const std::string& content )
{
	std::vector<token> tokens = {};
	size_t position = 0u, end = content.length();

	while ( position < end )
	{
		const auto match = [&] ( const char* pos, const char match[3] ) -> bool
		{
			const bool matching = ((pos[0] == match[0]) && (pos[1] == match[1]) && (pos[2] == match[2])); // will read a little bit past string size but its fine

			if ( matching )
				position += 3;

			return matching;
		}; // will hopefully optimize nicely

		if ( match( &content[position], "moo" ) )
		{
			tokens.emplace_back( token::LoopEnd );
		}
		else if ( match( &content[position], "mOo" ) )
		{ 
			tokens.emplace_back( token::MoveMemoryBackward );
		}
		else if ( match( &content[position], "moO" ) )
		{
			tokens.emplace_back( token::MoveMemoryForward );
		}
		else if ( match( &content[position], "mOO" ) )
		{
			tokens.emplace_back( token::ExecuteMemory );
		}
		else if ( match( &content[position], "Moo" ) )
		{
			tokens.emplace_back( token::StdInOut );
		}
		else if ( match( &content[position], "MOo" ) )
		{
			tokens.emplace_back( token::DecrementMemoryValue );
		}
		else if ( match( &content[position], "MoO" ) )
		{
			tokens.emplace_back( token::IncrementMemoryValue );
		}
		else if ( match( &content[position], "MOO" ) )
		{
			tokens.emplace_back( token::LoopStart );
		}
		else if ( match( &content[position], "OOO" ) )
		{
			tokens.emplace_back( token::ZeroMemory );
		}
		else if ( match( &content[position], "MMM" ) )
		{
			tokens.emplace_back( token::ReadWriteRegister );
		}
		else if ( match( &content[position], "OOM" ) )
		{
			tokens.emplace_back( token::PrintMemory );
		}
		else if ( match( &content[position], "oom" ) )
		{
			tokens.emplace_back( token::ReadInt );
		}
		else 
			position++;
	}

	return tokens;
}

} // namespace lexer

} // namespace cow