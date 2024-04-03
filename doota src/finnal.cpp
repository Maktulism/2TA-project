#include <iostream>
#include <string>
#include "User.h"
#include "Teacher.h"
#include "Admin.h"
#include "Student.h"


int main() {
  Teacher* teacherPtr = nullptr;
  Student* studentPtr = nullptr;
  Admin admin("abolfazl", "admin", "password123", "1234567890");
  while (true) {
    UserType userType;
    cout << "**Login**" << endl;
    cout << "1. Login as Admin" << endl;
    cout << "2. Login as Teacher" << endl;
    cout << "3. Login as Student" << endl;
    cout << "4. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
      case 1:
        userType = ADMIN;
        break;
      case 2:
        userType = TEACHER;
        break;
      case 3:
        userType = STUDENT;
        break;
      case 4:
        cout << "Exiting..." << endl;
        return 0;
      default:
        cout << "Invalid choice!" << endl;
        continue;
    }
    string username, password;
    while (true) {
      cout << "Enter username: ";
      cin >> username;
      cout << "Enter password: ";
      cin >> password;
      if (userType == ADMIN && admin.authenticate(username, password)) {
        break; // Login successful for admin
      } else {
        cout << "Invalid username or password!" << endl;
      }
    }
switch (userType) {
  case ADMIN:
    admin.displayMenu();
    break;
  case TEACHER:
    if (teacherPtr != nullptr) {
      teacherPtr->displayMenu(); 
    }
    break;
  case STUDENT:
    if (studentPtr != nullptr) {
      studentPtr->displayMenu(); 
    break;
}
  return 0;
}
  }
  }
























