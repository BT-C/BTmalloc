#include "MemoryAllocator.h"

#include<iostream>



MemoryAllocator::MemoryAllocator()
{
    std::cout << "create memory allocator" << std::endl;
    this -> scopeTree = new RedBlackTree<ScopeMemory>();
    size_t scopeLowerBound = 0, scopeUpperBound = 1024 * 1024 * 1024;
    size_t row = 4, col = 2;
    size_t scopeInterval = 1024 * 1024;
    row = (scopeUpperBound - scopeLowerBound) / scopeInterval;
    this -> scopeInterval = scopeInterval;
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
    std::cout << std::endl;
    this -> initMemoryToTree();
    this -> showTree();
}

void* MemoryAllocator::allocate(size_t memorySize)
{
    RedBlackNode<ScopeMemory>* findedNode = this -> scopeTree -> search(ScopeMemory(memorySize, memorySize));
    if (findedNode)
    {
        ScopeMemory scopeMemory = findedNode -> key;
        return scopeMemory.allocate(memorySize);
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
    size_t memNum = 400;
    for (size_t i = 1; i < memNum; i ++)
    {
        this -> insertMemory(MetaMemory(i * 16 * 1024, i));
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

MemoryAllocator::~MemoryAllocator()
{
    scopeTree -> destroy();
    std::cout << "delete MemoryAllocator" << std::endl;
}
