
template <typename T>
BinaryTree<T>::BinaryTree() : root{nullptr} {}

template <typename T>
BinaryTree<T>::BinaryTree(const T& val)  : root{new Node<T>(val)} {}

template <typename T>
BinaryTree<T>::BinaryTree(const T& data, const BinaryTree<T>* leftTree, const BinaryTree<T>* rightTree)
{
    root = new BinaryTree<T>(data, copyTree(leftTree->root), copyTree(rightTree->root));
}
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree) 
{
    root = copyTree(tree.root);
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    destroyTree(root);
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& src)
{
    if (this == &src)
    {
        return *this;
    }

    delete root;
    root = copyTree(src.root);
}

template <typename T>
bool BinaryTree<T>::isEmpty() const
{
    return root==nullptr;
}

template <typename T>
int BinaryTree<T>::getHeight() const 
{
    return getHeightHelper(root);
}

template <typename T>
int BinaryTree<T>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(root);
}

template <typename T>
T BinaryTree<T>::getRootData() const
{
    return root->getData();
}

template <typename T>
void BinaryTree<T>::setRootData(const T& val)
{
    root->setData(val);
}

template <typename T>
void BinaryTree<T>::add(const T& val) 
{
    Node<T>* node = new Node<T>(val);
    root = balancedAdd(root, node);
}

template <typename T>
void BinaryTree<T>::remove(const T& val)
{
    root = removeValue(root, val);
}

template <typename T>
void BinaryTree<T>::clear()
{
    destroyTree(root);
}

template <typename T>
bool BinaryTree<T>::contains(const T& val) const
{
    Node<T>* node = new Node(val);
    Node<T>* contain = findNode(root, val);
    return node->getData() == contain->getData();
}

template <typename T>
void BinaryTree<T>::print() const
{
    inorderHelper(root);
    
}

template <typename T>
void BinaryTree<T>::preorder() const
{
    preorderHelper(root);
} 

template <typename T>
void BinaryTree<T>::inorder() const
{
    inorderHelper(root);
}

template <typename T>
void BinaryTree<T>::postorder() const
{
    postorderHelper(root);
}




template <typename T>
int BinaryTree<T>::getHeightHelper(Node<T>* tree) const
{
    if (tree == nullptr) {
        return 0;
    }
    else{
        return 1 + std::max(getHeightHelper(tree->getLeftChild()), getHeightHelper(tree->getRightChild()));
    }
}

template <typename T>
int BinaryTree<T>::getNumberOfNodesHelper(Node<T>* tree) const
{
     if (tree == nullptr) {
        return 0;
    } else {
        int leftCount = getNumberOfNodesHelper(tree->getLeftChild());
        int rightCount = getNumberOfNodesHelper(tree->getRightChild());

        return 1 + leftCount + rightCount;
    }
}


template <typename T>
void BinaryTree<T>::destroyTree(Node<T>* tree) 
{
    if(tree!=nullptr)
    {
        destroyTree(tree->getLeftChild());
        destroyTree(tree->getRightChild());
        delete tree;

    }
    
}

template <typename T>
Node<T>* BinaryTree<T>::balancedAdd(Node<T>* tree, Node<T>* newNode)
{
    if (tree == nullptr)
    {
        return newNode;
    }
    else { 
        Node<T>* leftNode = tree->getLeftChild();
        Node<T>* rightNode = tree->getRightChild();
        if (getHeightHelper(leftNode) > getHeightHelper(rightNode)) {
            rightNode = balancedAdd(rightNode, newNode);
            tree->setRightChild(rightNode);
        }
        else {
            leftNode = balancedAdd(leftNode, newNode);
            tree->setLeftChild(leftNode);

        }
        return tree;
    }
}

template <typename T>
Node<T>* BinaryTree<T>::removeValue(Node<T>* node, const T target)
{
    if (node == nullptr) {
        return nullptr;
    }
    
    if (node->getData() == target) {
        if (node->isLeaf()) {
            delete node;
            return nullptr;
        }
        
        else if (node->getLeftChild() == nullptr && node->getRightChild() != nullptr) {
            Node<T>* rightChild = node->getRightChild();
            delete node;
            return rightChild;
        }
        
        else if (node->getRightChild() == nullptr && node->getLeftChild()  != nullptr) {
            Node<T>* leftChild = node->getLeftChild();
            delete node;
            return leftChild;
        }
        
        else {
           /* Node<T>* minNode = node;
            while (!minNode->isLeaf()) {
                minNode = minNode->getLeftChild();
            }
            std::cout << minNode->getLeftChild() << std::endl;
            node->setData(minNode->getData());
            delete minNode;
            minNode = nullptr;
            return node;
        */
        
        
        Node<T>* minNode = node;
        while (!minNode->getLeftChild()->isLeaf()) {
            minNode = minNode->getLeftChild();
        }
        node->setData(minNode->getLeftChild()->getData());
        minNode->setLeftChild(removeValue(minNode->getLeftChild(), minNode->getLeftChild()->getData()));
        return node;
        }
    }
    
    
    node->setLeftChild(removeValue(node->getLeftChild(), target));
    node->setRightChild(removeValue(node->getRightChild(), target));
 
    
    
    return node;
}


template <typename T>
Node<T>* BinaryTree<T>::findNode(Node<T>* node, const T& target) const
{
    if (node == nullptr) {
        return nullptr;
    }
    if (node->getData() == target) {
        return node;
    }
    
    Node<T>* foundNode = findNode(node->getLeftChild(), target);
    if (foundNode == nullptr) {
        foundNode = findNode(node->getRightChild(), target);
    }

    return foundNode;    

}

// veradradznuma funkciayi meji haytararac popxakan??????????????????????????????????????????????????????????????
template <typename T>
Node<T>* BinaryTree<T>::copyTree(const Node<T>* tree) const
{
    Node<T>* node = nullptr;
    if(tree!=nullptr) {
        node = new Node<T>(tree->getData());
        node->setLeftChild(copyTree(tree->getLeftChild()));
        node->setRightChild(copyTree(tree->getRightChild()));
    }
    return node;
}



template <typename T> 
void BinaryTree<T>::preorderHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return;
    }
    std::cout << node->getData() << "  ";
    preorderHelper(node->getLeftChild());
    preorderHelper(node->getRightChild());
 }

template <typename T>
void BinaryTree<T>::inorderHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return;
    }
    inorderHelper(node->getLeftChild());
    std::cout << node->getData() << " ";
    inorderHelper(node->getRightChild());
}

template <typename T>
void BinaryTree<T>::postorderHelper(Node<T>* node) const
{
    if (node == nullptr) {
        return;
    }
    postorderHelper(node->getLeftChild());
    postorderHelper(node->getRightChild());
    std::cout << node->getData() << " ";
}
