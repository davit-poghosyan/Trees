#include "Node.h"

template <typename T>
class AVLTree
{
private:
    Node<T>* root;
private:
    int getHeightHelper(Node<T>*) const;
    int getNumberOfNodesHelper(Node<T>*) const;
    void destroyTree(Node<T>*);
    Node<T>* balancedAdd(Node<T>*, Node<T>*);
    Node<T>* removeHelper(Node<T>*,const T&);
    Node<T>* findNode(Node<T>*, const T&) const;
    Node<T>* copyTree(Node<T>*) const;  
    Node<T>* getMin(Node<T>*) const;
    Node<T>* getMax(Node<T>*) const;
    Node<T>* getPredecessor(Node<T>*) const;
    Node<T>* getSuccessor(Node<T>*) const;
    void preorder(Node<T>*) const;
    void inorder(Node<T>*) const;
    void postorder(Node<T>*) const;
    int balanceFactor(Node<T>*) const;
    Node<T>* leftRotate(Node<T>*);
    Node<T>* rightRotate(Node<T>*);
public:
    AVLTree();
    AVLTree(const T&);
    AVLTree(const T&, const AVLTree<T>*, const AVLTree<T>*);
    AVLTree(const AVLTree&);
    ~AVLTree();

public:
    bool isEmpty() const;
    int getHeight() const;
    int getNumberofNodes() const;
    Node<T>* getRootData() const;
    void add(const T&);
    void remove(const T&);
    void clear();
    bool contains(const T&) const;
public:
    void preorderTraverse() const;
    void inorderTraverse() const;
    void postorderTraverse() const;
};


template <typename T>
int AVLTree<T>::getHeightHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return 0;
    }

    return std::max(getHeightHelper(node->getLeftChild()), getHeightHelper(node->getRightChild())) + 1;
}

template <typename T>
int AVLTree<T>::getNumberOfNodesHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return 0;
    }

    int left = getNumberOfNodesHelper(node->getLeftChild());
    int right = getNumberOfNodesHelper(node->getRightChild());

    return left + right + 1;
}

template <typename T>
void AVLTree<T>::destroyTree(Node<T>* node)
{
    if (node != nullptr) {
        destroyTree(node->getLeftChild());
        destroyTree(node->getRightChild());
        delete node;
        node = nullptr;
    }
}

template <typename T>
Node<T>* AVLTree<T>::balancedAdd(Node<T>* node, Node<T>* newNode)
{
    if (node == nullptr) {
        return newNode;
    }

    Node<T>* left = node->getLeftChild();
    Node<T>* right = node->getRightChild();

    if (node->getVal() > newNode->getVal()) {
        left = balancedAdd(left, newNode);
        node->setLeftChild(left);
    }
    else {
        right = balancedAdd(right, newNode);
        node->setRightChild(right);
    }

    int  balance = balanceFactor(node);
    //left - left
    if (balance > 1 && node->getLeftChild()->getVal() > newNode->getVal()) {
        node = rightRotate(node);
    } 
    //left - right
    else if (balance > 1 && node->getLeftChild()->getVal() < newNode->getVal()) {
        node->setLeftChild(leftRotate(node->getLeftChild()));
        node = rightRotate(node);
    }
    //right - right
    else if (balance < -1 && node->getRightChild()->getVal() < newNode->getVal()) {
        node = leftRotate(node);
    }
    //right - left
    else if (balance < -1 && node->getRightChild()->getVal() > newNode->getVal()) {
        node->setRightChild(rightRotate(node->getRightChild()));
        node = leftRotate(node);
    }


    return node;
}

template <typename T>
Node<T>* AVLTree<T>::removeHelper(Node<T>* node, const T& val)
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->getVal() > val) {
        node->setLeftChild(removeHelper(node->getLeftChild(), val));
    }
    else if (node->getVal() < val) {
        node->setRightChild(removeHelper(node->getRightChild(), val));
    }
    else {
        if (node->getLeftChild() == nullptr) {
            Node<T>* right = node->getRightChild();
            delete node;
            return right;
        }
        else if (node->getRightChild() == nullptr) {
            Node<T>* left = node->getLeftChild();
            delete node;
            return left;
        }
        else {
            Node<T>* successor = getSuccessor(node);
            node->setVal(successor->getVal());
            node->setRightChild(removeHelper(node->getRightChild(), successor->getVal()));
        }
    }

    int  balance = balanceFactor(node);

    //left - left
    if (balance > 1 && balanceFactor(node->getLeftChild()) >= 0) {
        node = rightRotate(node);
    } 
    //left - right
    else if (balance > 1 && balanceFactor(node->getLeftChild()) < 0) {
       node->setLeftChild(rightRotate(node->getLeftChild()));
       node = leftRotate(node);
    }
    //right - right
    else if (balance < -1 && balanceFactor(node->getRightChild()) <= 0) {
        node = leftRotate(node);
    }
    //right - left
    else if (balance < -1 && balanceFactor(node->getRightChild()) > 0) {
        node->setRightChild(leftRotate(node->getRightChild()));
        node = rightRotate(node);
    }

    return node;  

}

