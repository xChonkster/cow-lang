#pragma once

#include "../cow.hpp"

#include "../object/object.hpp"

template <typename T>
concept is_signed_or_unsigned_short = std::_Is_any_of_v<T, int16_t, uint16_t>;

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

