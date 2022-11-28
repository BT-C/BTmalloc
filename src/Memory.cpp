#include "Memory.h"

#include<iostream>


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











ScopeMemory::ScopeMemory()
{
    this -> lowerBound = 0;
    this -> upperBound = 0;
    this -> tree = new RedBlackTree<MetaMemory>();
}

ScopeMemory::ScopeMemory(size_t lowerBound, size_t upperBound)
{
    this -> lowerBound = lowerBound;
    this -> upperBound = upperBound;
    this -> tree = new RedBlackTree<MetaMemory>();
}

ScopeMemory::~ScopeMemory()
{
    tree -> destroy();
}

// void ScopeMemory::modifyBound()
// {
//     if (this -> tree -> getRoot() == NULL)
//     {
//         this -> lowerBound = this -> upperBound = 0;
//         return ;
//     }
//     this -> lowerBound = this -> tree -> minimum().getMemorySize();
//     this -> upperBound = this -> tree -> maximum().getMemorySize();
// }

bool ScopeMemory::operator < (ScopeMemory& a)
{
    return this -> upperBound < a.lowerBound;
}

bool ScopeMemory::operator > (ScopeMemory& a)
{
    return this -> lowerBound > a.upperBound;
}

bool ScopeMemory::operator == (ScopeMemory& a)
{
    return ((this -> lowerBound <= a.lowerBound) && (a.upperBound <= this -> upperBound));
}

bool ScopeMemory::operator <= (ScopeMemory& a)
{
    return this -> upperBound <= a.lowerBound;
}

std::ostream & operator << (std::ostream &os, ScopeMemory &a)
{
    os << "(" << a.lowerBound << ", " << a.upperBound << ")";
    return os;
}