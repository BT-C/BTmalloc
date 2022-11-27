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

MetaMemory::MetaMemory(){
    this -> memorySize = 0;
    this -> address = 0;
}

MetaMemory::MetaMemory(size_t memory, size_t address)
{
    this -> memorySize = memory;
    this -> address = address;
}

size_t MetaMemory::getAddress()
{
    return this -> address;
}

size_t MetaMemory::getMemorySize()
{
    return this -> memorySize;
}

bool MetaMemory::operator<(MetaMemory &a)
{
    return this -> memorySize < a.memorySize;
}

bool MetaMemory::operator>(MetaMemory &a)
{
    return this -> memorySize > a.memorySize;
}

bool MetaMemory::operator==(MetaMemory &a)
{
    return this -> memorySize == a.memorySize;
}

bool MetaMemory::operator<=(MetaMemory &a)
{
    return this -> memorySize <= a.memorySize;
}

std::ostream & operator << (std::ostream &os, MetaMemory &a)
{
    os << a.memorySize;
    return os;
}