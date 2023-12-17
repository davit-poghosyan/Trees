#include "node.h"

template <typename T>
class BST
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
public:
    BST();
    BST(const T&);
    BST(const T&, const BST<T>*, const BST<T>*);
    BST(const BST&);
    ~BST();

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
int BST<T>::getHeightHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return 0;
    }

    int left = getHeightHelper(node->getLeftChild()) + 1;
    int right = getHeightHelper(node->getRightChild()) + 1;

    return std::max(left, right);

}

template <typename T>
int BST<T>::getNumberOfNodesHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return 0;
    }

    return getNumberOfNodesHelper(node->getLeftChild()) + getNumberOfNodesHelper(node->getRightChild()) + 1;
}


template <typename T>
void BST<T>::destroyTree(Node<T>* root)
{
    if (root != nullptr) {
        destroyTree(root->getLeftChild());
        destroyTree(root->getRightChild());
        delete root;
        root = nullptr;
    }
}

template <typename T>
Node<T>* BST<T>::balancedAdd(Node<T>* node, Node<T>* newNode)
{
    if (node == nullptr) {
        return newNode;
    }
    else {
        Node<T>* left = node->getLeftChild();
        Node<T>* right = node->getRightChild();

        if (newNode->getVal() > node->getVal()) {
            right = balancedAdd(right, newNode);
            node->setRightChild(right);
        }
        else if (newNode->getVal() < node->getVal()) {
            left = balancedAdd(left, newNode);
            node->setLeftChild(left);
        }
        return node;
    }
}


template <typename T>
Node<T>* BST<T>::removeHelper(Node<T>* node, const T& val) 
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
            Node<T>* successor = getSuccessor(node->getRightChild());
            std::cout << successor->getVal() << "\n";
            node->setVal(successor->getVal());
            node->setRightChild(removeHelper(node->getRightChild(), successor->getVal()));
        }
    }
    return node;
}

template <typename T>
Node<T>* BST<T>::findNode(Node<T>* node, const T& val) const
{
    if (node == nullptr || node->getVal() == val) {
        return node;
    }

    if (val < node->getVal()) {
        // Search in the left subtree
        return findNode(node->getLeftChild(), val);
    } else {
        // Search in the right subtree
        return findNode(node->getRightChild(), val);
    }
}





template <typename T>
Node<T>* BST<T>::copyTree(Node<T>* node) const
{
    if (node == nullptr) {
        return node;
    }

    Node<T>* copyNode = new Node(node->getVal());
    copyNode->setLeftChild(copyTree(node->getLeftChild()));
    copyNode->setRightChild(copyTree(node->getRightChild()));

    return copyNode;
}

template <typename T>
Node<T>* BST<T>::getMin(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }
    while (node->getLeftChild() != nullptr) {
        node = node->getLeftChild();
    }
    return node;
}

template <typename T>
Node<T>* BST<T>::getMax(Node<T>* node) const
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
Node<T>* BST<T>::getPredecessor(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->getLeftChild() != nullptr) 
    {
        return node->getMax(node->getLeftChild());
    }
    else {
        Node<T>* predescessor = nullptr;
        Node<T>* ancestor = root;

        while (ancestor != node) {
            if (ancestor->getVal() < node->getVal()) {
                predescessor = ancestor;
                ancestor = ancestor->getRightChild();
            }
            else {
                ancestor = ancestor->getLeftChild();
            }
        }
        return predescessor;
    }   
}

template <typename T>
Node<T>* BST<T>::getSuccessor(Node<T>* node) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->getRightChild() != nullptr) {
        return getMin(node->getRightChild());
    }
    else {
        Node<T>* successor = nullptr;
        Node<T>* ancestor = root;

        while (ancestor->getVal() != node->getVal()) {
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
void BST<T>::preorder(Node<T>* node) const
{
    if (node != nullptr) {
        std::cout << node->getVal() << " ";
        preorder(node->getLeftChild());
        preorder(node->getRightChild());
    }
}


template <typename T>
void BST<T>::inorder(Node<T>* node) const
{
    if (node != nullptr) {
        inorder(node->getLeftChild());
        std::cout << node->getVal() << " ";
        inorder(node->getRightChild());
    }
}

template <typename T>
void BST<T>::postorder(Node<T>* node) const
{
    if (node != nullptr) {
        postorder(node->getLeftChild());
        postorder(node->getRightChild());
        std::cout << node->getVal() << " ";
    }
}


























template <typename T>
bool BST<T>::isEmpty() const
{
    return (getRootData() == nullptr);
}

template <typename T>
int BST<T>::getHeight() const
{
    return getHeightHelper(root);
}

template <typename T>
int BST<T>::getNumberofNodes() const
{
    return getNumberOfNodesHelper(root);
}

template <typename T>
Node<T>* BST<T>::getRootData() const
{
    return root;
}

template <typename T>
void BST<T>::add(const T& val) {
    root = balancedAdd(root, new Node(val));
}

template <typename T>
void BST<T>::remove(const T& val) {
    root = removeHelper(root, val);
}

template <typename T>
void BST<T>::clear()
{
    destroyTree(root);
    root = nullptr;
}

template <typename T>
bool BST<T>::contains(const T& val) const
{
    Node<T>* node = findNode(root, val);
    if (node == nullptr) {
        return false;
    }
    return true;
}

template <typename T>
BST<T>::BST() : root{nullptr} {}

template <typename T>
BST<T>::BST(const T& val) : root{new Node(val)} {}

template <typename T>
BST<T>::BST(const T& val, const BST<T>* leftSubTree, const BST<T>* rightSubTree) 
{
    root = new Node(val, copyTree(leftSubTree->getRootData()), copyTree(rightSubTree->getRootData()));
}

template <typename T>
BST<T>::BST(const BST<T>& tree)
{
    //root = new Node(tree->getRootData(), copyTree(tree.getRightChild()), copyTree(tree.getLeftChild()));
    root = copyTree(tree.getRootData());
}

template <typename T>
BST<T>::~BST()
{
    destroyTree(root);
}

template <typename T>
void BST<T>::preorderTraverse() const
{
    preorder(root);
}

template <typename T>
void BST<T>::inorderTraverse() const
{
    inorder(root);
}

template <typename T>
void BST<T>::postorderTraverse() const
{
    postorder(root);
}

int main()
{
    BST<int>* tree = new BST<int>();
    tree->add(50);
    tree->add(25);
    tree->add(100);
    tree->add(10);
    tree->add(5);
    tree->add(16);
    tree->add(150);
    tree->add(125);
    tree->add(180);
    tree->add(114);
    tree->add(60);
    
    std::cout << tree->isEmpty() << "\n";
    std::cout << tree->getHeight() << "\n";
    std::cout << tree->getNumberofNodes() << "\n";
//    tree->clear();
    std::cout << tree->contains(16);
    //tree->remove(25);
    //tree->remove(25);
    //std::cout << tree->contains(11);
    //std::cout << tree->getMax(tree->getRootData())->getVal();
    //std::cout << std::endl;

    //tree->inorderTraverse();

}