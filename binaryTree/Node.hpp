#ifndef NODE_HPP
#define NODE_HPP


template <typename T>
class Node
{
private:
    T m_data;
    Node<T>* leftChild;
    Node<T>* rightChild;
public:
    Node();
    Node(const T&);
    Node(const T&, Node<T>* left, Node<T>* right);
    void setData(const T&);
    T getData() const;
    bool isLeaf() const;
    Node<T>* getLeftChild() const;
    Node<T>* getRightChild() const;
    void setLeftChild(Node<T>*);
    void setRightChild(Node<T>*);
};

template <typename T>
Node<T>::Node() : m_data{}, leftChild{nullptr}, rightChild{nullptr} {}

template <typename T>
Node<T>::Node(const T& data) : m_data{data}, leftChild{nullptr}, rightChild{nullptr} {}

template <typename T>
Node<T>::Node(const T& data, Node<T>* left, Node<T>* right) : m_data{data}, leftChild{left}, rightChild{right} {} 

template <typename T>
void Node<T>::setData(const T& data) 
{
    m_data = data;
}

template <typename T>
T Node<T>::getData() const
{
    return m_data;
}

template <typename T>
bool Node<T>::isLeaf() const
{
    return (leftChild==nullptr && rightChild==nullptr);
}
template <typename T>
Node<T>* Node<T>::getLeftChild() const
{
    return leftChild;
}

template <typename T>
Node<T>* Node<T>::getRightChild() const
{
    return rightChild;
}
template <typename T>
void Node<T>::setLeftChild(Node<T>* node)
{
    leftChild = node;
}

template <typename T>
void Node<T>::setRightChild(Node<T>* node)
{
    rightChild = node;
}

#endif