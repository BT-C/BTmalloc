#include "RedBlackTree.h"

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
};

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
};
