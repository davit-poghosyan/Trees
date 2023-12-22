#include <iostream>

template <typename T>
class Node
{
private:
    T m_val;
    Node<T>* m_left;
    Node<T>* m_right;
public:
    Node();
    Node(const T&);
    Node(const T&, Node<T>*, Node<T>*);
    ~Node();

    void setVal(const T&);
    void setLeftChild(Node<T>*);
    void setRightChild(Node<T>*);
    
    T getVal() const;
    Node<T>* getLeftChild() const;
    Node<T>* getRightChild() const;

    bool isLeaf() const;
};

template <typename T>
Node<T>::Node() : m_val{}, m_left{nullptr}, m_right{nullptr} {}

template <typename T>
Node<T>::Node(const T& val) : m_val{val}, m_left{nullptr}, m_right{nullptr} {}

template <typename T>
Node<T>::Node(const T& val, Node<T>* left, Node<T>* right) : m_val{val}, m_left{left}, m_right{right} {}

template <typename T>
Node<T>::~Node() {}

template <typename T>
void Node<T>::setVal(const T& val) 
{
    m_val = val;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>* node)
{
    m_left = node;
}

template <typename T>
void Node<T>::setRightChild(Node<T>* node) 
{
    m_right = node;
}

template <typename T>
T Node<T>::getVal() const
{
    return m_val;
}
template <typename T>
Node<T>* Node<T>::getLeftChild() const
{
    return m_left;
}
template <typename T>
Node<T>* Node<T>::getRightChild() const
{
    return m_right;
}

template <typename T>
bool Node<T>::isLeaf() const
{
    return (m_left == nullptr && m_right == nullptr);
}