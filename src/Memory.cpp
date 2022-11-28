#include "Memory.h"

#include<iostream>
#include<cstdlib>
#include<ctime>


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
    this -> treeListLength = 10;
    this -> treeList = new RedBlackTree<MetaMemory>[this -> treeListLength];
}

ScopeMemory::ScopeMemory(size_t lowerBound, size_t upperBound)
{
    this -> lowerBound = lowerBound;
    this -> upperBound = upperBound;
    this -> treeListLength = 10;
    this -> treeList = new RedBlackTree<MetaMemory>[this -> treeListLength];
}

bool ScopeMemory::insertMemory(MetaMemory* node)
{
    srand((int)time(0));
    size_t index = rand() % this -> treeListLength;
    
}

ScopeMemory::~ScopeMemory()
{
    for (int i = 0; i < this -> treeListLength; i ++)
        this -> treeList[i].destroy();
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