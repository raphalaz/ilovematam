/*
 * UnionFind.h
 *
 *  Created on: 28 déc. 2015
 *      Author: sathouel
 */



#ifndef UNIONFIND_H_
#define UNIONFIND_H_

typedef int S;

#include <iostream>
#include "UFindException.h"
using namespace UFindException;
using namespace std;

#define IS_ROOT -1

/*
 * Remarque : atention a definir le constructeur par defaut de la class Student
 * afin de pouvoir "initialiser" toute les case du tab bestStudent et de ce fait
 * nous pourrons savoir si aucun eleves n'appartien a une faculté donne
 * on en a besoin dans la fonction GetSmartestStudent
 */
//------------------------------------------------------------------------------
//                           UNION FIND CLASS
//------------------------------------------------------------------------------

template <class S>
class UFind {

private:
	int domainSize;
	S* bestStudents;
	int* sizes;
	int* fathers;
	int* roots;

public:

// Constructor / Destructor

	UFind(int domain);
	~UFind();

// Union / Find

	int find(int member) const;
	void unionWith(int setName1, int setName2);

//	Set / Get bestStudent

	void setBestStudent(int setName, S newBestStudent);
	S getBestStudent(int setName);

private :

// Find AUX

	int findRoot(int member) const;
	void findChange(int newFather, int start) const;

public	:

// DEBUG

	void printAll() {
		cout << "ROOT ; SETNAME ; SIZE " << endl;
		for(int i = 0; i< domainSize ; i++){
			cout << fathers[i] <<" ; "  << roots[i]<< " ; " << sizes[i]  << endl;
		}
	}
};

//                         CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------------------------------------

template <class S>
UFind<S>::UFind(int domain): domainSize(domain) {
	if(domain < 2) throw Invalid_size();

	fathers = new int[domain];
	roots = new int[domain];
	sizes = new int[domain];
	bestStudents = new S[domain];

	for(int i = 0; i<domain; i++) {
		fathers[i]= -1;
		roots[i] = i;
		sizes[i] = 1;
	}

}

template <class S>
UFind<S>::~UFind() {
	delete[] fathers;
	delete[] roots;
	delete[] sizes;
	delete[] bestStudents;
}


//                         UNION / FIND
//------------------------------------------------------------------------------

template <class S>
int UFind<S>::findRoot(int member) const {
	if(member < 0 || member >= domainSize){
		throw UFindException::Invalid_input();
	}
	if(fathers[member] == IS_ROOT) return member;
	return findRoot(fathers[member]);
}

template <class S>
void UFind<S>::findChange(int newFather, int start) const {
	if(start == newFather || fathers[start] == newFather) return;
	int nextStart = fathers[start];
	fathers[start] = newFather;
	findChange(newFather, nextStart);
	return;
}

template <class S>
int UFind<S>::find(int member) const {
	if(member < 0 || member >= domainSize){
		throw UFindException::Invalid_input();
	}
	int result = findRoot(member);
	findChange(result, member);
	return roots[result];
}

template <class S>
void UFind<S>::unionWith(int setName1, int setName2){
	if(setName1 >= domainSize || setName1 < 0 || setName2 >= domainSize ||
			setName2 < 0 || setName1 == setName2){
		throw UFindException::Invalid_input();
	}
	int father1 = roots[setName1], father2 = roots[setName2];
	bool test = (roots[father1] != setName1 ) || (roots[father2] != setName2 );
	if(fathers[father1] != IS_ROOT || test ||
			fathers[father2] != IS_ROOT || father1 == father2 ){
		throw UFindException::Failure();
	}
	int newFather = father1;
	int oldFather = father2;
	if(sizes[father2] > sizes[father1]){
		newFather = father2;
		oldFather = father1;
	}

	fathers[oldFather] = newFather;
	sizes[newFather]+= sizes[oldFather];
	roots[setName1] = newFather;
	roots[newFather] = setName1;
	setBestStudent(setName1, bestStudents[setName2]);
	return;
}

//                        SET / GET BEST STUDENT
//------------------------------------------------------------------------------

template <class S>
void UFind<S>::setBestStudent(int setName, S newBestStudent) {
	int dad = roots[setName];
	if(fathers[dad] != IS_ROOT || roots[dad]!= setName ){
		throw UFindException::Failure();
	}
	if(bestStudents[setName] >= newBestStudent) return;
	bestStudents[setName] = newBestStudent;
}

template <class S>
S UFind<S>::getBestStudent(int setName) {
	int dad = roots[setName];
	if(fathers[dad] != IS_ROOT || roots[dad]!= setName ){
		throw UFindException::Failure();
	}
	return bestStudents[setName];
}

//------------------------------------------------------------------------------
//                           UNION FIND END
//------------------------------------------------------------------------------

#endif /* UNIONFIND_H_ */