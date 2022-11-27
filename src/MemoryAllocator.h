#ifndef MEMORY_ALLOCATOR
#define MEMORY_ALLOCATOR
#include<iostream>
#include <stddef.h>
#include <cstdlib>



class MemoryAllocator
{
    private:
        MemoryAllocator();
    public:
        ~MemoryAllocator();
        MemoryAllocator(const MemoryAllocator&)=delete;
        MemoryAllocator& operator=(const MemoryAllocator&)=delete;
        static MemoryAllocator& get_instance();
};

class MetaMemory
{
    // private:
    //     size_t memorySize;
    //     size_t address;

    public:
        size_t memorySize;
        size_t address;
        MetaMemory();
        MetaMemory(size_t memory, size_t address);
        size_t getMemorySize();
        size_t getAddress();
        bool operator < (MetaMemory &a);
        bool operator > (MetaMemory &a);
        bool operator == (MetaMemory &a);
        bool operator <= (MetaMemory &a);
        friend std::ostream & operator << (std::ostream &os, MetaMemory &a);
};

#endif