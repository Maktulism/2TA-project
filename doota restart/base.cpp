// base.cpp
#include "base.h"

User::User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

User::~User() {}

std::string User::getUsername() const {
    return username;
}

Admin::Admin(const std::string& username, const std::string& password)
        : User(username, password) {}

#include <iostream>

void Admin::displayMenu() {
    int choice;
    do {
        std::cout << "\nWelcome, Admin!\n";
        std::cout << "1. Create Instructor\n";
        std::cout << "2. Manage Instructors\n";
        std::cout << "3. Manage Classes\n";
        std::cout << "4. Create Student\n";
        std::cout << "5. Manage Students\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                createInstructor();
                break;
            case 2:
                manageInstructors();
                break;
            case 3:
                manageClasses();
                break;
            case 4:
                createStudent();
                break;
            case 5:
                manageStudents();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 6);
}


#include <fstream>

void Admin::createInstructor() {
    std::string instructorName, instructorUsername, instructorPassword, instructorPhone;

    // Prompting admin to enter instructor details
    std::cout << "\nEnter instructor name: ";
    std::cin.ignore();
    std::getline(std::cin, instructorName);
    std::cout << "Enter instructor username: ";
    std::getline(std::cin, instructorUsername);
    std::cout << "Enter instructor password: ";
    std::getline(std::cin, instructorPassword);
    std::cout << "Enter instructor phone: ";
    std::getline(std::cin, instructorPhone);

    // Writing instructor details to file
    std::ofstream outFile("instructors.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << instructorName << ',' << instructorUsername << ',' << instructorPassword << ',' << instructorPhone << '\n';
        std::cout << "Instructor created successfully!\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}


void Admin::manageInstructors() {
    int choice;
    do {
        std::cout << "\nManage Instructors Menu:\n";
        std::cout << "1. View All Instructors\n";
        std::cout << "2. Update Instructor Details\n";
        std::cout << "3. Delete Instructor\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                viewAllInstructors();
                break;
            case 2:
                updateInstructorDetails();
                break;
            case 3:
                deleteInstructor();
                break;
            case 4:
                std::cout << "Exiting manage instructors menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
}

void Admin::viewAllInstructors() {
    std::ifstream inFile("instructors.txt");
    if (inFile.is_open()) {
        std::cout << "\nAll Instructors:\n";
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name, username, password, phone;
            std::getline(iss, name, ',');
            std::getline(iss, username, ',');
            std::getline(iss, password, ',');
            std::getline(iss, phone, ',');
            std::cout << "Name: " << name << ", Username: " << username << ", Phone: " << phone << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::updateInstructorDetails() {
    std::string instructorUsername;
    std::cout << "\nEnter the username of the instructor whose details you want to update: ";
    std::cin >> instructorUsername;

    std::ifstream inFile("instructors.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string username;
            std::getline(iss, username, ',');
            if (username == instructorUsername) {
                std::string newName, newPassword, newPhone;
                std::cout << "Enter new name for the instructor: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                std::cout << "Enter new password for the instructor: ";
                std::getline(std::cin, newPassword);
                std::cout << "Enter new phone number for the instructor: ";
                std::getline(std::cin, newPhone);
                line = newName + ',' + username + ',' + newPassword + ',' + newPhone;
            }
            lines.push_back(line);
        }
        inFile.close();

        std::ofstream outFile("instructors.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Instructor details updated successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::deleteInstructor() {
    std::string instructorUsername;
    std::cout << "\nEnter the username of the instructor you want to delete: ";
    std::cin >> instructorUsername;

    std::ifstream inFile("instructors.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string username;
            std::getline(iss, username, ',');
            if (username != instructorUsername) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            std::cout << "Instructor with username " << instructorUsername << " not found!\n";
            return;
        }

        std::ofstream outFile("instructors.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Instructor deleted successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::manageClasses() {
    int choice;
    do {
        std::cout << "\nManage Classes Menu:\n";
        std::cout << "1. View All Classes\n";
        std::cout << "2. Create New Class\n";
        std::cout << "3. Update Class Details\n";
        std::cout << "4. Delete Class\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                viewAllClasses();
                break;
            case 2:
                createNewClass();
                break;
            case 3:
                updateClassDetails();
                break;
            case 4:
                deleteClass();
                break;
            case 5:
                std::cout << "Exiting manage classes menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 5);
}

void Admin::viewAllClasses() {
    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::cout << "\nAll Classes:\n";
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string className;
            std::getline(iss, className, ',');
            std::cout << "Class Name: " << className << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::createNewClass() {
    std::string className;
    int capacity;

    std::cout << "\nEnter class name: ";
    std::cin.ignore();
    std::getline(std::cin, className);
    std::cout << "Enter class capacity: ";
    std::cin >> capacity;

    std::ofstream outFile("classes.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << className << ',' << capacity << '\n';
        std::cout << "Class created successfully!\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}

void Admin::updateClassDetails() {
    std::string className;
    std::cout << "\nEnter the name of the class whose details you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name;
            std::getline(iss, name, ',');
            if (name == className) {
                int capacity;
                std::cout << "Enter new capacity for the class: ";
                std::cin >> capacity;
                line = className + ',' + std::to_string(capacity);
                found = true;
            }
            lines.push_back(line);
        }
        inFile.close();

        if (!found) {
            std::cout << "Class with name " << className << " not found!\n";
            return;
        }

        std::ofstream outFile("classes.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Class details updated successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::deleteClass() {
    std::string className;
    std::cout << "\nEnter the name of the class you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name;
            std::getline(iss, name, ',');
            if (name != className) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            std::cout << "Class with name " << className << " not found!\n";
            return;
        }

        std::ofstream outFile("classes.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Class deleted successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::createStudent() {
    std::string studentName, studentPhoneNumber, studentMajor, studentID, studentPassword;

    // Prompting admin to enter student details
    std::cout << "\nEnter student name: ";
    std::cin.ignore();
    std::getline(std::cin, studentName);
    std::cout << "Enter student phone number: ";
    std::getline(std::cin, studentPhoneNumber);
    std::cout << "Enter student major: ";
    std::getline(std::cin, studentMajor);
    std::cout << "Enter student ID: ";
    std::getline(std::cin, studentID);
    std::cout << "Enter student password: ";
    std::getline(std::cin, studentPassword);

    // Writing student details to file
    std::ofstream outFile("students.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << studentName << ',' << studentPhoneNumber << ',' << studentMajor << ',' << studentID << ',' << studentPassword << '\n';
        std::cout << "Student created successfully!\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}

void Admin::manageStudents() {
    int choice;
    do {
        std::cout << "\nManage Students Menu:\n";
        std::cout << "1. View All Students\n";
        std::cout << "2. Update Student Details\n";
        std::cout << "3. Delete Student\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                viewAllStudents();
                break;
            case 2:
                updateStudentDetails();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                std::cout << "Exiting manage students menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
}

void Admin::viewAllStudents() {
    std::ifstream inFile("students.txt");
    if (inFile.is_open()) {
        std::cout << "\nAll Students:\n";
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name, phoneNumber, major, id, password;
            std::getline(iss, name, ',');
            std::getline(iss, phoneNumber, ',');
            std::getline(iss, major, ',');
            std::getline(iss, id, ',');
            std::getline(iss, password, ',');
            std::cout << "Name: " << name << ", Phone Number: " << phoneNumber << ", Major: " << major << ", ID: " << id << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::updateStudentDetails() {
    std::string studentID;
    std::cout << "\nEnter the ID of the student whose details you want to update: ";
    std::cin >> studentID;

    std::ifstream inFile("students.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string id;
            std::getline(iss, id, ',');
            if (id == studentID) {
                std::string newName, newPhoneNumber, newMajor, newPassword;
                std::cout << "Enter new name for the student: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                std::cout << "Enter new phone number for the student: ";
                std::getline(std::cin, newPhoneNumber);
                std::cout << "Enter new major for the student: ";
                std::getline(std::cin, newMajor);
                std::cout << "Enter new password for the student: ";
                std::getline(std::cin, newPassword);
                line = newName + ',' + newPhoneNumber + ',' + newMajor + ',' + studentID + ',' + newPassword;
                found = true;
            }
            lines.push_back(line);
        }
        inFile.close();

        if (!found) {
            std::cout << "Student with ID " << studentID << " not found!\n";
            return;
        }

        std::ofstream outFile("students.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Student details updated successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Admin::deleteStudent() {
    std::string studentID;
    std::cout << "\nEnter the ID of the student you want to delete: ";
    std::cin >> studentID;

    std::ifstream inFile("students.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string id;
            std::getline(iss, id, ',');
            if (id != studentID) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            std::cout << "Student with ID " << studentID << " not found!\n";
            return;
        }

        std::ofstream outFile("students.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Student deleted successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

Instructor::Instructor(const std::string& username, const std::string& password)
        : User(username, password) {}

void Instructor::displayMenu() {
    int choice;
    do {
        std::cout << "\nInstructor Menu:\n";
        std::cout << "1. Manage Classes\n";
        std::cout << "2. Create Assignment\n";
        std::cout << "3. Manage Announcements\n";
        std::cout << "4. Grade Students\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                manageClasses();
                break;
            case 2:
                createAssignment();
                break;
            case 3:
                manageAnnouncements();
                break;
            case 4:
                gradeStudents();
                break;
            case 5:
                std::cout << "Exiting instructor menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 5);
}

void Instructor::manageClasses() {
    int choice;
    do {
        std::cout << "\nManage Classes Menu:\n";
        std::cout << "1. View All Classes\n";
        std::cout << "2. Update Class Details\n";
        std::cout << "3. Delete Class\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                viewAllClasses();
                break;
            case 2:
                updateClassDetails();
                break;
            case 3:
                deleteClass();
                break;
            case 4:
                std::cout << "Exiting manage classes menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
}

void Instructor::viewAllClasses() {
    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::cout << "\nAll Classes:\n";
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name, instructor, capacity;
            std::getline(iss, name, ',');
            std::getline(iss, instructor, ',');
            std::getline(iss, capacity, ',');
            std::cout << "Name: " << name << ", Instructor: " << instructor << ", Capacity: " << capacity << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::updateClassDetails() {
    std::string className;
    std::cout << "\nEnter the name of the class you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name;
            std::getline(iss, name, ',');
            if (name == className) {
                std::string newInstructor, newCapacity;
                std::cout << "Enter new instructor for the class: ";
                std::getline(std::cin, newInstructor);
                std::cout << "Enter new capacity for the class: ";
                std::getline(std::cin, newCapacity);
                line = className + ',' + newInstructor + ',' + newCapacity;
                found = true;
            }
            lines.push_back(line);
        }
        inFile.close();

        if (!found) {
            std::cout << "Class with name " << className << " not found!\n";
            return;
        }

        std::ofstream outFile("classes.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Class details updated successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::deleteClass() {
    std::string className;
    std::cout << "\nEnter the name of the class you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name;
            std::getline(iss, name, ',');
            if (name != className) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            std::cout << "Class with name " << className << " not found!\n";
            return;
        }

        std::ofstream outFile("classes.txt");
        if (outFile.is_open()) {
            for (const auto& l : lines) {
                outFile << l << '\n';
            }
            std::cout << "Class deleted successfully!\n";
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::createAssignment() {
    std::string className;
    std::cout << "\nEnter the name of the class to create assignment for: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name;
            std::getline(iss, name, ',');
            if (name == className) {
                std::ofstream outFile("assignments.txt", std::ios::app);
                if (outFile.is_open()) {
                    std::string assignmentName, deadline;
                    std::cout << "Enter assignment name: ";
                    std::getline(std::cin, assignmentName);
                    std::cout << "Enter deadline (e.g., 2024-05-31): ";
                    std::getline(std::cin, deadline);
                    outFile << className << ',' << assignmentName << ',' << deadline << '\n';
                    outFile.close();
                    std::cout << "Assignment created successfully!\n";
                } else {
                    std::cerr << "Unable to open file for writing!\n";
                }
                found = true;
                break;
            }
        }
        inFile.close();

        if (!found) {
            std::cout << "Class with name " << className << " not found!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::manageAnnouncements() {
    int choice;
    do {
        std::cout << "\nManage Announcements Menu:\n";
        std::cout << "1. View All Announcements\n";
        std::cout << "2. Create Announcement\n";
        std::cout << "3. Delete Announcement\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                viewAllAnnouncements();
                break;
            case 2:
                createAnnouncement();
                break;
            case 3:
                deleteAnnouncement();
                break;
            case 4:
                std::cout << "Exiting manage announcements menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
}

void Instructor::viewAllAnnouncements() {
    std::ifstream inFile("announcements.txt");
    if (inFile.is_open()) {
        std::cout << "\nAll Announcements:\n";
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::createAnnouncement() {
    std::ofstream outFile("announcements.txt", std::ios::app);
    if (outFile.is_open()) {
        std::string announcement;
        std::cin.ignore();
        std::cout << "\nEnter the announcement: ";
        std::getline(std::cin, announcement);
        outFile << announcement << '\n';
        std::cout << "Announcement created successfully!\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}

void Instructor::deleteAnnouncement() {
    std::vector<std::string> announcements;
    std::ifstream inFile("announcements.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            announcements.push_back(line);
        }
        inFile.close();

        int announcementNumber;
        std::cout << "\nEnter the number of the announcement you want to delete: ";
        std::cin >> announcementNumber;

        if (announcementNumber >= 1 && announcementNumber <= announcements.size()) {
            announcements.erase(announcements.begin() + announcementNumber - 1);
            std::ofstream outFile("announcements.txt");
            if (outFile.is_open()) {
                for (const auto& a : announcements) {
                    outFile << a << '\n';
                }
                std::cout << "Announcement deleted successfully!\n";
                outFile.close();
            } else {
                std::cerr << "Unable to open file for writing!\n";
            }
        } else {
            std::cerr << "Invalid announcement number!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::gradeStudents() {
    std::string className;
    std::cout << "\nEnter the name of the class to grade students for: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("assignments.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string assignmentClass, assignmentName, deadline;
            std::getline(iss, assignmentClass, ',');
            std::getline(iss, assignmentName, ',');
            std::getline(iss, deadline, ',');
            if (assignmentClass == className) {
                found = true;
                std::cout << "\nGrading students for assignment: " << assignmentName << '\n';
                gradeStudentsForAssignment(className, assignmentName);
                break;
            }
        }
        inFile.close();

        if (!found) {
            std::cout << "Class with name " << className << " not found!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Instructor::gradeStudentsForAssignment(const std::string& className, const std::string& assignmentName) {
    std::string studentsFile = className + "_students.txt";
    std::ifstream inFile(studentsFile);
    if (inFile.is_open()) {
        std::string line;
        std::cout << "\nStudents and their grades for assignment '" << assignmentName << "':\n";
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string studentName, grade;
            std::getline(iss, studentName, ',');
            std::getline(iss, grade, ',');
            std::cout << "Student: " << studentName << ", Grade: " << grade << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

Student::Student(const std::string& username, const std::string& password)
        : User(username, password) {}

void Student::displayMenu() {
    int choice;
    do {
        std::cout << "\nStudent Menu:\n";
        std::cout << "1. View Classes\n";
        std::cout << "2. View Assignments\n";
        std::cout << "3. View Announcements\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewClasses();
                break;
            case 2:
                viewAssignments();
                break;
            case 3:
                viewAnnouncements();
                break;
            case 4:
                std::cout << "Exiting student menu...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

void Student::viewClasses() {
    std::ifstream inFile("classes.txt");
    if (inFile.is_open()) {
        std::cout << "\nClasses Available:\n";
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string className;
            std::getline(iss, className, ',');
            std::cout << className << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Student::viewAssignments() {
    std::string className;
    std::cout << "\nEnter the name of the class to view assignments for: ";
    std::cin.ignore();
    std::getline(std::cin, className);

    std::ifstream inFile("assignments.txt");
    if (inFile.is_open()) {
        std::cout << "\nAssignments for Class '" << className << "':\n";
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string assignmentClass, assignmentName, deadline;
            std::getline(iss, assignmentClass, ',');
            std::getline(iss, assignmentName, ',');
            std::getline(iss, deadline, ',');
            if (assignmentClass == className) {
                found = true;
                std::cout << "Assignment: " << assignmentName << ", Deadline: " << deadline << '\n';
            }
        }
        if (!found) {
            std::cout << "No assignments found for class '" << className << "'!\n";
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

void Student::viewAnnouncements() {
    std::ifstream inFile("announcements.txt");
    if (inFile.is_open()) {
        std::cout << "\nAnnouncements:\n";
        std::string announcement;
        while (std::getline(inFile, announcement)) {
            std::cout << announcement << '\n';
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}

Class::Class(const std::string& className, int capacity, const std::string& instructor)
        : className(className), capacity(capacity), instructor(instructor) {}

void Class::addStudent(const std::string& student) {
    students.push_back(student); // Assuming 'students' is a vector<string> member variable of the Class class

    std::ofstream outFile(className + "_students.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << student << ",0\n"; // Assuming the student's initial grade is set to 0
        outFile.close();
        std::cout << "Student '" << student << "' added to class '" << className << "' successfully!\n";
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}

void Class::removeStudent(const std::string& student) {
    auto it = std::find(students.begin(), students.end(), student);
    if (it != students.end()) {
        students.erase(it); // Remove student from the vector

        std::string fileName = className + "_students.txt";
        std::ifstream inFile(fileName);
        if (inFile.is_open()) {
            std::vector<std::string> updatedStudents;
            std::string line;
            while (std::getline(inFile, line)) {
                if (line.find(student) == std::string::npos) {
                    updatedStudents.push_back(line); // Add all students except the one to be removed
                }
            }
            inFile.close();

            std::ofstream outFile(fileName);
            if (outFile.is_open()) {
                for (const auto& s : updatedStudents) {
                    outFile << s << '\n'; // Rewrite the file without the removed student
                }
                outFile.close();
                std::cout << "Student '" << student << "' removed from class '" << className << "' successfully!\n";
            } else {
                std::cerr << "Unable to open file for writing!\n";
            }
        } else {
            std::cerr << "Unable to open file for reading!\n";
        }
    } else {
        std::cout << "Student '" << student << "' is not enrolled in class '" << className << "'.\n";
    }
}

void Class::addAssignment(const std::string& assignment) {
    assignments.push_back(assignment); // Assuming 'assignments' is a vector<string> member variable of the Class class

    std::ofstream outFile(className + "_assignments.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << assignment << '\n'; // Write the assignment name to the file
        outFile.close();
        std::cout << "Assignment '" << assignment << "' added to class '" << className << "' successfully!\n";
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}

void Class::removeAssignment(const std::string& assignment) {
    auto it = std::find(assignments.begin(), assignments.end(), assignment); // Use std::find to find the assignment
    if (it != assignments.end()) {
        assignments.erase(it); // Remove assignment from the vector

        std::string fileName = className + "_assignments.txt";
        std::ifstream inFile(fileName);
        if (inFile.is_open()) {
            std::vector<std::string> updatedAssignments;
            std::string line;
            while (std::getline(inFile, line)) {
                if (line != assignment) {
                    updatedAssignments.push_back(line); // Add all assignments except the one to be removed
                }
            }
            inFile.close();

            std::ofstream outFile(fileName);
            if (outFile.is_open()) {
                for (const auto& a : updatedAssignments) {
                    outFile << a << '\n'; // Rewrite the file without the removed assignment
                }
                outFile.close();
                std::cout << "Assignment '" << assignment << "' removed from class '" << className << "' successfully!\n";
            } else {
                std::cerr << "Unable to open file for writing!\n";
            }
        } else {
            std::cerr << "Unable to open file for reading!\n";
        }
    } else {
        std::cout << "Assignment '" << assignment << "' does not exist in class '" << className << "'.\n";
    }
}

void Class::addAnnouncement(const std::string& announcement) {
    std::ofstream outFile(className + "_announcements.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << announcement << '\n'; // Write the announcement to the file
        outFile.close();
        std::cout << "Announcement added to class '" << className << "' successfully!\n";
    } else {
        std::cerr << "Unable to open file for writing!\n";
    }
}

const std::string& Class::getClassName() const {
    return className;
}

const std::vector<std::string>& Class::getStudents() const {
    return students;
}

const std::vector<std::string>& Class::getAssignments() const {
    return assignments;
}

const std::vector<std::string>& Class::getAnnouncements() const {
    return announcements;
}
