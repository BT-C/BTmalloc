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

    if (node -> parent == NULL)
        root = nodeRight;
    else
    {
        if (parent -> leftChild == node)
            parent -> leftChild = nodeRight;
        else
            parent -> rightChild = nodeRight;
    }

    nodeRight -> leftChild = node;
    node -> parent         = nodeRight;
}

