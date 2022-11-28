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
        RedBlackTree<ScopeMemory>* scopeTree;
        MemoryAllocator();
    public:
        ~MemoryAllocator();
        MemoryAllocator(const MemoryAllocator&)=delete;
        MemoryAllocator& operator=(const MemoryAllocator&)=delete;
        static MemoryAllocator& get_instance();
};

#endif