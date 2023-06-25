#include <iostream>
#include "Node.hpp"

template <typename T>
class BinarySearchTree
{
private:
    Node<T>* root;
protected:
//helper methods for public methods
    int getHeightHelper(Node<T>*) const;
    int getNumberOfNodesHelper(Node<T>*) const;

    void destroyTree(Node<T>*);
    Node<T>* balancedAdd(Node<T>* tree, Node<T>* newNode);
    Node<T>* removeValue(Node<T>* tree, const T target);
    Node<T>* findNode(Node<T>* tree, const T& target) const;
    Node<T>* copyTree(const Node<T>*) const;
    void preorderHelper(Node<T>*) const;
    void inorderHelper(Node<T>*) const;
    void postorderHelper(Node<T>*) const;
public:
    BinarySearchTree();
    BinarySearchTree(const T&);
    BinarySearchTree(const T&, const BinarySearchTree<T>* leftTree, const BinarySearchTree<T>* rightTree);
    BinarySearchTree(const BinarySearchTree<T>&);
    ~BinarySearchTree();
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>&);
    
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes()  const;
    T getRootData() const; 
    void setRootData(const T&);
    void add(const T&);
    void remove(const T&);
    void clear();
    bool contains(const T&) const;
    void print() const;
    void preorder() const;
    void inorder() const;
    void postorder() const;

};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root{nullptr} {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T& val)  
{
    root = new Node<T>(val);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T& val, const BinarySearchTree<T>* leftTree, const BinarySearchTree<T>* rightTree)
{
    root = new Node<T>(val, copyTree(leftTree->root), copyTree(rightTree->root));
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& src)
{
    root = copyTree(src.root);
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    destroyTree(root);
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& src)
{
    if (this == &src)
    {
        return *this;
    }

    delete root;
    root = copyTree(src.root);
}


template <typename T>
bool BinarySearchTree<T>::isEmpty() const
{
    return getNumberOfNodes() == 0;
}

template <typename T>
int BinarySearchTree<T>::getHeight() const
{
    return getHeightHelper(root);
}

template <typename T>
int BinarySearchTree<T>::getNumberOfNodes()  const
{
    return getNumberOfNodesHelper(root);
}

template <typename T>
T BinarySearchTree<T>::getRootData() const
{
    return root->getData();
}

template <typename T>
void BinarySearchTree<T>::setRootData(const T& val)
{
    root->setData(val);
}

template <typename T>
void BinarySearchTree<T>::add(const T& val)
{
    Node<T>* newNode = new Node<T>(val);
    root = balancedAdd(root, newNode);
}

template <typename T>
void BinarySearchTree<T>::remove(const T& val)
{
    root = removeValue(root, val);
}

template <typename T>
void BinarySearchTree<T>::clear()
{
    destroyTree(root);
}


template <typename T>
bool BinarySearchTree<T>::contains(const T& val) const
{
    Node<T>* node = new Node<T>(val);
    Node<T>* contain = findNode(root, val);
    return node->getData() ==  contain->getData();
}

template <typename T>
void BinarySearchTree<T>::print() const
{
    inorder();
}


template <typename T>
void BinarySearchTree<T>::preorder() const
{
    preorderHelper(root);
}

template <typename T>
void BinarySearchTree<T>::inorder() const
{
    inorderHelper(root);
}

template <typename T>
void BinarySearchTree<T>::postorder() const
{
    postorder(root);
}








template <typename T>
int BinarySearchTree<T>::getHeightHelper(Node<T>* tree) const
{
    if (tree == nullptr) {
        return 0;
    }
    else {
        return 1 + std::max(getHeightHelper(tree->getLeftChild()), getHeightHelper(tree->getRightChild()));
    }
}

template <typename T>
int BinarySearchTree<T>::getNumberOfNodesHelper(Node<T>* tree) const
{
    if (tree == nullptr) {
        return 0;
    }
    else {
        int left = getNumberOfNodesHelper(tree->getLeftChild());
        int right = getNumberOfNodesHelper(tree->getRightChild());
        return 1 + left + right;
    }
}

