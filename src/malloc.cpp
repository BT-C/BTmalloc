#include<iostream>
#include <iomanip>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<pthread.h>
#include<time.h>

#include "Memory.h"
#include "MemoryAllocator.h"
#include "RedBlackTree.h"



// void * MyMalloc(size_t malloc_size)
// {
//     std::cout << sizeof(malloc_size) << std::endl;
//     MemoryAllocator& m1 = MemoryAllocator::get_instance();
//     MemoryAllocator& m2 = MemoryAllocator::get_instance();
//     std::cout << &m1 << std::endl;
//     std::cout << &m2 << std::endl;
//     std::cout << "finish" << std::endl;
//     // m.InitMemoryStruct();
// }

void TestRedBlack()
{
    int a[]= {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int check_insert=0;    // "插入"动作的检测开关(0，关闭；1，打开)
    int check_remove=0;    // "删除"动作的检测开关(0，关闭；1，打开)
    int i;
    int ilen = (sizeof(a)) / (sizeof(a[0])) ;
    RedBlackTree<int>* tree=new RedBlackTree<int>();
    
    std::cout << "== 原始数据: ";
    for(i=0; i<ilen; i++)
        std::cout << a[i] <<" ";
    std::cout << std::endl;

    for(i=0; i<ilen; i++)
    {
        tree->insert(a[i]);
        // 设置check_insert=1,测试"添加函数"
        if(check_insert)
        {
            std::cout << "== 添加节点: " << a[i] << std::endl;
            std::cout << "== 树的详细信息: " << std::endl;
            tree->print();
            std::cout << std::endl;
        }

    }

    std::cout << "== 前序遍历: ";
    tree->preOrder();

    std::cout << "\n== 中序遍历: ";
    tree->inOrder();

    std::cout << "\n== 后序遍历: ";
    tree->postOrder();
    std::cout << std::endl;

    std::cout << "== 最小值: " << tree->minimum() << std::endl;
    std::cout << "== 最大值: " << tree->maximum() << std::endl;
    std::cout << "== 树的详细信息: " << std::endl;
    tree->print();

    if(check_remove)
    {
        for(i=0; i<ilen; i++)
        {
            tree->remove(a[i]);

            std::cout << "== 删除节点: " << a[i] << std::endl;
            std::cout << "== 树的详细信息: " << std::endl;
            tree->print();
            std::cout << std::endl;
        }
    }

    tree -> destroy();

}

void TestRedBlackAllocate()
{
    // MyMalloc(10);
    // TestRedBlack();
    
    MetaMemory m(10, 20);
    // std::cout << m.getAddress() << " " << m.getMemorySize() << std::endl;   
    MetaMemory metaList[10];
    std::cout << sizeof(metaList) / sizeof(metaList[0]) << std::endl;
    int length = sizeof(metaList) / sizeof(metaList[0]);
    for (int i = 0; i < length; i ++)
    {
        metaList[i].memorySize = i * 10;
    }

    RedBlackTree<MetaMemory> *tree = new RedBlackTree<MetaMemory>();
    for (int i = 0; i < length; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
            tree -> insert(MetaMemory(i * 20, 0));
            tree -> preOrder();
            std::cout << std::endl;
        }
        std::cout << "------" << std::endl;
    }

    for (int i = 0; i < length; i ++)
    {
        // std::cout << metaList[i].memorySize << std::endl;
        std::cout << "------------" << std::endl;
        for (int j = 0; j < 6; j ++)
        {
            RedBlackNode<MetaMemory> *result = tree -> search(metaList[i]);
            if (result)
            {
                // std::cout << (result -> key.getMemorySize()) << std::endl;
                tree -> remove(metaList[i]);
                tree -> preOrder();
                std::cout << "----" << std::endl;
            }
            else
                std::cout << "NULL" << std::endl;
        }

        // return 0;
    }
    // return 1;
}

void *MyMalloc(size_t size)
{
    srand(time(NULL));
    MemoryAllocator& mallocator = MemoryAllocator::get_instance();

    // mallocator.showTree();
    // std::cout << "allocate size " << size << std::endl;
    if (size % 8 != 0)
        size = (size / 8 + 1) * 8;
    
    return mallocator.allocate(size);
    // return (void *)1;
}

void MyFree(void* address)
{
    size_t* allocateAddress = (size_t *)address;
    // std::cout << allocateAddress << " ^ " << std::endl;
    size_t allocateSize = *(allocateAddress - 1);
    MemoryAllocator& mallocator = MemoryAllocator::get_instance();
    // std::cout << allocateAddress << " " << allocateSize << std::endl;
    mallocator.allocateMemoryBack(allocateSize, allocateAddress);
}

void TestMalloc()
{
    for (size_t i = 1; i < 4; i ++)
    {
        // void* address = MyMalloc(sizeof(int) * 100);
        void* address = MyMalloc(i);
        MyFree(address);
    }
}


int value = 0;
void* addOne(void* args)
{
    value ++;
    return 0;
}

void* ThreadMalloc(void *args)
{
    size_t size = rand() % 1024;
    void* address = MyMalloc(3);

    // MyFree(address);
    return 0;
}

void TestMultiThread()
{
    size_t numThreads = 30000;
    pthread_t tids[numThreads];
    for (size_t i = 0; i < numThreads; i ++)
    {
        size_t result = pthread_create(&tids[i], NULL, ThreadMalloc, NULL);
    }
    // std::cout << value << std::endl;

    for (size_t i = 0; i < numThreads; i ++)
        pthread_join(tids[i], NULL);
}

int main()
{
    // size_t length = 4;
    // int *arr = (int *)mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_ANON | MAP_SHARED, 0, 0);
    // for (size_t i = 0; i < 100; i ++)
    //     std::cout << arr[i] << std::endl;
    // munmap(arr, length);
    // MemoryAllocator& mallocator = MemoryAllocator::get_instance();
    clock_t start, end;
    MemoryAllocator& mallocator = MemoryAllocator::get_instance();
    start = clock();
    TestMultiThread();    
    end = clock();
    std::cout << "time : " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    
    
    // void *addr = mmap(NULL, 100, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // std::cout << &(((size_t *)addr)[0]) << std::endl;
    // std::cout << &(((size_t *)addr)[1]) << std::endl;
    // size_t address = (size_t)(&(((size_t *)addr)[1]));
    // std::cout << (size_t *)address  << std::endl;
    // std::cout << (size_t *)address << std::endl;


}