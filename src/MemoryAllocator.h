#ifndef MEMORY_ALLOCATOR
#define MEMORY_ALLOCATOR

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

#endif