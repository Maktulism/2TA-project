
#ifndef BASE_H
#define BASE_H
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class User {
protected:
    std::string username;
    std::string password;
public:
    User(const std::string& username, const std::string& password);
    virtual ~User();
    virtual void displayMenu() = 0;
    std::string getUsername() const;
};

class Admin : public User {
public:
    Admin(const std::string& username, const std::string& password);
    void displayMenu() override;
    void createInstructor();
    void manageInstructors();
    void manageClasses();
    void createStudent();
    void manageStudents();

    void viewAllInstructors();

    void updateInstructorDetails();

    void deleteInstructor();

    void updateClassDetails();

    void deleteClass();

    void createNewClass();

    void viewAllClasses();

    void viewAllStudents();

    void updateStudentDetails();

    void deleteStudent();
};

class Instructor : public User {
public:
    Instructor(const std::string& username, const std::string& password);
    void displayMenu() override;
    void manageClasses();
    void createAssignment();
    void manageAnnouncements();
    void gradeStudents();

    void updateClassDetails();

    void deleteClass();

    void viewAllClasses();

    void viewAllAnnouncements();

    void createAnnouncement();

    void deleteAnnouncement();

    void gradeStudentsForAssignment(const std::string &className, const std::string &assignmentName);
};

class Student : public User {
public:
    Student(const std::string& username, const std::string& password);
    void displayMenu() override;
    void viewClasses();
    void viewAssignments();
    void viewAnnouncements();
};

class Class {
private:
    std::string className;
    int capacity;
    std::vector<std::string> students;
    std::string instructor;
    std::vector<std::string> assignments;
    std::vector<std::string> announcements;
public:
    Class(const std::string& className, int capacity, const std::string& instructor);
    void addStudent(const std::string& student);
    void removeStudent(const std::string& student);
    void addAssignment(const std::string& assignment);
    void removeAssignment(const std::string& assignment);
    void addAnnouncement(const std::string& announcement);
    const std::string& getClassName() const;
    const std::vector<std::string>& getStudents() const;
    const std::vector<std::string>& getAssignments() const;
    const std::vector<std::string>& getAnnouncements() const;
};

#endif // BASE_H
