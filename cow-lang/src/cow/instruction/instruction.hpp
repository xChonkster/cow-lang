#pragma once

#include "../cow.hpp"

#include "../object/object.hpp"

namespace cow::instruction
{

enum class opcode : uint8_t // opcodes fit in 4 bits
{
	moo, // custom jmp instruction
	mOo,
	moO,
	mOO,
	Moo,
	MOo,
	MoO,
	MOO, // custom conditional jmp instruction
	OOO,
	MMM,
	OOM,
	oom,
	mom, // custom exit instruction
};

constexpr opcode INSN_OP( object::instruction insn )
{
	return static_cast<opcode>(insn & 0xF);
}

template <typename T>
constexpr T INSN_A( object::instruction insn )
{
	return (static_cast<T>(insn) >> 4);
}

} // namespace cow::instruction

