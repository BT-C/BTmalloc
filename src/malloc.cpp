#include<iostream>

#include "MemoryAllocator.h"


void * MyMalloc(size_t malloc_size)
{
    std::cout << sizeof(malloc_size) << std::endl;
    MemoryAllocator& m1 = MemoryAllocator::get_instance();
    MemoryAllocator& m2 = MemoryAllocator::get_instance();
    std::cout << &m1 << std::endl;
    std::cout << &m2 << std::endl;
    std::cout << "finish" << std::endl;
    // m.InitMemoryStruct();
}

int main()
{
    MyMalloc(10);

    return 1;
}