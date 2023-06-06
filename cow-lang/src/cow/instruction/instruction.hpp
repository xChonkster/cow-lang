#pragma once

#include "../cow.hpp"

#include "../object/object.hpp"

template<typename T>
concept is_signed_or_unsigned_short = std::_Is_any_of_v<T, int16_t, uint16_t>; // can be interpreted as signed or unsigned

// instruction opcodes
enum cow_opcode
{
	moo,
	mOo,
	moO,
	mOO,
	Moo,
	MMo,
	MoO,
	MOO,
	OOO,
	MMM,
	OOM,
	oom
};

// need to widen int16_t's to uint64_t's to allow shifting
// static_cast<uint64_t>(...) will sign extend the value, meaning the value in base 2 (bits) will have leading 1's past its 2 byte (int16_t short) range, which sets trailing arguments to (static_cast<uint64_t>(-1))
// so what we do is we AND the 2 bytes that represent the value we want (shifted mask), this way we eliminate leading 1's, this way our OR gate works :)
constexpr cow_instruction COW_INSN_CREATE( uint16_t opcode, int16_t a, int16_t b, int16_t c )
{
	constexpr uint64_t mask = 0xFFFF;

	return static_cast<uint64_t>(opcode) | ((static_cast<uint64_t>(a) << 16) & (mask << 16)) | ((static_cast<uint64_t>(b) << 32) & (mask << 32)) | ((static_cast<uint64_t>(c) << 48) & (mask << 48));
} // will have different versions

constexpr uint16_t COW_INSN_OPCODE( cow_instruction instruction )
{
	return instruction & 0xFFFF; // opcode is always positive
}

template <typename T>
	requires is_signed_or_unsigned_short<T>
constexpr T COW_INSN_A( cow_instruction instruction )
{
	return (instruction >> 16) & 0xFFFF;
}

template <typename T>
	requires is_signed_or_unsigned_short<T>
constexpr T COW_INSN_B( cow_instruction instruction )
{
	return (instruction >> 32) & 0xFFFF; // -32768...32767
}

template <typename T>
	requires is_signed_or_unsigned_short<T>
constexpr T COW_INSN_C( cow_instruction instruction )
{
	return (instruction >> 48) & 0xFFFF; // -32768...32767
}
