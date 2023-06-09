#pragma once

#include "../cow.hpp"

#include "../lexer/lexer.hpp"
#include "../bytecode/bytecode.hpp"
#include "../object/object.hpp"
#include "../instruction/instruction.hpp"

#include <unordered_map>

namespace cow
{

// lol
using parser_error = std::runtime_error;

class parser
{
public:
	parser( const std::vector<lexer::token>& tokens, serializer& serializer );

	void get_loop_information();
	void parse();

	std::string error( const parser_error& message );

private:
	void emitOP( instruction::opcode op );
	void emitOPA( instruction::opcode op, int32_t arg ); // arg has 28 bit range (-134217728...134217727)
	
private:
	// [ip, rel64]
	std::unordered_map<uint32_t, uint32_t> jmpinfo;

	const std::vector<lexer::token>& tokens;
	serializer& _serializer;
};

} // namespace cow

