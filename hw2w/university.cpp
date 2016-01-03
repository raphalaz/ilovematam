#include "university.h"

void University::addStudent(int studentID, int average) {
    if (studentID < 0 || average < 0 || average > MAX_GRADE) {
        throw UniversityException::InvalidInput();
    }
    Student student(studentID, average);
    if (students.find(student) != NULL) {
        throw UniversityException::Failure();
    }
    students.insert(student);
}

void University::getFaculty(int studentID, int* faculty) const {
    if (studentID < 0 || faculty == NULL) {
        throw UniversityException::InvalidInput();
    }
    int studyGroup;
    try {
        studyGroup = studentAssignement.getValue(studentID);
    } catch (ListException::ElementNotFound&) {
        throw UniversityException::Failure();
    }
    *faculty = faculties.find(studyGroup);
}

void University::unifyFacultiesByStudents(int studentID1, int studentID2) {
    if (studentID1 < 0 || studentID2 < 0) {
        throw UniversityException::InvalidInput();
    }
    int studyGroup1, studyGroup2;
    try {
        studyGroup1 = studentAssignement.getValue(studentID1);
        studyGroup2 = studentAssignement.getValue(studentID2);
    } catch (ListException::ElementNotFound&) {
        throw UniversityException::Failure();
    }
    try {
        faculties.unionWith(studyGroup1, studyGroup2);
    } catch (UFindException::Failure&) {
        throw UniversityException::Failure();
    }
}

void University::updateStudyGroup(int studyGroup, int factor) {
    if (studyGroup < 0 || studyGroup >= size || factor < 1) {
        throw UniversityException::InvalidInput();
    }
    Student* array = new Student[students.getNodeNumber()];
    initializeHistogram();
    
    
}

int University::getNumOfStudentsInRange(int fromAvg, int toAvg, int* num) const {
    if (fromAvg < 0 || fromAvg > MAX_GRADE || toAvg < 0 || toAvg > MAX_GRADE ||
        fromAvg > toAvg) {
        throw UniversityException::InvalidInput();
    }
    return gradeHistogram[fromAvg + 1] - gradeHistogram[toAvg];
}

void University::initializeHistogram() {
    for (int i = 0; i < MAX_GRADE; i++) {
        gradeHistogram[i] = 0;
    }
}