#ifndef tree_h
#define tree_h

#include <iostream>

namespace treeException {
    class Invalid_input{};
    class Failure{};
    class TreeIsEmpty {};
    class TreeIsNotEmpty {};
}

using namespace treeException;
using namespace std;

//------------------------------------------------------------------------------
//                                  NODE CLASS
//------------------------------------------------------------------------------
template <class T>
class Node {
public:
    T data;
    int nodeHeight;

    Node* dad;
    Node* sonL;
    Node* sonR;

    Node(const T& data, Node<T>* dad);
    Node(Node<T>* dad);
};

template <class T>
Node<T>::Node(const T& data, Node<T>* dad): data(data), nodeHeight(1), dad(dad),
sonL(NULL), sonR(NULL) {}

template <class T>
Node<T>::Node(Node<T>* dad): data(), nodeHeight(1), dad(dad), sonL(NULL), sonR(NULL) {}

//------------------------------------------------------------------------------
//                                END NODE CLASS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                                  TREE CLASS
//------------------------------------------------------------------------------

template <class T>
class Tree {

private:

    Node<T> * root;
    int nodeNumber;

public:

// Constructor & Destructor

    Tree();
    Tree(Node<T> * root);
    ~Tree();
    void clean();

//  Tree traversal functions

    void inOrder(void (*f) (const T &));
    void postOrder(void (*f) (const T &));
    void preOrder(void (*f) (const T &));

//  Empty / Find functiuns

    bool empty();
    Node<T> * find(const T& data);

//  Getters

    int getNodeNumber() const;
    T getMax();
    T getMin();
    int getHeight() ;

//  Insert / Dell functions

    void insert(const T& data);
    void del(const T& data);

//	Tree to Tab & Tab to Tree

	void toTab(T tab[]);
	void toTree(int size, T src[]);

private:

//  Tree traversal functions Aux

    void inOrderAux(Node<T> * p, void (*f) (const T &));
    void preOrderAux(Node<T> * p, void (*f) (const T &));
    void postOrderAux(Node<T> * p, void (*f) (const T &));

//  Insert / Del functions Aux

    void insertAux(const T& data, Node<T> * p);
    void delAux(const T& data, Node<T> * p);
    void cleanAux(Node<T> * p);

//  Find function Aux

    Node<T> * findAux(const T& data, Node<T> * p);

//  Getters Aux

    T getMaxAux(Node<T> * p);
    T getMinAux(Node<T> * p);
    int getHeightAux(Node<T> * p) ;

//	Tree AVL Rotations

	void rightRotation(Node<T> * p);
	void leftRotation(Node<T> * p);
	void balanceTree(Node<T> * p);
	void balanceTreeAux(Node<T> * p);

//	Balance factor function

	int getNodeHeight(Node<T> * p);
	void updateHeight(Node<T> * p);

//	Tree to Tab & Tab to Tree Aux

	void toTabAux(T tab[], Node<T> * p, int* i);
	Node<T> * completeTree(int height, Node<T> * p);
	void delVertex(int* num, Node<T> * p);
	void insertTabToTree(Node<T> * p, int* num, T values[]);
	void updateHeightToTree(Node<T> * p);

public:
// 	BALANCE TEST FUNCTIONS

	bool treeBalanced(){
		return isBalanced(root);
	}
	int getNodeBalance(Node<T> * p) {
		int leftHeight = getHeightAux(p->sonL);
		int rightHeight = getHeightAux(p->sonR);
		return leftHeight - rightHeight ;
	}
	bool isBalanced(Node<T> * p){
		if(!p) return true;
		int nodeBalance = getNodeBalance(p);
		if(nodeBalance >= -1 && nodeBalance <= 1){
			return isBalanced(p->sonL)&&isBalanced(p->sonR);
		}
		return false;
	}


};


//                          CONSTRUCTOR/DESTRUCTOR
//------------------------------------------------------------------------------

template <class T>
Tree<T>::Tree() {
	root=NULL;
	nodeNumber = 0;
}

template <class T>
Tree<T>::Tree(Node<T>* root):root(root) {
	if(!root) {
		nodeNumber = 0;
	}
	else nodeNumber = 1;
}

