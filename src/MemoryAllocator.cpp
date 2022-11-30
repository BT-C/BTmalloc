#include "MemoryAllocator.h"

#include<iostream>
#include<sys/mman.h>


MemoryAllocator::MemoryAllocator()
{
    std::cout << "create memory allocator" << std::endl;
    this -> scopeTree = new RedBlackTree<ScopeMemory>();
    // size_t scopeLowerBound = 0, scopeUpperBound = 1024 * 1024 * 1024;
    size_t scopeLowerBound = 0, scopeUpperBound = 1024;
    size_t row = 4, col = 2;
    // size_t scopeInterval = 1024 * 1024 * 512;
    size_t scopeInterval = 512;
    allocateMmapMutex = new std::mutex();
    row = (scopeUpperBound - scopeLowerBound) / scopeInterval;
    this -> scopeInterval = scopeInterval;
    size_t lowerBound = 0, upperBound = 0;

    // int scopeList[row][col];
    for (int i = 0; i < row; i ++)
    {
        lowerBound = i * scopeInterval + 1;
        upperBound = (i + 1) * scopeInterval;
        this -> scopeTree -> insert(ScopeMemory(lowerBound, upperBound));
    }

    size_t mmapSize = 1024 * 1024 * 1024;
    void *addr = mmap(NULL, mmapSize, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    this -> mmapAddress = addr;
    
    this -> mmapLength = mmapSize;
    this -> lastFreeIndex = 0;

    this -> initMemoryToTree();
    // this -> showTree();
    std::cout << "finish init allocator" << std::endl;
}

void* MemoryAllocator::allocate(size_t memorySize)
{
    memorySize = ((memorySize / 8)) * 8;
    RedBlackNode<ScopeMemory>* findedNode = this -> scopeTree -> search(ScopeMemory(memorySize, memorySize));
    if (findedNode)
    {
        ScopeMemory* scopeMemory = &(findedNode -> key);
        // std::cout << (*scopeMemory) << std::endl;
        // scopeMemory -> showTree();
        void* result = scopeMemory -> allocate(memorySize);
        // scopeMemory -> showTree();
        return result;
    }
    else
    {
        // size_t insertScopeMemoryUpperBound = (size_t(memorySize / this -> scopeInterval) + 1) * this -> scopeInterval;
        // size_t insertScopeMemoryLowerBound = (size_t(memorySize / this -> scopeInterval)) * this -> scopeInterval;
        // this -> scopeTree -> insert(ScopeMemory(insertScopeMemoryLowerBound + 1, insertScopeMemoryUpperBound));
        // findedNode = this -> scopeTree -> search(ScopeMemory(memorySize, memorySize));
        // // findedNode -> key.insertMemory(&metaMemory);
        // ScopeMemory ScopeMemory = findedNode -> key;
        // return ScopeMemory.allocate(memorySize);
        std::cout << "allocate too large" << std::endl;
        return (void *)NULL;
    }
}

void MemoryAllocator::allocateMemoryBack(size_t allocateSize, size_t* allocateAddress)
{
    this -> insertMemory(MetaMemory(allocateSize, (size_t)allocateAddress));
}

void MemoryAllocator::show(RedBlackNode<ScopeMemory>* node)
{
    if (node == NULL)
        return ;
    std::cout << node -> key << std::endl;
    node -> key.showTree();
    show(node -> leftChild);
    show(node -> rightChild);
}

void MemoryAllocator::showTree()
{
    this -> show(this -> scopeTree -> getRoot());
}

void MemoryAllocator::initMemoryToTree()
{
    size_t memNum = 100;
    for (size_t i = 1; i < memNum; i ++)
    {
        // this -> insertMemory(MetaMemory(i * 16 * 1024, i));
        size_t allocateSize = i * 8;
        for (size_t j = 1; j < 100; j ++)
        {
            size_t tempAddress = this -> allocateNewMemoryToTree(allocateSize);
            this -> insertMemory(MetaMemory(allocateSize, tempAddress));
        }
    }
}

void MemoryAllocator::insertMemory(MetaMemory metaMemory)
{
    ScopeMemory scopeMemory(metaMemory.getMemorySize(), metaMemory.getMemorySize());
    RedBlackNode<ScopeMemory>* findedNode = this -> scopeTree -> search(scopeMemory);
    if (findedNode)
    {
        findedNode -> key.insertMemory(&metaMemory);
    }
    else
    {
        // ScopeMemory maxScopeMemory = this -> scopeTree -> maximum();
        // size_t maxScopeMemoryUpperBound = maxScopeMemory.upperBound;
        // size_t insertMemorySize = metaMemory.getMemorySize();
        // size_t insertScopeMemoryUpperBound = (size_t(insertMemorySize / this -> scopeInterval) + 1) * this -> scopeInterval;  
        // size_t insertScopeMemoryLowerBound = (size_t(insertMemorySize / this -> scopeInterval)) * this -> scopeInterval;
        // this -> scopeTree -> insert(ScopeMemory(insertScopeMemoryLowerBound + 1, insertScopeMemoryUpperBound));
        // findedNode = this -> scopeTree -> search(scopeMemory);
        // findedNode -> key.insertMemory(&metaMemory);
        return ;
    }
}

MemoryAllocator& MemoryAllocator::get_instance()
{
    static MemoryAllocator instance;
    return instance;
}

RedBlackTree<ScopeMemory>* MemoryAllocator::getScopeTree()
{
    return this -> scopeTree;
}

MemoryAllocator::~MemoryAllocator()
{
    scopeTree -> destroy();
    munmap((void*)this->mmapAddress, this -> mmapLength);
    std::cout << "delete MemoryAllocator" << std::endl;
}

void* MemoryAllocator::getMmapAddress()
{
    return this -> mmapAddress;
}

size_t MemoryAllocator::getMmapLength()
{
    return this -> mmapLength;
}

size_t MemoryAllocator::getScopeInterval()
{
    return this -> scopeInterval;
}

size_t MemoryAllocator::getLastFreeIndex()
{
    return this -> lastFreeIndex;
}

size_t MemoryAllocator::allocateNewMemoryToTree(size_t allocateSize)
{
    allocateMmapMutex -> lock();

    if (this -> lastFreeIndex + allocateSize + 1 >= this -> mmapLength)
    {
        std::cout << "no other mmap address to allocate" << std::endl;
        return (size_t)NULL;
    }
            
    ((size_t *)this -> mmapAddress)[this -> lastFreeIndex] = allocateSize;
    size_t tempAddress = (size_t)(&(((size_t *)(this -> mmapAddress))[this -> lastFreeIndex + 1]));
    // std::cout << tempAddress << " ";
    this -> lastFreeIndex += allocateSize + 1;
    // this -> insertMemory(MetaMemory(allocateSize, tempAddress));

    allocateMmapMutex -> unlock();

    return tempAddress;
}

