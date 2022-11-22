#include<iostream>

#include "MemoryAllocator.h"
#include "RedBlackTree.h"


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

void TestRedBlack()
{
    int input[] = {10, 20, 30, 40, 50, 60};
    
}

int main()
{
    // MyMalloc(10);

    return 1;
}