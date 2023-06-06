#pragma once

#include "../cow.hpp"

// instruction typedef
typedef uint64_t cow_instruction;

// cow function object
struct cow_function
{
	size_t ninstructions; // size of bytecode
	cow_instruction* instructions; // bytecode
};