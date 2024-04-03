#ifndef ABOL_ADMIN_H
#define ABOL_ADMIN_H
#include "iostream"
#include "User.h"
#include "Teacher.h" // Include Teacher.h if necessary
// Forward declaration of Class
class Class;
using namespace std;

class Admin : public User {
public:
    Admin() {}
    Admin(string name, string username, string password, string phone_number) : User(name, username, password, phone_number) {}
    void displayMenu() {
        cout << "**Admin Menu**" << endl;
        cout << "1. Create Teacher" << endl;
        cout << "2. Edit/Delete Teacher" << endl;
        cout << "3. Manage Classes" << endl;
        cout << "4. Create Student" << endl;
        cout << "5. Edit/Delete Student" << endl;
        cout << "6. Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                createTeacher();
                break;
            case 2:
                editDeleteTeacher();
                break;
            case 3:
                manageClasses();
                break;
            case 4:
                createStudent();
                break;
            case 5:
                editDeleteStudent();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    bool authenticate(string username, string password) {
        return this->username == username && this->password == password;
    }
private:


    void editStudent(string username);
    void createTeacher();
    void editDeleteTeacher();
    void deleteTeacher(string username);
    void editTeacher(string username);
    vector<Class>getAllClasses();
    bool isStudentExist(string studentUsername);
    bool isClassExist(string className);
    void addStudentToClass();
    void addStudentToClassData(string studentUsername, string className);
    void removeStudentFromClass();
    void removeStudentFromClassData(string studentUsername, string className);
    void manageClasses();
    void listClasses();
    void createStudent();
    void editDeleteStudent();
    void deleteStudent(string username);
    bool isUsernameTaken(string username);
    bool isValidPassword(string password);
    bool isTeacherExist(string username);
};

#endif //ABOL_ADMIN_H
