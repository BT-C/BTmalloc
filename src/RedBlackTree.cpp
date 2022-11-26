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
    RedBlackNode<T>* parent, * grandparent;

    while ((parent = node -> parent) && parent -> color == RED)
    {
        grandparent = parent -> parent;
        if (parent == grandparent -> leftChild)
        {
            RedBlackNode<T>* uncle = grandparent -> rightChild;
            if (uncle && uncle -> color == RED)
            {
                uncle -> color = BLACK;
                parent -> color = BLACK;
                grandparent -> color = RED;
                node = grandparent;
                continue;
            }

            if (parent -> rightChild == node)
            {
                leftRotate(root, parent);
                RedBlackNode<T>* tempNode = parent;
                parent = node;
                node = tempNode;
            }
            parent -> color = BLACK;
            grandparent -> color = RED;
            rightRotate(root, grandparent);
        }
        else
        {
            RedBlackNode<T>* uncle = grandparent -> leftChild;
            if (uncle && uncle -> color == RED){
                uncle -> color = BLACK;
                parent -> color = BLACK;
                grandparent -> color = RED;
                node = grandparent;
                continue;
            }

            if (parent -> leftChild == node)
            {
                rightRotate(parent);
                RedBlackNode<T>* tempParent = parent;
                parent = node;
                node = tempParent;
            }
            parent -> color = BLACK;
            grandparent -> color = RED;
            leftRotate(root, grandparent);
        }
    }

    root -> color = BLACK;
}

template<class T>
void RedBlackTree<T>::remove(T key)
{
    RedBlackNode<T> *removeNode = NULL;
    if ((removeNode == search(key)) != NULL)
        remove(treeRoot, removeNode);
}

template<class T>
void RedBlackTree<T>::remove(RedBlackNode<T>* &root, RedBlackNode<T>* node)
{
    RedBlackNode<T>* child, * parent;
    RedBlackColor color;

    if ((node -> leftChild != NULL) && (node -> rightChild != NULL))
    {
        RedBlackNode<T>* replace = node;
        replace = replace -> rightChild;
        while (replace -> leftChild)
            replace = replace -> leftChild;

        if (node -> parent != root)
        {
            if (node -> parent -> leftChild == node)
                node -> parent -> leftChild = replace;
            else    
                node -> parent -> rightChild = replace;
        }
        else
            root = replace;

        child = replace -> rightChild;
        parent = replace -> parent;
        color = replace -> color;

        if (parent == node)
            parent = replace;
        else
        {
            if (child)
                child -> parent = parent;
            parent -> left= child;

            replace -> rightChild = node -> rightChild;
            node -> rightChild -> parent = replace;
        }

        replace -> parent = node -> parent;
        replace -> color = node -> color;
        replace -> leftChild = node -> leftChild;
        if (color == BLACK)
            removeReBalance(root, child, parent);
        
        delete node;
        return ;
    }

    if (node -> leftChild != NULL)
        child = node -> leftChild;
    else
        child = node -> rightChild;
    
    parent = node -> parent;
    color = node -> color;

    if (child)
        child -> parent = parent;
    
    if (parent)
    {
        if (parent -> leftChild == node)
            parent -> leftChild = child;
        else
            parent -> rightChild = child;
    }
    else    
        root = child;
    
    if (color == BLACK)
        removeReBalance(root, child, parent);
    
    delete node;
}

template<class T>
void RedBlackTree<T>::removeReBalance(RedBlackNode<T>* &root, RedBlackNode<T>* node, RedBlackNode<T>* parentNode)
{
    RedBlackNode<T>* uncle = NULL;
    while ((!node || node -> color == BLACK && node != root))
    {
        if (parentNode -> left == node)
        {
            uncle = parent -> right;
            if (uncle -> color == RED)
            {

            }

            
        }
        else
        {

        }
    }
}
