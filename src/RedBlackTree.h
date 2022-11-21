#ifndef REDBLACKTREE
#define REDBLACKTREE
enum RedBlackColor{RED, BLACK};

template<class T>
class RedBlackNode
{
    public:
        RedBlackColor color;
        T key;
        RedBlackNode *left_child;
        RedBlackNode *right_child;
        RedBlackNode *parent;
};

template<class T>
class RedBlackTree
{
    private:
        RedBlackNode<T> *tree_root;

    public:
        RedBlackTree();
        ~RedBlackTree();

        RedBlackNode<T> *search(T key);
        void insert(T key);
        void remove(T key);
};

#endif
