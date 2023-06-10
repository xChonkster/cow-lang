#pragma once

#include "../cow.hpp"

namespace cow
{

class allocator
{
public:
	void* allocate( size_t size );

public:
	allocator();
	allocator( allocator&& other ) noexcept;

	allocator( allocator& other ) = delete;

	~allocator();

private:
	struct page
	{
		page* next; // really its previous but whatever

		uint8_t data[8192];
	}; // kinda took this idea from luau source, but its so smart (we allocate memory in pages)

private:
	page* base{ 0 };
	size_t offset{ 0 };
}; // class would be static but thats a horrible idea so nvm

} // namespace cow

