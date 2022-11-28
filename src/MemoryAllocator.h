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
        size_t scopeInterval;
        RedBlackTree<ScopeMemory>* scopeTree;
        MemoryAllocator();
        void insertMemory(MetaMemory m);
        void initMemoryToTree();
    public:
        ~MemoryAllocator();
        MemoryAllocator(const MemoryAllocator&)=delete;
        MemoryAllocator& operator=(const MemoryAllocator&)=delete;
        static MemoryAllocator& get_instance();

        void* allocate(size_t memorySize);
        void showTree();
        void show(RedBlackNode<ScopeMemory>* node);
};

#endif