#include "./vm.hpp"

#include "../allocator/allocator.hpp"
#include "../bytecode/bytecode.hpp"
#include "../instruction/instruction.hpp"

namespace cow::vm
{

void load( const std::string& bytecode )
{
	allocator allocator;
	deserializer deserializer{ allocator };

	const object::function* function = deserializer.deserialize( bytecode );

	if ( function )
		vm::execute( function );
}

void execute( const object::function* function )
{
	const object::instruction* instructions = function->instructions;

	uintptr_t ip = 0; // instruction pointer

	uint32_t stack[1024]{ 0 }; // stack space
	uint32_t* sp = stack; // stack pointer

	bool cleared = true;
	uint32_t r32 = 0u; // register for MMM instruction

	while ( true )
	{
	start:
		object::instruction instruction = instructions[ip];
		instruction::opcode OP = instruction::INSN_OP( instruction );

	dispatch:
		switch ( OP )
		{

		case instruction::opcode::moo:
		{
			ip += instruction::INSN_A<int32_t>( instruction ); // most OP thing ever...

			goto start;
		}
		case instruction::opcode::mOo:
		{
			sp--;

			break;
		}
		case instruction::opcode::moO:
		{
			sp++;

			break;
		}
		case instruction::opcode::mOO:
		{
			OP = static_cast<instruction::opcode>(*sp);

			goto dispatch;
		}
		case instruction::opcode::Moo:
		{
			if ( *sp == 0 )
				*sp = static_cast<uint32_t>(getchar());
			else
				putchar( static_cast<int>(*sp) );

			break;
		}
		case instruction::opcode::MOo:
		{
			(*sp)--;

			break;
		}
		case instruction::opcode::MoO:
		{
			(*sp)++;

			break;
		}
		case instruction::opcode::MOO:
		{
			if ( *sp == 0 )
			{
				ip += instruction::INSN_A<int32_t>( instruction ); // already has + 1

				goto start;
			}

			break;
		}
		case instruction::opcode::OOO:
		{
			*sp = 0;

			break;
		}
		case instruction::opcode::MMM:
		{
			if ( cleared )
			{
				r32 = *sp;

				cleared = false;
			}
			else
			{
				*sp = r32;

				cleared = true;
			}

			break;
		}
		case instruction::opcode::OOM:
		{
			std::printf( "%u\n", *sp );

			break;
		}
		case instruction::opcode::oom:
		{
			uint32_t integer = 0u;
			uint32_t result = static_cast<uint32_t>(scanf_s( "%d", &integer )); // lets just hope scanf succeeds...

			*sp = result;

			break;
		}
		case instruction::opcode::mom: // please come pick me up im scared
		{
			return;
		}
		default:
			__assume(false); // will never happen (unless someone mOO's a bogus instruction in which case we segfault) so optimize into jumptable

		}

		ip++;
	} // interpreter loop
}

} // namespace cow::vm

