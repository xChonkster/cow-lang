#pragma once

#include "../cow.hpp"
#include "../object/object.hpp"

namespace cow
{

namespace vm
{

void load( const std::string& bytecode );

void execute( const object::function* function );

} // namespace vm

} // namespace cow
