#pragma once

#include "../lexer/lexer.hpp"

#include "../object/object.hpp"
#include "../allocator/allocator.hpp"

#include <sstream>

namespace cow
{

class serializer
{
public:
	std::string finalize();

	template <typename T>
	void write( T value )
	{
		stream.write( reinterpret_cast<const char*>(&value), sizeof( T ) );
	}

private:
	std::stringstream stream;
};

class deserializer
{
public:
	deserializer( allocator& allocator );

	// pointer is allocated by allocator, so it will live as long as allocator lives
	object::function* deserialize( const std::string& bytecode );

private:
	template <typename T>
	T read()
	{
		T obj{ 0 };

		stream.read( reinterpret_cast<char*>(&obj), sizeof( T ) );

		return obj;
	}

private:
	allocator& _allocator;
	std::stringstream stream;
};

} // namespace cow

