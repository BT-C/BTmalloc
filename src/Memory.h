#ifndef MEMORY
#define MEMORY
#include <iostream>
#include <stddef.h>
#include <cstdlib>
#include <mutex>

#include "RedBlackTree.h"

class MetaMemory
{
    // private:
    //     size_t memorySize;
    //     size_t address;

    public:
        size_t memorySize;
        size_t address;
        MetaMemory();
        MetaMemory(size_t memorySize, size_t address);
        size_t getMemorySize();
        size_t getAddress();
        bool operator < (MetaMemory& a);
        bool operator > (MetaMemory& a);
        bool operator == (MetaMemory& a);
        bool operator <= (MetaMemory& a);
        friend std::ostream & operator << (std::ostream &os, MetaMemory &a);
};

class ScopeMemory
{
    public:
        size_t lowerBound;
        size_t upperBound;
        size_t treeListLength;
        std::mutex *mutexList;
        RedBlackTree<MetaMemory>* treeList;
        
        // MemoryAllocator* memoryAllocator;

        ScopeMemory();
        ScopeMemory(size_t lowerBound, size_t upperBound);
        // ScopeMemory(size_t lowerBound, size_t upperBound, MemoryAllocator* memoryAllocator);
        ~ScopeMemory();

        void insertMemory(MetaMemory* node);
        void* allocate(size_t memorySize);

        // void modifyBound();
        void showTree();
        bool operator < (ScopeMemory& a);
        bool operator > (ScopeMemory& a);
        bool operator == (ScopeMemory& a);
        bool operator <= (ScopeMemory& a);
        friend std::ostream & operator << (std::ostream& os, ScopeMemory& a);
};

#endif