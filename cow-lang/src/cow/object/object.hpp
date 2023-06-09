#pragma once

#include "../cow.hpp"

namespace cow
{

namespace object
{

// instruction typedef
typedef uint16_t instruction;

// cow function object
struct function
{
	size_t ninstructions; // size of bytecode
	instruction* instructions; // bytecode
};

} // namespace object

} // namespace cow