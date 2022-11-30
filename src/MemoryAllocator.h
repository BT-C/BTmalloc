#ifndef MEMORY_ALLOCATOR
#define MEMORY_ALLOCATOR
#include<iostream>
#include <stddef.h>
#include <cstdlib>

#include "RedBlackTree.h"
#include "Memory.h"

class MemoryAllocator
{
    private:
        void* mmapAddress;
        // size_t mmapLength;
        // size_t scopeInterval;
        // size_t lastFreeIndex;

        RedBlackTree<ScopeMemory>* scopeTree;
        MemoryAllocator();
        void insertMemory(MetaMemory m);
        void initMemoryToTree();
    public:
        size_t mmapLength;
        size_t scopeInterval;
        size_t lastFreeIndex;
        
        ~MemoryAllocator();
        MemoryAllocator(const MemoryAllocator&)=delete;
        MemoryAllocator& operator=(const MemoryAllocator&)=delete;
        static MemoryAllocator& get_instance();

        RedBlackTree<ScopeMemory>* getScopeTree();
        void* allocate(size_t memorySize);
        void showTree();
        void show(RedBlackNode<ScopeMemory>* node);
};

#endif