template <class T>
Tree<T>::~Tree(){
	clean();
}

template <class T>
void Tree<T>::cleanAux(Node<T> * p) {
	if(!p) return;
	cleanAux(p->sonL);
	cleanAux(p->sonR);
	delete p;
	return;
}

template <class T>
void Tree<T>::clean() {
	cleanAux(root);
	nodeNumber = 0;
	root = NULL;
	return;
}

//                         FIND/EMPTY FUNCTION
//------------------------------------------------------------------------------

template <class T>
Node<T> * Tree<T>::findAux(const T& data, Node<T> * p){
    if(!p) return NULL;
    if (p->data == data) return p;

    if(data > p->data) {
        return findAux(data, p->sonR);
    }
    if(data < p->data){
        return findAux(data, p->sonL);
    }
    return NULL;
}

template <class T>
Node<T> * Tree<T>::find(const T& data) {
    return findAux(data, root);
}

template <class T>
bool Tree<T>::empty(){
    if(getNodeNumber() == 0) return true;
    return false;
}

//                              INSERT FUNCTION
//------------------------------------------------------------------------------

template <class T>
void Tree<T>::insertAux(const T& data, Node<T> * p) {
    if(data > p->data) {
        if(!p->sonR) {
            p->sonR = new Node<T>(data, p);
            if(!p->sonR){
            	throw bad_alloc();
            }
            nodeNumber++;
            balanceTree(p);
            return;
        }
        insertAux(data, p->sonR);
    }
    if(data < p->data){
        if(!p->sonL) {
            p->sonL = new Node<T>(data, p);
            if(!p->sonL){
            	throw bad_alloc();
            }
            nodeNumber++;
            balanceTree(p);
            return;
        }
        insertAux(data, p->sonL);
    }
    return;

}

template <class T>
void Tree<T>::insert(const T& data) {
    if(!root) {
        root=new Node<T>(data, NULL);
        if(!root) throw bad_alloc();
        nodeNumber++;
        return;
    }
    if(find(data)){
    	throw treeException::Failure();
    	return;
    }
    insertAux(data, root);
    return;
}

//                              DEL FUNCTION
//------------------------------------------------------------------------------

template <class T>
void Tree<T>::del(const T& data) {
	if(!find(data)){
		throw treeException::Failure();
		return;
	}
	if(nodeNumber == 1) {
		Node<T> * tmp= root;
		root= NULL;
		delete tmp;
		nodeNumber = 0;
		return;
	}
	delAux(data, root);
	return;
}

template <class T>
void Tree<T>::delAux(const T& data, Node<T> * p) {
	if(!p) return;
	if(data > p->data) {
		delAux(data, p->sonR);
	}
	if(data < p->data) {
		delAux(data, p->sonL);
	}

	if(data == p->data) {
		if(!p->sonL && !p->sonR) {
			Node<T> * father = p->dad;
			(father->sonL == p)? father->sonL = NULL : father->sonR = NULL;
			delete p;
			nodeNumber--;
			balanceTree(father);
			return;
		}
		if(!p->sonL || !p->sonR) {

			Node<T> * father = p->dad;
			if(!father) {
				root = (p->sonR)? p->sonR : p->sonL;
				root->dad = NULL;
				delete p;
				nodeNumber--;
				return;
			}
			if(father->sonL == p) {
				(p->sonR)? father->sonL = p->sonR : father->sonL = p->sonL;
				(p->sonR)? p->sonR->dad = father : p->sonL->dad = father;
			}
			if(father->sonR == p) {
				(p->sonR)? father->sonR = p->sonR : father->sonR = p->sonL;
				(p->sonR)? p->sonR->dad = father : p->sonL->dad = father;
			}
			delete p;
			nodeNumber--;
			balanceTree(father);
			return;
		}
		if(p->sonL && p->sonR) {
			p->data = getMinAux(p->sonR);
			delAux(p->data, p->sonR);
		}
	}
}

//                          TREE TRAVERSAL FUNCTION
//------------------------------------------------------------------------------


// preOrder
template <class T>
void Tree<T>::preOrderAux(Node<T> * p,void (*f) (const T &)) {
    if(!p) return;
    f(p->data);
    preOrderAux(p->sonL,f);
    preOrderAux(p->sonR,f);
}

