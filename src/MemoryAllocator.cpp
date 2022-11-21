#include "MemoryAllocator.h"

#include<iostream>


MemoryAllocator::MemoryAllocator()
{
    std::cout << "create function" << std::endl;
}

MemoryAllocator& MemoryAllocator::get_instance()
{
    static MemoryAllocator instance;
    return instance;
}

MemoryAllocator::~MemoryAllocator()
{
    std::cout << "delete MemoryAllocator" << std::endl;
}