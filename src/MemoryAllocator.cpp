#include "MemoryAllocator.h"

#include<iostream>


MemoryAllocator::MemoryAllocator()
{
    std::cout << "create memory allocator" << std::endl;
    this -> scopeTree = new RedBlackTree<ScopeMemory>();
    size_t row = 4, col = 2;
    size_t scopeInterval = 1024 * 1024;
    size_t lowerBound = 0, upperBound = 0;

    // int scopeList[row][col];
    for (int i = 0; i < row; i ++)
    {
        // scopeList[i][0] = i * scopeInterval;
        // scopeList[i][1] = (i + 1) * scopeInterval;
        lowerBound = i * scopeInterval + 1;
        upperBound = (i + 1) * scopeInterval;
        this -> scopeTree -> insert(ScopeMemory(lowerBound, upperBound));
    }

    this -> scopeTree -> preOrder();
}

void MemoryAllocator::insertMemory(MetaMemory metaMemory)
{
    ScopeMemory scopeMemory(metaMemory.getMemorySize(), metaMemory.getMemorySize());
    RedBlackNode<ScopeMemory>* findedNode = this -> scopeTree -> search(scopeMemory);
    if (findedNode)
    {
        // findedNode -> key.insertMemory(&metaMemory);
    }
    else
    {

    }
}

MemoryAllocator& MemoryAllocator::get_instance()
{
    static MemoryAllocator instance;
    return instance;
}

MemoryAllocator::~MemoryAllocator()
{
    scopeTree -> destroy();
    std::cout << "delete MemoryAllocator" << std::endl;
}
