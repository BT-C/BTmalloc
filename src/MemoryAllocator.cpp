#include "MemoryAllocator.h"

#include<iostream>


MemoryAllocator::MemoryAllocator()
{
    std::cout << "create memory allocator" << std::endl;
    size_t row = 10, col = 2;
    size_t scopeInterval = 1024;
    size_t lowerBound = 0, upperBound = 0;

    // int scopeList[row][col];
    for (int i = 0; i < row; i ++)
    {
        // scopeList[i][0] = i * scopeInterval;
        // scopeList[i][1] = (i + 1) * scopeInterval;
        lowerBound = i * scopeInterval;
        upperBound = (i + 1) * scopeInterval;
        this -> scopeTree -> insert(ScopeMemory(lowerBound, upperBound));
    }

    this -> scopeTree -> preOrder();
}

MemoryAllocator& MemoryAllocator::get_instance()
{
    static MemoryAllocator instance;
    return instance;
}

MemoryAllocator::~MemoryAllocator()
{
    scopeTree -> destroy();
    std::cout << "delete MemoryAllocator" << std::endl;
}
