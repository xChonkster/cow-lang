#include "./bytecode.hpp"

namespace cow
{

std::string serializer::finalize()
{
	return stream.str();
}


deserializer::deserializer( allocator& allocator )
	: _allocator(allocator)
{
}

object::function* deserializer::deserialize( const std::string& bytecode )
{
	stream.str( bytecode ); // initialize stream

	const uint8_t success = read<uint8_t>(); // did compilation succeed?

	if ( !success )
	{
		std::printf( "failed to load bytecode: %s\n", bytecode.c_str() + sizeof( char ) ); // rest of the string is the error message

		return NULL;
	}

	const size_t ninstructions = read<size_t>(); // read instruction count (8 bytes);
	
	object::function* function = reinterpret_cast<object::function*>(_allocator.allocate( ninstructions * sizeof( object::instruction ) + sizeof( size_t ) ));

	function->ninstructions = ninstructions;
	function->instructions = reinterpret_cast<object::instruction*>(function + offsetof( object::function, instructions )); // instructions points to allocated memory

	for ( size_t index = 0u; index < ninstructions; index++ )
		function->instructions[index] = read<object::instruction>();

	return function;
}

} // namespace cow

