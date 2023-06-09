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
	const size_t ninstructions = function->ninstructions;
	const object::instruction* instructions = function->instructions;

	uint64_t ip = 0; // instruction pointer

	uint32_t stack[1024]{ 0 }; // stack space
	uint32_t* sp = stack; // stack pointer

	bool cleared = true;
	uint32_t r32 = 0u; // register for MMM instruction

	while ( ip < ninstructions )
	{
	start:
		object::instruction instruction = instructions[ip];
		instruction::opcode OP = instruction::INSN_OP( instruction );

	dispatch:
		if ( OP == instruction::opcode::moo )
		{
			ip += instruction::INSN_A<int32_t>( instruction ); // most OP thing ever...

			goto start;
		}
		else if ( OP == instruction::opcode::mOo )
		{
			sp--;
		}
		else if ( OP == instruction::opcode::moO )
		{
			sp++;
		}
		else if ( OP == instruction::opcode::mOO )
		{
			OP = static_cast<instruction::opcode>(*sp);

			goto dispatch;
		}
		else if ( OP == instruction::opcode::Moo )
		{
			if ( *sp == 0 )
				*sp = static_cast<uint32_t>(getchar());
			else
				putchar( static_cast<int>(*sp) );
		}
		else if ( OP == instruction::opcode::MOo )
		{
			(*sp)--;
		}
		else if ( OP == instruction::opcode::MoO )
		{
			(*sp)++;
		}
		else if ( OP == instruction::opcode::MOO )
		{
			if ( *sp == 0 )
			{
				ip += instruction::INSN_A<int32_t>( instruction ); // already has + 1

				goto start;
			}
		}
		else if ( OP == instruction::opcode::OOO )
		{
			*sp = 0;
		}
		else if ( OP == instruction::opcode::MMM )
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
		}
		else if ( OP == instruction::opcode::OOM )
		{
			std::printf( "%u\n", *sp );
		}
		else if ( OP == instruction::opcode::oom )
		{
			uint32_t integer = 0u;
			uint32_t result = static_cast<uint32_t>(scanf_s( "%d", &integer )); // lets just hope scanf succeeds...

			*sp = result;
		}

		ip++;
	} // interpreter loop
}

} // namespace cow::vm

