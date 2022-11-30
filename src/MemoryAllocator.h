#ifndef MEMORY_ALLOCATOR
#define MEMORY_ALLOCATOR
#include<iostream>
#include <stddef.h>
#include <cstdlib>
#include <mutex>

#include "RedBlackTree.h"
#include "Memory.h"

class MemoryAllocator
{
    private:
        void* mmapAddress;
        size_t mmapLength;
        size_t scopeInterval;
        size_t lastFreeIndex;
        std::mutex* allocateMmapMutex;

        RedBlackTree<ScopeMemory>* scopeTree;
        MemoryAllocator();
        void insertMemory(MetaMemory m);
        void initMemoryToTree();
    public:
        ~MemoryAllocator();
        MemoryAllocator(const MemoryAllocator&)=delete;
        MemoryAllocator& operator=(const MemoryAllocator&)=delete;
        static MemoryAllocator& get_instance();

        RedBlackTree<ScopeMemory>* getScopeTree();
        void* getMmapAddress();
        size_t getMmapLength();
        size_t getScopeInterval();
        size_t getLastFreeIndex();
        // void addLastFreeIndex(size_t addIndex);

        void* allocate(size_t memorySize);
        void allocateMemoryBack(size_t allocateSize, size_t* allocateAddress);
        size_t allocateNewMemoryToTree(size_t allocateSize);
        void showTree();
        void show(RedBlackNode<ScopeMemory>* node);
};

#endif