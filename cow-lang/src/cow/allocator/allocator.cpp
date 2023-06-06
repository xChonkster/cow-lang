#include "./allocator.hpp"

namespace cow
{

allocator::allocator( )
	: base( static_cast<page*>(operator new(sizeof( page ))) )
{
	base->next = nullptr;
}

allocator::allocator( allocator&& other ) noexcept
	: base( other.base ),
	offset( other.offset )
{
	other.base = nullptr;
	other.offset = NULL;
}

allocator::~allocator( )
{
	page* current = base;

	do
	{
		page* next = current->next;

		operator delete(current);

		current = next;
	} while ( current );
}

void* allocator::allocate( size_t size )
{
	constexpr size_t alignment = alignof(void*);

	if ( base )
	{
		const uintptr_t data = reinterpret_cast<uintptr_t>(base->data);
		const uintptr_t current = (data + offset + alignment - 1) & ~(alignment - 1); // will be atleast base + (alignment - 1) bytes (probably 7 since were on 64bit)

		if ( current + size <= data + sizeof( base->data ) )
		{
			offset = current + size - data;

			return reinterpret_cast<void*>(current);
		}
	}

	const size_t newsize = size > sizeof( page::data ) ? size : sizeof( page::data );

	// size requested + sizeof(page* next)
	page* newpage = static_cast<page*>(operator new(offsetof( page, data ) + newsize));

	newpage->next = base;

	base = newpage;
	offset = NULL;

	return newpage->data;
}

}