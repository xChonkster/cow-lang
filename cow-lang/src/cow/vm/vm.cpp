#include "./vm.hpp"

#include "../allocator/allocator.hpp"
#include "../bytecode/bytecode.hpp"
#include "../instruction/instruction.hpp"

namespace cow
{

namespace vm
{

void load( const std::string& bytecode )
{
	allocator allocator;
	deserializer deserializer{ allocator };

	const object::function* function = deserializer.deserialize( bytecode );

	vm::execute( function );
}

void execute( const object::function* function )
{
	const size_t ninstructions = function->ninstructions;
	const object::instruction* instructions = function->instructions;

	size_t ip = 0;
	size_t last_loop_start_ip = 0;
	size_t last_loop_end_ip = 0; // so op

	uint32_t stack[1024]{ 0 }; // stack space
	uint32_t* sp = stack; // stack pointer

	uint32_t r32 = 0u; // register for MMM instruction

	while ( ip < ninstructions )
	{
	start:
		instruction::opcode instruction = static_cast<instruction::opcode>(instructions[ip]);

	dispatch:
		if ( instruction == instruction::opcode::moo )
		{
			if ( static_cast<instruction::opcode>(instructions[ip - 1]) != instruction::opcode::MOO )
				last_loop_end_ip = ip;

			ip = last_loop_start_ip;

			goto start;
		}
		else if ( instruction == instruction::opcode::mOo )
		{
			sp--;
		}
		else if ( instruction == instruction::opcode::moO )
		{
			sp++;
		}
		else if ( instruction == instruction::opcode::mOO )
		{
			instruction = static_cast<instruction::opcode>(*sp);

			goto dispatch;
		}
		else if ( instruction == instruction::opcode::Moo )
		{
			if ( *sp == 0 )
				*sp = static_cast<uint32_t>(getchar()); // c code ewwie (jk lol..)
			else
				putchar( static_cast<int>(*sp) );
		}
		else if ( instruction == instruction::opcode::MOo )
		{
			(*sp)--;
		}
		else if ( instruction == instruction::opcode::MoO )
		{
			(*sp)++;
		}
		else if ( instruction == instruction::opcode::MOO )
		{
			if ( static_cast<instruction::opcode>(instructions[ip + 1]) != instruction::opcode::moo )
				last_loop_start_ip = ip;

			if ( *sp == 0 )
			{
				ip = last_loop_end_ip + 1;

				goto start;
			}
		}
		else if ( instruction == instruction::opcode::OOO )
		{
			*sp = 0;
		}
		else if ( instruction == instruction::opcode::MMM )
		{
			if ( r32 == 0 )
			{
				r32 = *sp;
			}
			else
			{
				*sp = r32;

				r32 = 0;
			}
		}
		else if ( instruction == instruction::opcode::OOM )
		{
			std::printf( "%ud\n", *sp );
		}
		else if ( instruction == instruction::opcode::oom )
		{
			uint32_t integer = 0u;
			uint32_t result = static_cast<uint32_t>(scanf_s( "%d", &integer )); // lets just hope scanf succeeds...

			*sp = result;
		}

		ip++;
	} // interpreter loop
}

} // namespace vm

} // namespace cow