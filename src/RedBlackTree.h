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

        RedBlackNode(T value, RedBlackColor color, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right);
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
        void insert(RedBlackNode<T>* &root, RedBlackNode<T>* node);
        void insert(T key);
        void insertReBalance(RedBlackNode<T>* &root, RedBlackNode<T>* node);
        void remove(T key);
        void remove(RedBlackNode<T>* &root, RedBlackNode<T>* node);
        void removeReBalance(RedBlackNode<T>* &root, RedBlackNode<T>* childNode, RedBlackNode<T>* parentNode);
};


#endif
