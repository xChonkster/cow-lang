#pragma once

#include "../cow.hpp"

#include "../object/object.hpp"

namespace cow
{

namespace instruction
{

enum class opcode : object::instruction
{
	moo,
	mOo,
	moO,
	mOO,
	Moo,
	MOo,
	MoO,
	MOO,
	OOO,
	MMM,
	OOM,
	oom,
};

} // namespace instruction

} // namespace cow
