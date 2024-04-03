#ifndef ABOL_TEACHER_H
#define ABOL_TEACHER_H

#include <vector>
#include "User.h"
#include "Assignment.h"
#include "string"
#include "Class.h"
using namespace std;

class Teacher : public User {
    vector<Class> classes;
public:
    Teacher();
    Teacher(string teacherName);
    Teacher(string name, string username, string password, string phone_number, vector<Class> classes);
    void displayMenu();
    bool authenticate(string username, string password);

private:

    void listClasses();
    vector<string> split(const string& str, char delimiter);
    vector<Class> getClassesForTeacher(string teacherUsername);
    void editClass();
    bool isClassExist(string className);
    Class getClassByName(string className);
    void updateClassDetails(Class c);
    bool updateClass(string className, string newClassName, string newSubject, string newGradeLevel);
    void saveClass(Class c);
    void createClass();
    void createAssignment();
    void saveAssignment(Assignment a);
    void messaging();
    void addClassComment(string className, string message);
    void gradeAssignments();
    void saveGrade(int assignmentId, int grade);
    vector<Assignment> getAllAssignments(string className);
};

#endif //ABOL_TEACHER_H
