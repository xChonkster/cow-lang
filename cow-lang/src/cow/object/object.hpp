#pragma once

#include "../cow.hpp"

namespace cow::object
{

// instruction typedef
typedef uint32_t instruction;

// cow function object
struct function
{
	size_t ninstructions; // size of bytecode
	instruction* instructions; // bytecode
};

} // namespace cow::object

