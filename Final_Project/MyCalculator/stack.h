#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack;

template <class T>
ostream& operator<<(ostream&, const Stack<T>&);

template <class T>
class Node{
private:
    friend class Stack<T>;

    T m_val;
    Node * m_nextPtr;

public:
    Node()=default;
    Node(const T& val) :m_val(val) {}

    Node(const Node& rhs) = delete;
    Node& operator =(const Node& rhs) = delete;

    Node(T&& val) :m_val(std::move(val)) { }

    const T& value() const {
        return m_val;
    }

    Node* next() {
        return m_nextPtr;
    }
};


template <class T>
class Stack{
private:
    Node<T>* m_top=NULL;
public:
    Stack()=default;
    Stack(const Stack&) = delete;

    ~Stack();
    Stack& operator=(const Stack&) = delete;

    void clear();
    void push(const T& val);
    void push(T&& val);
    void pop();
    const T& top() {
        return m_top->m_val;
    }
    bool empty()const {
        return m_top == NULL;
    }

    friend ostream& operator<< <T>(ostream&, const Stack<T>&);
};

template <class T>
void Stack<T>::clear(){
    Node<T>* p = NULL;
    while (m_top != NULL) {
        p = m_top;
        m_top = m_top->m_nextPtr;
        delete p;
    }
}

template <class T>
void Stack<T>::push(const T& val){
    Node<T>* node = new Node<T>(val);
    node->m_nextPtr=m_top;
    m_top=node;
}

template <class T>
void Stack<T>::push(T&& val){
    Node<T>* node = new Node<T>(move(val));
    node->m_nextPtr = m_top;
    m_top = node;

}

template <class T>
void Stack<T>::pop(){
    Node<T>* p = m_top;
    m_top = m_top->m_nextPtr;
    delete p;
}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
ostream& operator<<(ostream& os, const Stack<T>& s) {
    Node<T>* p = s.m_top;
    while (p != NULL) {
        os << p->value() << " ";
        p = p->next();
    }
    return os;
}

#endif // STACK_H
