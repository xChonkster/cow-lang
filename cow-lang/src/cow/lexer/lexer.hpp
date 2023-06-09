#pragma once

#include "../cow.hpp"

namespace cow
{

namespace lexer
{

enum class token : uint16_t
{
	LoopEnd,				// moo
	MoveMemoryBackward,		// mOo
	MoveMemoryForward,		// moO
	ExecuteMemory,			// mOO
	StdInOut,				// Moo
	DecrementMemoryValue,	// MMo
	IncrementMemoryValue,	// MoO
	LoopStart,				// MOO
	ZeroMemory,				// OOO
	ReadWriteRegister,		// MMM
	PrintMemory,			// OOM
	ReadInt					// oom
};

std::vector<token> tokenize( const std::string& lexer );

}; // namespace lexer

} // namespace cow