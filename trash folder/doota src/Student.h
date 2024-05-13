#ifndef ABOL_STUDENT_H
#define ABOL_STUDENT_H

#include <fstream>
#include "string"
#include "vector"
#include "iostream"
#include "User.h"
#include "Assignment.h"
using namespace std;

class Student : public User {
    vector<string> classes;
public:
    Student();
    Student(string name, string username, string password, string phone_number, vector<string> classes);
    void displayMenu();
    bool authenticate(string username, string password);
private:
    void listClasses();
    vector<Assignment> getAssignmentsForStudent(string studentName);
    void assignments();
    void announcements();
};


#endif //ABOL_STUDENT_H
