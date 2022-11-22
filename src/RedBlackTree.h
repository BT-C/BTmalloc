#ifndef REDBLACKTREE
#define REDBLACKTREE
enum RedBlackColor{RED, BLACK};

template<class T>
class RedBlackNode
{
    public:
        RedBlackColor color;
        T key;
        RedBlackNode *leftChild;
        RedBlackNode *rightChild;
        RedBlackNode *parent;
};

template<class T>
class RedBlackTree
{
    private:
        RedBlackNode<T> *treeRoot;

    public:
        RedBlackTree();
        ~RedBlackTree();

        RedBlackNode<T> *search(T key);
        void leftRotate(RedBlackNode<T>* &root, RedBlackNode<T>* node);
        void rightRotate(RedBlackNode<T>* &root, RedBlackNode<T>* node);
        void insert(T key);
        void remove(T key);

};


#endif
