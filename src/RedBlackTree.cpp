#include "RedBlackTree.h"


template<class T>
RedBlackNode<T>::RedBlackNode(T value, RedBlackColor color, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right):
    key(value), color(color), parent(parent), leftChild(left), rightChild(right) {}

template<class T>
void RedBlackTree<T>::leftRotate(RedBlackNode<T>* &root, RedBlackNode<T>* node)
{
    RedBlackNode<T>* nodeLeft   = node -> leftChild;
    RedBlackNode<T>* nodeRight  = node -> rightChild;
    RedBlackNode<T>* parent    = node -> parent;

    node -> rightChild     = nodeRight -> leftChild;
    if (nodeRight -> leftChild)
        nodeRight -> leftChild -> parent = node;
    nodeRight -> parent    = parent;
    nodeRight -> leftChild = node;

    if (node -> parent == NULL)
        root = nodeRight;
    else
    {
        if (parent -> leftChild == node)
            parent -> leftChild = nodeRight;
        else
            parent -> rightChild = nodeRight;
    }

    node -> parent = nodeRight;
}

template<class T>
void rightRotate(RedBlackNode<T>* &root, RedBlackNode<T>* node)
{
    RedBlackNode<T>* nodeLeft  = node -> leftChild;
    RedBlackNode<T>* nodeRight = node -> rightChild;
    RedBlackNode<T>* parent    = node -> parent;

    node -> leftChild = nodeLeft -> rightChild;
    if (nodeLeft -> rightChild)
        nodeLeft -> rightChild -> parent = node;
    nodeLeft -> parent = parent;
    nodeLeft -> rightChild = node;

    if (node -> parent == NULL)
        node -> parent = root;
    else
    {
        if (parent -> leftChild == node)
            parent -> leftChild = nodeLeft;
        else
            parent -> rightChild = nodeLeft;
    }

    node -> parent = nodeLeft;
}

template<class T>
void RedBlackTree<T>::insert(T key)
{
    RedBlackNode<T>* insertNode = NULL;
    insertNode = new RedBlackNode<T>(key, BLACK, NULL, NULL, NULL);
    if (insertNode == NULL)
        return ;
    this -> insert(treeRoot, insertNode);
}


template<class T>
void RedBlackTree<T>::insert(RedBlackNode<T>* &root, RedBlackNode<T>* node)
{
    RedBlackNode<T>* pre  = NULL;
    RedBlackNode<T>* next = root;

    while (next != NULL)
    {
        pre = next;
        if (node -> key <= next -> key)
            next = next -> leftChild;
        else
            next = next -> rightChild;
    }

    node -> parent = pre;
    if (pre == NULL)
        root = node;
    else
    {
        if (node -> key <= pre -> key)
            pre -> leftChild = node;
        else    
            pre -> rightChild = node;
    }
        

    node -> color = RED;
    insertReBalance(root, node);
}

template<class T>
void RedBlackTree<T>::insertReBalance(RedBlackNode<T>* &root, RedBlackNode<T>* node)
{
    
}