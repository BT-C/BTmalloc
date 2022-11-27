#include<iostream>
#include <iomanip>

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

    // 设置check_remove=1,测试"删除函数"
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

    // 销毁红黑树
    tree -> destroy();

}

int main()
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
        for (int j = 0; j < 4; j ++)
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
    }
    return 1;
}