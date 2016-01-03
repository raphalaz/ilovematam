/*
 * Student.h
 *
 *  Created on: 28 déc. 2015
 *      Author: sathouel
 */

#ifndef STUDENT_H_
#define STUDENT_H_

//------------------------------------------------------------------------------
//                           STUDENT EXCEPTION
//------------------------------------------------------------------------------

namespace StudentException {
    class Invalid_input{ };
    class Failure{ };
    class Invalid_size{};
}

#include <iostream>
using namespace std;
//------------------------------------------------------------------------------
//                           STUDENT CLASS
//------------------------------------------------------------------------------

class Student{
private :

	int studentID;
	int average;
	int studyGroup;

public :
	Student(int def): studentID(-1), average(-1), studyGroup(-1){}
	Student(int ID, int average):studentID(ID), average(average), studyGroup(-1){
		if(ID < 0 || average < 0 || average > 100) throw StudentException::Invalid_input();
	}

	int getID(){
		return studentID;
	}
	int getAverage(){
		return average;
	}
	void setAverage(int average){
		if(average > 100 || average < 0) throw StudentException::Invalid_input();
		this->average = average;
	}
	int getStudyGroup(){
		return studyGroup;
	}
	void setStudyGroup(int studyGroup){
		if(studyGroup < 0) throw StudentException::Invalid_input();
		this->studyGroup = studyGroup;
	}

	friend bool operator>=(Student& s1, Student& s2) {
		if(s1.average == s2.average) return s1.studentID >= s2.studentID;
		return s1.average > s2.average;
	}
	friend bool operator<(Student& s1, Student& s2) {
		return !(s1 >= s2);
	}
	friend bool operator<=(Student& s1, Student& s2) {
		return (s1 < s2) || (s1.average == s2.average);
	}
	friend bool operator>(Student& s1, Student& s2) {
		return !(s1 <= s2);
	}

	void printAll() {
		cout << "ID : " << studentID << " |average : " << average << " |studyGroup : " << studyGroup << endl;
	}
};

#endif /* STUDENT_H_ */
