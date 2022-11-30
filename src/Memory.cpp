#include "Memory.h"
#include "MemoryAllocator.h"

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<mutex>


MetaMemory::MetaMemory(){
    this -> memorySize = 0;
    this -> address = 0;
}

MetaMemory::MetaMemory(size_t memorySize, size_t address)
{
    this -> memorySize = memorySize;
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
    // this -> memoryAllocator = NULL;
    // MemoryAllocator& mallocator = MemoryAllocator::get_instance();
    this -> mutexList = new std::mutex[this -> treeListLength];
    this -> treeList = new RedBlackTree<MetaMemory>[this -> treeListLength];
}

ScopeMemory::ScopeMemory(size_t lowerBound, size_t upperBound)
{
    this -> lowerBound = lowerBound;
    this -> upperBound = upperBound;
    this -> treeListLength = 1;
    this -> mutexList = new std::mutex[this -> treeListLength];
    this -> treeList = new RedBlackTree<MetaMemory>[this -> treeListLength];
}

// ScopeMemory::ScopeMemory(size_t lowerBound, size_t upperBound, MemoryAllocator* memoryAllocator)
// {
//     this -> lowerBound = lowerBound;
//     this -> upperBound = upperBound;
//     this -> treeListLength = 10;
//     this -> memoryAllocator = memoryAllocator;
//     this -> treeList = new RedBlackTree<MetaMemory>[this -> treeListLength];
// }

void ScopeMemory::insertMemory(MetaMemory* node)
{
    // srand((int)time(0));
    size_t index = rand() % (this -> treeListLength);
    // std::cout << "index :" << index << std::endl;
    this -> mutexList[index].lock();
    this -> treeList[index].insert((*node));
    this -> mutexList[index].unlock();
}

void* ScopeMemory::allocate(size_t memorySize)
{
    size_t index = rand() % (this -> treeListLength);
    this -> mutexList[index].lock();

    RedBlackNode<MetaMemory>* result = this -> treeList[index].search(MetaMemory(memorySize, 0));
    if (result)
    {
        void *address = (void *)(result -> key.getAddress());
        treeList[index].remove(MetaMemory(memorySize, 0));
        this -> mutexList[index].unlock();
        return address;
    }
    else
    {
        MemoryAllocator& memoryAllocator = MemoryAllocator::get_instance();
        void* mmapAddress = memoryAllocator.getMmapAddress();
        size_t mmapLength = memoryAllocator.getMmapLength();
        size_t lastFreeIndex = memoryAllocator.getLastFreeIndex();

        for (size_t i = 0; i < 5; i ++)
        {
            size_t allocateSize = memorySize;
            size_t tempAddress = memoryAllocator.allocateNewMemoryToTree(allocateSize);
            this -> treeList[index].insert(MetaMemory(allocateSize, tempAddress));
        }
        size_t allocateSize = memorySize;
        size_t tempAddress = memoryAllocator.allocateNewMemoryToTree(allocateSize);
        this -> mutexList[index].unlock();
        return (void *)tempAddress;
    }
}

ScopeMemory::~ScopeMemory()
{
    for (int i = 0; i < this -> treeListLength; i ++)
        this -> treeList[i].destroy();
}

void ScopeMemory::showTree()
{
    for (size_t i = 0; i < this -> treeListLength; i ++)
    {
        std::cout << "MetaMemory Tree " << i << " : ";
        this -> treeList[i].preOrder();
        std::cout << std::endl;
    }
    
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
    // std::cout << std::endl;
    // for (size_t i = 0; i < a.treeListLength; i ++)
    // {
    //     a.treeList[i].preOrder();
    //     std::cout << std::endl;
    // }
    return os;
}

