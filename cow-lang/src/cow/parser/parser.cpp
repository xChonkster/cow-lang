#include "./parser.hpp"

namespace cow
{

parser::parser( std::vector<lexer::token>& tokens, serializer& serializer )
	: tokens( tokens ), _serializer( serializer )
{
}

void parser::get_arith_information()
{
	for ( uint32_t ip = 0; ip < tokens.size(); ip++ )
	{
		const auto get_sequence_size = [&] (lexer::token token) -> uint32_t
		{
			uint32_t current = ip;

			while ( tokens[current] == token )
				current++;

			return current - ip;
		};

		const lexer::token& token = tokens[ip];

		if ( token == lexer::token::MoveMemoryBackward || token == lexer::token::MoveMemoryForward || token == lexer::token::DecrementMemoryValue || token == lexer::token::IncrementMemoryValue )
		{
			const uint32_t size = get_sequence_size( token );

			arithinfo.insert( { ip, size } );

			if ( size > 1 )
				tokens.erase( tokens.begin() + ip + 1, tokens.begin() + ip + size); // erase the instructions
			// this is a very bad solution to this problem (imo)
			// use linked list token allocator for next project
		}
	}
}

void parser::get_loop_information()
{
	// [depth, ip]
	std::unordered_multimap<uint32_t, uint32_t> jumps = {}; // hm (should get deepest loop depth from lexer so i can properly alloc 2d array, next project...)
	uint32_t loop_level = 0;

	// look foor loop tokens, store each one by loop depth
	for ( uint32_t ip = 0; ip < tokens.size(); ip++ )
	{
		const lexer::token& token = tokens[ip];

		if ( token == lexer::token::LoopStart )
		{
			jumps.insert( { loop_level++, ip } );
		}
		else if ( token == lexer::token::LoopEnd )
		{
			jumps.insert( { --loop_level, ip } );
		}
	}

	// cute
	if ( loop_level != 0 )
		throw parser_error( "amount of loop start (MOO) and loop end (moo) do not match" );

	// iterate loop depths
	for ( uint32_t bucket = 0; bucket < jumps.bucket_count(); bucket++ )
	{
		for ( auto it = jumps.begin( bucket ); it != jumps.end( bucket ); )
		{
			const uint32_t start_ip = (it++)->second; // (conditional, so rel64 + 1)
			const uint32_t end_ip = (it++)->second; // iterate in pairs

			jmpinfo.insert( { start_ip, (end_ip - start_ip) + 1});
			jmpinfo.insert( { end_ip, (start_ip - end_ip) } );
		}
	}
}

void parser::parse()
{	
	_serializer.write<uint8_t>( 1 ); // bytecode compiled successfully

	_serializer.write<size_t>( tokens.size() );

	for (uint32_t ip = 0; ip < tokens.size(); ip++ )
	{
		const lexer::token& token = tokens[ip];

		switch ( token )
		{

		case lexer::token::LoopEnd:
		{
			emitOPA( instruction::opcode::moo, jmpinfo[ip] );

			break;
		}
		case lexer::token::LoopStart:
		{
			emitOPA( instruction::opcode::MOO, jmpinfo[ip] );

			break;
		}
		case lexer::token::MoveMemoryBackward:
		case lexer::token::MoveMemoryForward:
		case lexer::token::DecrementMemoryValue:
		case lexer::token::IncrementMemoryValue:
		{
			emitOPA( static_cast<instruction::opcode>(token), arithinfo[ip]);

			break;
		}
		default:
		{
			emitOP( static_cast<instruction::opcode>(token) );

			break;
		}

		}
	}
}

std::string parser::error( const parser_error& message )
{
	std::string error = {};

	error += '\0'; // script failed to compile
	error += message.what();
	
	return error;
}

void parser::emitOP( instruction::opcode op )
{
	const object::instruction insn = static_cast<object::instruction>(std::to_underlying( op ) & 0xF);

	_serializer.write( insn );
}

void parser::emitOPA( instruction::opcode op, int32_t arg )
{
	const object::instruction insn = static_cast<object::instruction>((std::to_underlying( op ) & 0xF) | (static_cast<uint32_t>(arg) << 4));

	_serializer.write( insn );
}

} // namespace cow

