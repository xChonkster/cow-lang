#pragma once

#include "../cow.hpp"

namespace cow::lexer
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
	ReadInt,				// oom
	Exit					// mom (not parsed)
};

std::vector<token> tokenize( const std::string& lexer );

} // namespace cow::lexer

