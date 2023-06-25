#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include "Node.hpp"

template <typename T>
class BinaryTree 
{
private:
    Node<T>* root;
protected:
//helper methods for public methods
    int getHeightHelper(Node<T>*) const;
    int getNumberOfNodesHelper(Node<T>*) const;

    void destroyTree(Node<T>*);//void destroyTree(BinaryNode<ItemType>* subTreePtr);
    Node<T>* balancedAdd(Node<T>* node, Node<T>* newNode);
    Node<T>* removeValue(Node<T>* node, const T target);
    Node<T>* findNode(Node<T>* node, const T& target) const;
    Node<T>* copyTree(const Node<T>*) const;
    void preorderHelper(Node<T>* node) const;
    void inorderHelper(Node<T>* node) const;
    void postorderHelper(Node<T>* node) const;
public:
    BinaryTree();
    BinaryTree(const T&);
    BinaryTree(const T&, const BinaryTree<T>* leftTree, const BinaryTree<T>* rightTree);
    BinaryTree(const BinaryTree<T>&);
    ~BinaryTree();
    BinaryTree<T>& operator=(const BinaryTree<T>& );
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

#include "BinaryTree.tpp"

#endif
