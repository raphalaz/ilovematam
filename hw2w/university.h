#ifndef university_hpp
#define university_hpp

#include <exception>
#include "hashTable.h"
#include "tree.h"
#include "UnionFind.h"
#include "Student.h"

namespace UniversityException {
    class InvalidInput : public exception {};
    class Failure : public exception {};
}

class University {
    
    static const int MAX_GRADE = 100;
    
    int size;
    UFind<Student> faculties;
    HashTable studentAssignement;
    Tree<Student> students;
    int* gradeHistogram;
    
public:
    
    // Constructors
    
    University(int size); // S
    ~University(); // S
    
    // Handling functions
    
    void addStudent(int studentID, int average); // R
    void assignStudent(int studentID, int studyGroup); // S
    void joinFaculties(int studyGroup1, int studyGroup2); // S
    void getFaculty(int studentID, int* faculty) const; // R
    void unifyFacultiesByStudents(int studentID1, int studentID2); // R
    void updateStudyGroup(int studyGroup, int factor); // R
    void getSmartestStudent(int facultyID, int* student) const; // S
    int getNumOfStudentsInRange(int fromAvg, int toAvg, int* num) const; // R
    
private:
    
    void initializeHistogram();
};

#endif /* university_hpp */