template <typename T>
Node<T>* BinarySearchTree<T>::balancedAdd(Node<T>* tree, Node<T>* newNode)
{
    if (tree == nullptr) {
        return newNode;
    }
    else {
        Node<T>* leftNode = tree->getLeftChild();
        Node<T>* rightNode = tree->getRightChild();
        if (newNode->getData() > tree->getData()) {
            rightNode = balancedAdd(rightNode, newNode);
            tree->setRightChild(rightNode);
        }
        else if (newNode->getData() < tree->getData()){
            leftNode = balancedAdd(leftNode, newNode);
            tree->setLeftChild(leftNode);
        }
        return tree;
    }
}

template <typename T>
Node<T>* BinarySearchTree<T>::removeValue(Node<T>* tree, const T target)
{
    if (tree == nullptr) {
        return nullptr;
    }
    else if (target == tree->getData()) {
        if (tree->isLeaf()) {
            delete tree;
            return nullptr;
        }
        else if (tree->getRightChild() == nullptr && tree->getLeftChild() != nullptr) {
            Node<T>* left = tree->getLeftChild();
            delete tree;
            return left;
        }
        else if (tree->getLeftChild() == nullptr && tree->getRightChild() != nullptr) {
            Node<T>* right = tree->getRightChild();
            delete tree;
            return right;
        }
        else {
            Node<T>* right = tree->getRightChild();
            while (!right->getLeftChild()->isLeaf()) {
                right = right->getLeftChild();
            }
            tree->setData(right->getLeftChild()->getData());
            right->setLeftChild(removeValue(right->getLeftChild(),right->getLeftChild()->getData()));
            return tree;
        }

    }

    tree->setLeftChild(removeValue(tree->getLeftChild(), target));
    tree->setRightChild(removeValue(tree->getRightChild(), target));
 
    
    
    return tree;
}

template <typename T>
Node<T>* BinarySearchTree<T>::findNode(Node<T>* tree, const T& target) const
{
    if (tree == nullptr) {
        return nullptr;
    }

    if (tree->getData() == target) {
        return tree;
    }

    Node<T>* found = findNode(tree->getLeftChild(), target);
    if (found == nullptr) {
        found = findNode(tree->getRightChild(), target);
    }
    
    return found;
}


template <typename T>
Node<T>* BinarySearchTree<T>::copyTree(const Node<T>* tree) const
{
    Node<T>* copy = nullptr;
    if (tree != nullptr) {
        copy = new Node<T>(tree->getData());
        copy->setLeftChild((tree->getLeftChild()));
        copy->setRightChild(copyTree(tree->getRightChild()));
    }
    return copy;
}

template <typename T>
void BinarySearchTree<T>::destroyTree(Node<T>* tree)
{
    if (tree != nullptr) {
        destroyTree(tree->getLeftChild());
        destroyTree(tree->getRightChild());
        delete tree;
    }

}

template <typename T>
void BinarySearchTree<T>::preorderHelper(Node<T>* tree) const
{
    if (tree == nullptr) {
        return;
    }

    std::cout << tree->getData() << " ";
    preorderHelper(tree->getLeftChild());
    preorderHelper(tree->getRightChild());
}    
    
template <typename T>
void BinarySearchTree<T>::inorderHelper(Node<T>* tree) const
{
    if (tree == nullptr) {
        return;
    }

    inorderHelper(tree->getLeftChild());
    std::cout << tree->getData() << " ";
    inopderHelper(tree->getRightChild());
}

template <typename T>
void BinarySearchTree<T>::postorderHelper(Node<T>* tree) const
{
    if (tree == nullptr) {
        return;
    }

    postoderHelper(tree->getLeftChild());
    postorderHelper(tree->getRightChild());
    std::cout << tree->getData() << " ";
}