template <class T>
void Tree<T>::preOrder(void (*f) (const T &)){
    preOrderAux(root,f);
    return;
}

// inOrder
template <class T>
void Tree<T>::inOrderAux(Node<T> * p,void (*f) (const T &)) {
    if(!p) return;
    inOrderAux(p->sonL,f);
    f(p->data);
    inOrderAux(p->sonR,f);
}

template <class T>
void Tree<T>::inOrder(void (*f) (const T &)){
    inOrderAux(root,f);
    return;
}

// postOrder
template <class T>
void Tree<T>::postOrderAux(Node<T> * p,void (*f) (const T &)){
    if(!p) return;
    postOrderAux(p->sonL, f);
    postOrderAux(p->sonR, f);
    f(p->data);
}

template <class T>
void Tree<T>::postOrder(void (*f) (const T &)){
    postOrderAux(root,f);
    return;
}

//                            GETTER FUNCTION
//------------------------------------------------------------------------------

template <class T>
int Tree<T>::getNodeNumber() const {
    return nodeNumber;
}

//	getMax
template <class T>
T Tree<T>::getMax() {
    if(empty()) {
        throw treeException::TreeIsEmpty();
    }
    return getMaxAux(root);
}

template <class T>
T Tree<T>::getMaxAux(Node<T> * p) {
    if(!p->sonR) {
        return p->data;
    }
    return getMaxAux(p->sonR);
}

//	getMin
template <class T>
T Tree<T>::getMin() {
    if(empty()) {
        throw treeException::TreeIsEmpty();
    }
    return getMinAux(root);
}

template <class T>
T Tree<T>::getMinAux(Node<T> * p)  {
    if(!p->sonL) {
        return p->data;
    }
    return getMinAux(p->sonL);
}

//	getHeight

template <class T>
int Tree<T>::getHeight() {
	return getHeightAux(root);
}

template <class T>
int Tree<T>::getHeightAux(Node<T> * p) {
	if(!p) return 0;
	int heightLeft = getHeightAux(p->sonL);
	int heightRight = getHeightAux(p->sonR);
	int max = heightRight;
	if(heightLeft >= heightRight) max = heightLeft;
	return max + 1;
}

//                        TREE AVL ROTATION FUNCTION
//------------------------------------------------------------------------------

template <class T>
void Tree<T>::leftRotation(Node<T> * p) {
	if(!p) return;
	Node<T> * a = p;
	Node<T> * b = p->sonR;
	// new fathers
	if(a->dad) {
		if(a->dad->sonR == a) a->dad->sonR = b;
		else a->dad->sonL = b;
	}
	b->dad = a->dad;

	if(b->sonL) b->sonL->dad = a;
	a->sonR = b->sonL;

	a->dad = b;
	b->sonL = a;
	if(a == root) root = b;
	a->nodeHeight = getNodeHeight(a);
	b->nodeHeight = getNodeHeight(b);
	updateHeight(p);
	return;
}

template <class T>
void Tree<T>::rightRotation(Node<T> * p) {
	if(!p) return;
	Node<T> * b = p;
	Node<T> * a = p->sonL;
	// new fathers
	if(b->dad) {
		if(b->dad->sonR == b) b->dad->sonR = a;
		else b->dad->sonL = a;
	}
	a->dad = b->dad;

	if(a->sonR) a->sonR->dad = b;
	b->sonL = a->sonR;

	b->dad = a;
	a->sonR = b;
	if(b == root) root = a;
	b->nodeHeight = getNodeHeight(b);
	a->nodeHeight = getNodeHeight(a);
	updateHeight(p);
	return;
}

template <class T>
void Tree<T>::balanceTree(Node<T> * p){
	updateHeight(p);
	balanceTreeAux(p);
}

