#include "./compiler.hpp"

#include "../lexer/lexer.hpp"
#include "../allocator/allocator.hpp"

namespace cow
{

std::string compile( const std::string& source )
{
	cow::allocator allocator;

	std::uint8_t* memory = reinterpret_cast<std::uint8_t*>(allocator.allocate( 0 ));

	memory[0] = 'a';
	memory[1] = 'b';
	memory[2] = 'c';
	memory[3] = '\0';

	std::printf( "%s\n", memory );

	return "soon:tm:";
}

} // namespace cow