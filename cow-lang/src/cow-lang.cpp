#include <windows.h>
#include <iostream>

#include <bitset>

#include "./cow/cow.hpp"
#include "./cow/instruction/instruction.hpp"

int main( )
{
    constexpr auto instr = COW_INSN_CREATE( 1, 3, -7, 15 );

    std::cout << "opcode: " << COW_INSN_OPCODE( instr )
        << "\na: " << COW_INSN_A<int16_t>( instr )
        << "\nb: " << COW_INSN_B<int16_t>( instr )
        << "\nc: " << COW_INSN_C<int16_t>( instr )
        << std::endl;

    std::cout << std::bitset<64>( instr ) << std::endl;
}