template <class T>
void Tree<T>::balanceTreeAux(Node<T> * p) {
	if(!p) return;
	//int rootBalance = getNodeBalance(p);
	int rootBalance = getNodeHeight(p->sonL) - getNodeHeight(p->sonR);
	// case LL & LR
	if(rootBalance == 2) {
		//int sonLBalance = getNodeBalance(p->sonL);
		int sonLBalance = getNodeHeight(p->sonL->sonL) - getNodeHeight(p->sonL->sonR);
		// case LL
		if(sonLBalance >= 0) {
			rightRotation(p);
		}
		// case LR
		if(sonLBalance == -1) {
			leftRotation(p->sonL);
			rightRotation(p);
		}
	}

	// case RR & RL
	if(rootBalance == -2) {
		//int sonRBalance = getNodeBalance(p->sonR);
		int sonRBalance = getNodeHeight(p->sonR->sonL) - getNodeHeight(p->sonR->sonR);
		// case RR
		if(sonRBalance <= 0){
			leftRotation(p);
		}
		// case RL
		if(sonRBalance == 1) {
			rightRotation(p->sonR);
			leftRotation(p);
		}
	}
	balanceTree(p->dad);
}

//                        BALANCE FACTOR FUNCTION
//------------------------------------------------------------------------------

template <class T>
int Tree<T>::getNodeHeight(Node<T> * p) {
	if(!p) return 0;
	int heightL = 0, heightR = 0;
	if(p->sonL) heightL = p->sonL->nodeHeight;
	if(p->sonR) heightR = p->sonR->nodeHeight;
	int max = heightR;
	if(heightL > heightR) max = heightL;
	return max + 1;
}

template <class T>
void Tree<T>::updateHeight(Node<T> * p) {
	if(!p) return;
	p->nodeHeight = getNodeHeight(p) ;
	updateHeight(p->dad);
}

//                        TO TAB & TO TREE FUNCTION
//------------------------------------------------------------------------------

//	Tree To Tab
template <class T>
void Tree<T>::toTabAux(T values[], Node<T> * p, int* i){
	if(!p) return;
	toTabAux(values, p->sonL, i);
	values[(*i)++] = p->data;
	toTabAux(values, p->sonR, i);
}

template <class T>
void Tree<T>::toTab(T values[]) {
	int i = 0;
	toTabAux(values, root, &i);
	return;
}

//	Tab To Tree
template <class T>
Node<T> * Tree<T>::completeTree(int height, Node<T> * p) {
	if(!height) return NULL;
	Node<T> * d = new Node<T>(p);
	d->sonL = completeTree(height-1, d);
	d->sonR = completeTree(height-1, d);
	return d;
}

template <class T>
void Tree<T>::delVertex(int* num, Node<T> * p) {
	if(!p) return;
	Node<T> * sonL = p->sonL;
	Node<T> * sonR = p->sonR;
	delVertex(num, sonR);
	if((*num > 0) && !p->sonL && !p->sonR) {
		if(p->dad){
			if(p->dad->sonL == p)
				p->dad->sonL = NULL;
			else
				p->dad->sonR = NULL;
		}
		delete p;
		(*num)--;
	}
	delVertex(num, sonL);
}

template <class T>
void Tree<T>::insertTabToTree(Node<T> * p, int* num, T values[]) {
	if(!p) return;
	insertTabToTree(p->sonL, num, values);
	p->data = values[(*num)++];
	insertTabToTree(p->sonR, num, values);
}

template <class T>
void Tree<T>::updateHeightToTree(Node<T> * p){
	if(!p) return;
	updateHeightToTree(p->sonL);
	updateHeightToTree(p->sonR);
	p->nodeHeight = getNodeHeight(p);
}

template <class T>
void Tree<T>::toTree(int size, T values[]) {
	if(!empty()){
		throw treeException::TreeIsNotEmpty();
		return;
	}
	// calcul of the height
	int height = 1, num = 2;
	while(size > num-1){
		num*=2;
		height++;
	}
	// creating the tree ==> completeTree
	root = new Node<T> (NULL);
	root->sonL = completeTree(height-1, root);
	root->sonR = completeTree(height-1, root);

	// delete vertexes which dont need ==> delVertex
	int numToDelete = num-1 - size;
	delVertex(&numToDelete, root);

	// updating height of new tree
	updateHeightToTree(root);

	// insert values in the tree ==> insertTabToTree
	int i=0;
	insertTabToTree(root, &i, values);
	nodeNumber = size;
	return;
}

//------------------------------------------------------------------------------
//                            END TREE CLASS
//------------------------------------------------------------------------------

#endif /* tree_h */
