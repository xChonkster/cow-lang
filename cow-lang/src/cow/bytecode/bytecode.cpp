#include "./bytecode.hpp"

namespace cow
{

std::string serializer::serialize( const std::vector<lexer::token>& tokens )
{
	stream.str( std::string() ); // clear stringstream

	write<size_t>( tokens.size() );

	stream.write( reinterpret_cast<const char*>(tokens.data()), tokens.size() * sizeof( object::instruction ) );

	return stream.str();
}


deserializer::deserializer( allocator& allocator )
	: _allocator(allocator)
{
}

object::function* deserializer::deserialize( const std::string& bytecode )
{
	stream.str( bytecode ); // initialize stream

	const size_t ninstructions = read<size_t>(); // read instruction count (8 bytes);
	
	object::function* function = reinterpret_cast<object::function*>(_allocator.allocate( ninstructions * sizeof( object::instruction ) + sizeof( size_t ) ));

	function->ninstructions = ninstructions;
	function->instructions = reinterpret_cast<object::instruction*>(function + offsetof( object::function, instructions )); // instructions points to allocated memory

	for ( size_t index = 0u; index < ninstructions; index++ )
		function->instructions[index] = read<object::instruction>();

	return function;
}

} // namespace cow
