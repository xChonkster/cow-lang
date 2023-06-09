#include "./cow/cow.hpp"

#include "./cow/compiler/compiler.hpp"
#include "./cow/vm/vm.hpp"

#include <windows.h>
#include <iostream>

// hello world in moolang
constexpr static const char* source = R"( MoO MoO MoO MoO MoO MoO MoO MoO MOO moO MoO MoO MoO MoO MoO moO MoO MoO MoO MoO moO MoO MoO MoO MoO moO MoO MoO MoO MoO MoO MoO MoO
 MoO MoO moO MoO MoO MoO MoO mOo mOo mOo mOo mOo MOo moo moO moO moO moO Moo moO MOO mOo MoO moO MOo moo mOo MOo MOo MOo Moo MoO MoO 
 MoO MoO MoO MoO MoO Moo Moo MoO MoO MoO Moo MMM mOo mOo mOo MoO MoO MoO MoO Moo moO Moo MOO moO moO MOo mOo mOo MOo moo moO moO MoO 
 MoO MoO MoO MoO MoO MoO MoO Moo MMM MMM Moo MoO MoO MoO Moo MMM MOo MOo MOo Moo MOo MOo MOo MOo MOo MOo MOo MOo Moo mOo MoO Moo )";

int main()
{
	SetConsoleTitleA( "MOO!" );
	
	const std::string compiled = cow::compiler::compile( source );

	cow::vm::load( compiled );
	
	std::cin.get();
}

