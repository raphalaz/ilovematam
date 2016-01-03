#ifndef list_h
#define list_h

#include <exception>
#include <cstdlib>

using namespace std;

//------------------------------------------------------------------------------
//                                  EXCEPTIONS
//------------------------------------------------------------------------------

namespace ListException {
    class ElementNotFound : public exception {};
}

//------------------------------------------------------------------------------
//                                  NODE CLASS
//------------------------------------------------------------------------------

template<class T>
class NodeL {
    
    T data;
    NodeL<T>* next;
    
public:
    
    //  Constructors
    
    NodeL(const T& data, NodeL* next = NULL);
    NodeL(const NodeL& node);
    
    //  Operators
    
    NodeL<T>& operator=(const NodeL& node);
    bool operator==(const NodeL& node);
    bool operator!=(const NodeL& node);
    
    // Get/Set functions
    
    NodeL<T>* getNext() const;
    T& getData();
    void setNext(NodeL* next);
    void setData(const T& data);
};

template<class T>
NodeL<T>::NodeL(const T& data, NodeL<T>* next) :
data(data), next(next) {}

template<class T>
NodeL<T>::NodeL(const NodeL<T>& node) :
data(node.data), next(node.next) {}

template<class T>
NodeL<T>& NodeL<T>::operator=(const NodeL<T>& node) {
    data = node.data;
    next = node.next;
    return *this;
}

template<class T>
bool NodeL<T>::operator==(const NodeL<T>& node) {
    return (data == node.data && next == node.next);
}

template<class T>
bool NodeL<T>::operator!=(const NodeL<T>& node) {
    return !(*this == node);
}

template<class T>
NodeL<T>* NodeL<T>::getNext() const {
    return next;
}

template<class T>
T& NodeL<T>::getData() {
    return data;
}

template<class T>
void NodeL<T>::setNext(NodeL<T>* next) {
    this->next = next;
}

template<class T>
void NodeL<T>::setData(const T& data) {
    this->data = data;
}

//------------------------------------------------------------------------------
//                               END OF NODE CLASS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                                  LIST CLASS
//------------------------------------------------------------------------------

template<class T>
class List {
    
    NodeL<T>* head;
    NodeL<T>* tail;
    int size;
    
public:
    
    // Constructors/Destructors
    
    List();
    ~List();
    
    // Handling functions
    
    void insertHead(const T& data);
    void insertTail(const T& data);
    NodeL<T>* find(const T& data);
    void remove(const T& data);
    
    // Get functions
    
    NodeL<T>* getHead() const;
    NodeL<T>* getTail() const;
    int getSize() const;
    
};

template<class T>
List<T>::List() :
head(NULL), tail(NULL), size(0) {}

template<class T>
List<T>::~List() {
    while (head != NULL) {
        remove(head->getData());
    }
}

template<class T>
void List<T>::insertHead(const T& data) {
    NodeL<T>* newNode = new NodeL<T>(data, head);
    head = newNode;
    size++;
}

template<class T>
void List<T>::insertTail(const T& data) {
    NodeL<T>* newNode = new NodeL<T>(data);
    if (head == NULL) {
        head = newNode, tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;
}

template<class T>
NodeL<T>* List<T>::find(const T& data) {
    if (head == NULL) {
        throw ListException::ElementNotFound();
    }
    NodeL<T>* iter = head;
    while (iter != NULL) {
        if (iter->getData() == data) {
            return iter;
        }
        iter = iter->getNext();
    }
    throw ListException::ElementNotFound();
}

template<class T>
void List<T>::remove(const T& data) {
    NodeL<T>* node = find(data);
    if (head == node) {
        head = head->getNext();
    } else {
        NodeL<T>* prev = head;
        while (prev->getNext() != node) {
            prev = prev->getNext();
        }
        prev->setNext(node->getNext());
        if (tail == node) {
            tail = prev;
        }
    }
    delete(node);
    size--;
}

template<class T>
NodeL<T>* List<T>::getHead() const {
    return head;
}

template<class T>
NodeL<T>* List<T>::getTail() const {
    return tail;
}

template<class T>
int List<T>::getSize() const {
    return size;
}


#endif /* list_h */