template <typename T>
Node<T>* AVLTree<T>::findNode(Node<T>* node, const T& val) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->getVal() > val) {
        return findNode(node->getLeftChild(), val);
    }
    else if (node->getVal() < val) {
        return findNode(node->getRightChild(), val);
    }
    else {
        return node;
    }
} 

template <typename T>
Node<T>* AVLTree<T>::copyTree(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }

    Node<T>* newNode = new Node<T>;
    newNode->getLeftChild(copyTree(node->getLeftChild()));
    newNode->getRightChild(copyTree(node->getRightChild()));
    return newNode;
}

template <typename T>
Node<T>* AVLTree<T>::getMin(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }

    while (node->getRightChild() != nullptr) {
        node = node->getLeftChild();
    }
    
    return node;
}

template <typename T>
Node<T>* AVLTree<T>::getMax(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }

    while (node->getRightChild() != nullptr) {
        node = node->getRightChild();
    }

    return node;
}

template <typename T>
Node<T>* AVLTree<T>::getPredecessor(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->getLeftChild() != nullptr) 
    {
        return getMax(node->getLeftChild());
    }
    else {
        Node<T>* predecessor = nullptr;
        Node<T>* ancestor = root;

        while (ancestor != node){
            if (ancestor->getVal() > node->getVal()) {
                ancestor = ancestor->getLeftChild();
            }
            else {
                predecessor = ancestor;
                ancestor = ancestor->getRightChild();
            }
        }

        return predecessor;
    }
}

template <typename T>
Node<T>* AVLTree<T>::getSuccessor(Node<T>*  node) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if(node->getRightChild() != nullptr) {
        return getMin(node->getRightChild());
    }
    else {
        Node<T>* successor = nullptr;
        Node<T>* ancestor = root;

        while (ancestor != nullptr) {
            if (ancestor->getVal() > node->getVal()) {
                successor = ancestor;
                ancestor = ancestor->getLeftChild();
            }
            else {
                ancestor = ancestor->getRightChild();
            }
        }

        return successor;
    }
}

template <typename T>
void AVLTree<T>::preorder(Node<T>* node) const
{   
    if (node != nullptr) {
        std::cout << node->getVal() << " ";
        preorder(node->getLeftChild());
        preorder(node->getRightChild());
    }
}

template <typename T>
void AVLTree<T>::inorder(Node<T>* node) const
{   
    if (node != nullptr) {
        inorder(node->getLeftChild());
        std::cout << node->getVal() << " ";
        inorder(node->getRightChild());
    }
}

template <typename T>
void AVLTree<T>::postorder(Node<T>* node) const
{   
    if (node != nullptr) {
        postorder(node->getLeftChild());
        postorder(node->getRightChild());
        std::cout << node->getVal() << " ";
    }
}

template <typename T>
int AVLTree<T>::balanceFactor(Node<T>* node) const
{
    return getHeightHelper(node->getLeftChild()) - getHeightHelper(node->getRightChild());
}

template <typename T>
Node<T>* AVLTree<T>::leftRotate(Node<T>* node)
{
    Node<T>* right = node->getRightChild();
    node->setRightChild(right->getLeftChild());
    right->setLeftChild(node);
    
    return right;
}

template <typename T>
Node<T>* AVLTree<T>::rightRotate(Node<T>* node)
{
    Node<T>* left = node->getLeftChild();
    node->setLeftChild(left->getRightChild());
    left->setRightChild(node);

    return left;
}


template <typename T>
AVLTree<T>::AVLTree() : root{nullptr} {} 

template <typename T>
AVLTree<T>::AVLTree(const T& val) : root{new Node(val)} {}

template <typename T>
AVLTree<T>::AVLTree(const T& val, const AVLTree<T>* leftSubTree, const AVLTree<T>* rightSubTree) 
{
    root = new Node(val);
    root->getLeftChild(copyTree(leftSubTree));
    root->getRightChild(copyTree(rightSubTree));
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
{
    root = copyTree(tree->getRootData());
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    destroyTree(root);
}

template <typename T>
bool AVLTree<T>::isEmpty() const
{
    return (root == nullptr);
}

template <typename T>
int AVLTree<T>::getHeight() const
{
    return getHeightHelper(root);
}

template <typename T>
int AVLTree<T>::getNumberofNodes() const
{
    return getNumberOfNodesHelper(root);
}

template <typename T>
Node<T>* AVLTree<T>::getRootData() const
{
    return root;
}

template <typename T>
void AVLTree<T>::add(const T& val)
{
    root = balancedAdd(root, new Node(val));
}

template <typename T>
void AVLTree<T>::remove(const T& val)
{
    root = removeHelper(root, val);
}

template <typename T>
void AVLTree<T>::clear()
{
    destroyTree(root);
}

template <typename T>
bool AVLTree<T>::contains(const T& val) const
{
    return (findNode(root, val) != nullptr);
}

template <typename T>
void AVLTree<T>::preorderTraverse() const
{
    preorder(root);
}

template <typename T>
void AVLTree<T>::inorderTraverse() const
{
    inorder(root);
}

template <typename T>
void AVLTree<T>::postorderTraverse() const
{
    postorder(root);
}

