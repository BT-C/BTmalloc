#ifndef REDBLACKTREE
#define REDBLACKTREE

#include <iomanip>

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

        RedBlackNode(T value, RedBlackColor color, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right):
            key(value), color(color), parent(parent), leftChild(left), rightChild(right) {}
};

template<class T>
class RedBlackTree
{
    private:
        RedBlackNode<T> *treeRoot;


    public:
        RedBlackTree():treeRoot(NULL)
        {
            treeRoot = NULL;
        }
        ~RedBlackTree()
        {
            destroy();
        }

        RedBlackNode<T>* getRoot()
        {
            return this -> treeRoot;
        }
                
        RedBlackNode<T>* search(RedBlackNode<T>* x, T key) 
        {
            // if (x && key.memorySize == 400)
            //     std::cout << x -> key -> memorySize << std::endl;
            if (x==NULL || x->key==key)
                return x;
        
            if (key < x->key)
                return search(x->leftChild, key);
            else
                return search(x->rightChild, key);
        }
        
        RedBlackNode<T>* search(T key) 
        {
            return search(treeRoot, key);
        }
        
        void destroy()
        {
            destroy(treeRoot);
        }
        void destroy(RedBlackNode<T>* &tree)
        {
            if (tree == NULL)
                return ;
            
            if (tree -> leftChild != NULL)
                destroy(tree -> leftChild);
            if (tree -> rightChild != NULL)
                destroy(tree -> rightChild);

            delete tree;
            tree = NULL;
        }
        

        void leftRotate(RedBlackNode<T>* &root, RedBlackNode<T>* node)
        {
            RedBlackNode<T>* nodeLeft = node -> leftChild;
            RedBlackNode<T>* nodeRight = node -> rightChild;
            RedBlackNode<T>* parent = node -> parent;

            node -> rightChild = nodeRight -> leftChild;
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
                // node -> parent = root;
                root = nodeLeft;
            else
            {
                if (parent -> leftChild == node)
                    parent -> leftChild = nodeLeft;
                else
                    parent -> rightChild = nodeLeft;
            }

            node -> parent = nodeLeft;
        }

        
        void insert(T key)
        {
            RedBlackNode<T>* insertNode = NULL;
            insertNode = new RedBlackNode<T>(key, BLACK, NULL, NULL, NULL);
            if (insertNode == NULL)
                return ;
            this -> insert(treeRoot, insertNode);
        }

        void insert(RedBlackNode<T>* &root, RedBlackNode<T>* node)
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
        
        void insertReBalance(RedBlackNode<T>* &root, RedBlackNode<T>* node)
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
                        rightRotate(root, parent);
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

        void remove(T key)
        {
            RedBlackNode<T> *removeNode = NULL;
            if ((removeNode = search(key)) != NULL)
            {
                remove(treeRoot, removeNode);
            }
        }

        void remove(RedBlackNode<T>* &root, RedBlackNode<T>* node)
        {
            RedBlackNode<T>* child, * parent;
            RedBlackColor color;

            if ((node -> leftChild != NULL) && (node -> rightChild != NULL))
            {
                RedBlackNode<T>* replace = node;
                replace = replace -> rightChild;
                while (replace -> leftChild)
                    replace = replace -> leftChild;

                if (node -> parent)
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
                    parent -> leftChild = child;

                    replace -> rightChild = node -> rightChild;
                    node -> rightChild -> parent = replace;
                }

                replace -> parent = node -> parent;
                replace -> color = node -> color;
                replace -> leftChild = node -> leftChild;
                node -> leftChild -> parent = replace;
                
                if (color == BLACK)
                    removeReBalance(root, child, parent);
                delete node;
                // preOrder();
                // std::cout << "#######" << std::endl;
                
                return ;
            }

            child = NULL;
            if (node -> leftChild != NULL)
                child = node -> leftChild;
            else
                child = node -> rightChild;
            
            parent = node -> parent;
            // std::cout << node -> key << std::endl;
            color = node -> color;
            if (child)
                child -> parent = parent;
            
            // std::cout << "+++" << std::endl;
            if (parent)
            {
                if (parent -> leftChild == node)
                {
                    parent -> leftChild = child;
                }
                else
                {
                    parent -> rightChild = child;
                }
            }
            else    
                root = child;
            
            // std::cout << parent -> key << std::endl;
            if (color == BLACK)
                removeReBalance(root, child, parent);
            
