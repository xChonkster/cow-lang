#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <string>

namespace cow {}; // cow namespace

// used when the default case of a switch will never happen (will generate a jumptable)
#define COW_SWITCH_UNREACHABLE() __assume(false)
