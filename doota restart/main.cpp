#include <iostream>
#include "base.h"

int main() {
    char userType;
    bool exitProgram = false;

    while (!exitProgram) {
        std::cout << "Welcome to the Educational System!\n";
        std::cout << "Please select your user type:\n";
        std::cout << "A: Admin\n";
        std::cout << "I: Instructor\n";
        std::cout << "S: Student\n";
        std::cout << "Q: Quit Program\n";
        std::cout << "Enter your choice: ";
        std::cin >> userType;

        switch (userType) {
            case 'A': {
                // Admin login
                std::string adminUsername, adminPassword;
                std::cout << "Enter admin username: ";
                std::cin >> adminUsername;
                std::cout << "Enter admin password: ";
                std::cin >> adminPassword;

                // Authenticate admin
                Admin admin(adminUsername, adminPassword);
                // Display admin menu
                admin.displayMenu();
                break;
            }
            case 'I': {
                // Instructor login
                std::string instructorUsername, instructorPassword;
                std::cout << "Enter instructor username: ";
                std::cin >> instructorUsername;
                std::cout << "Enter instructor password: ";
                std::cin >> instructorPassword;

                // Authenticate instructor
                Instructor instructor(instructorUsername, instructorPassword);
                // Display instructor menu
                instructor.displayMenu();
                break;
            }
            case 'S': {
                // Student login
                std::string studentUsername, studentPassword;
                std::cout << "Enter student username: ";
                std::cin >> studentUsername;
                std::cout << "Enter student password: ";
                std::cin >> studentPassword;

                // Authenticate student
                Student student(studentUsername, studentPassword);
                // Display student menu
                student.displayMenu();
                break;
            }
            case 'Q':
                exitProgram = true;
                break;
            default:
                std::cout << "Invalid user type!\n";
                break;
        }
    }

    std::cout << "Exiting the program...\n";
    return 0;
}