            delete node;
        }

        void removeReBalance(RedBlackNode<T>* &root, RedBlackNode<T>* node, RedBlackNode<T>* parentNode)
        {
            RedBlackNode<T>* uncle = NULL;
            while ((!node || node -> color == BLACK) && node != root)
            {
                
                if (parentNode -> leftChild == node)
                {
                    uncle = parentNode -> rightChild;
                    if (uncle -> color == RED)
                    {
                        uncle -> color = BLACK;
                        parentNode -> color = RED;
                        leftRotate(root, parentNode);
                        uncle = parentNode -> rightChild;
                    }

                    if (
                        (!uncle -> leftChild || uncle -> leftChild -> color == BLACK) &&
                        (!uncle -> rightChild || uncle -> rightChild -> color == BLACK))
                    {
                        uncle -> color = RED;
                        node = parentNode;
                        parentNode = node -> parent;
                    }
                    else
                    {
                        if (!uncle -> rightChild || uncle -> rightChild -> color == BLACK)
                        {
                            uncle -> leftChild -> color = BLACK;
                            uncle -> color = RED;
                            rightRotate(root, uncle);
                            uncle = parentNode -> rightChild;
                        }

                        uncle -> color = parentNode -> color;
                        parentNode -> color = BLACK;
                        uncle -> rightChild -> color = BLACK;
                        leftRotate(root, parentNode);
                        node = root;
                        break;
                    }
                }
                else
                {
                    // std::cout << "node -> parent " << std::endl;
                    uncle = parentNode -> leftChild;
                    if (uncle -> color == RED)
                    {
                        uncle -> color = BLACK;
                        parentNode -> color = RED;
                        rightRotate(root, parentNode);
                        uncle = parentNode -> leftChild;
                    }

                    // std::cout << "node -> parent " << std::endl;
                    if ((!uncle -> leftChild || uncle -> leftChild -> color == BLACK) && 
                        (!uncle -> rightChild || uncle -> rightChild -> color == BLACK))
                    {
                        uncle -> color = RED;
                        node = parentNode;
                        parentNode = node -> parent;
                    }
                    else
                    {
                        if (!uncle -> leftChild || uncle -> leftChild -> color == BLACK)
                        {
                            uncle -> rightChild -> color = BLACK;
                            uncle -> color = RED;
                            leftRotate(root, uncle);
                            uncle = parentNode -> leftChild;
                        }

                        
                        uncle -> color = parentNode -> color;
                        parentNode -> color = BLACK;
                        uncle -> leftChild -> color = BLACK;
                        rightRotate(root, parentNode);
                        node = root;
                        break;
                    }
                }
            }

            if (node)
                node -> color = BLACK;
        }



        void print(RedBlackNode<T>* tree, T key, int direction)
        {
            if(tree != NULL)
            {
                if(direction==0)    // tree是根节点
                    std::cout << std::setw(2) << tree->key << "(B) is root" << std::endl;
                else                // tree是分支节点
                    std::cout << std::setw(2) << tree->key <<  (tree->color == RED ?"(R)":"(B)") << " is " << std::setw(2) << key << "'s "  << std::setw(12) << (direction==1?"right child" : "left child") << std::endl; 
                print(tree->leftChild, tree->key, -1);
                print(tree->rightChild,tree->key,  1);
            }
        }

        void print()
        {
            if (treeRoot != NULL)
                print(treeRoot, treeRoot->key, 0);
        }


        void preOrder(RedBlackNode<T>* tree) 
        {
            if(tree != NULL)
            {
                std::cout<< tree->key << " " ;
                // if (tree -> parent)
                //     std::cout << "(" << tree->parent->key << ") ";
                preOrder(tree->leftChild);
                preOrder(tree->rightChild);
            }
        }

        void preOrder()
        {
            preOrder(treeRoot);
        }
        
        void inOrder(RedBlackNode<T>* tree) 
        {
            if(tree != NULL)
            {
                inOrder(tree->leftChild);
                std::cout<< tree->key << " " ;
                inOrder(tree->rightChild);
            }
        }

        void inOrder()
        {
            inOrder(treeRoot);
        }

        void postOrder(RedBlackNode<T>* tree) 
        {
            if(tree != NULL)
            {
                postOrder(tree->leftChild);
                postOrder(tree->rightChild);
                std::cout<< tree->key << " " ;
            }
        }


        T minimum()
        {
            RedBlackNode<T> *p = minimum(treeRoot);
            if (p != NULL)
                return p->key;

            return (T)NULL;
        }

        void postOrder()
        {
            postOrder(treeRoot);
        }

        RedBlackNode<T>* minimum(RedBlackNode<T>* tree)
        {
            if (tree == NULL)
                return NULL;

            while(tree->leftChild != NULL)
                tree = tree->leftChild;
            return tree;
        }

        RedBlackNode<T>* maximum(RedBlackNode<T>* tree)
        {
            if (tree == NULL)
                return NULL;

            while(tree->rightChild != NULL)
                tree = tree->rightChild;
            return tree;
        }

        T maximum()
        {
            RedBlackNode<T> *p = maximum(treeRoot);
            if (p != NULL)
                return p->key;

            return (T)NULL;
        }


};

#endif
 
