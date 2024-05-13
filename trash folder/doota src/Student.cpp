#include <sstream>
#include "Student.h"
Student::Student() {}
Student::Student(string name, string username, string password, string phone_number, vector<string> classes) : User(name, username, password, phone_number), classes(classes) {}
void Student::displayMenu() {
    cout << "**Student Menu**" << endl;
    cout << "1. List Classes" << endl;
    cout << "2. Assignments" << endl;
    cout << "3. Announcements" << endl;
    cout << "4. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            listClasses();
            break;
        case 2:
            assignments();
            break;
        case 3:
            announcements();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}
bool Student::authenticate(string username, string password) {
    return this->username == username && this->password == password;
}
void Student::listClasses() {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        cout << "Error opening classes file!" << endl;
        return;
    }
    vector<pair<string, string>> classes;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string className, teacherName;
        getline(ss, className, ',');
        getline(ss, teacherName, ',');

        classes.push_back({className, teacherName});
    }
    infile.close();
    string studentUsername = this->username;
    ifstream infile2("enrolled_students.txt");
    if (!infile2.is_open()) {
        cout << "Error opening enrolled students file!" << endl;
        return;
    }
    cout << "**Registered Classes**" << endl;
    cout << "---------------------" << endl;
    cout << "| Class Name | Teacher Name |" << endl;
    cout << "---------------------" << endl;
    bool foundClass = false;
    while (getline(infile2, line)) {
        stringstream ss(line);
        string className, studentUsernameEnrolled;
        getline(ss, className, ',');
        getline(ss, studentUsernameEnrolled, ',');
        if (studentUsername == studentUsernameEnrolled) {
            foundClass = true;
            for (auto& c : classes) {
                if (c.first == className) {
                    cout << "| " << c.first << " | " << c.second << " |" << endl;
                    break;
                }
            }
        }
    }
    infile2.close();
    if (!foundClass) {
        cout << "No registered classes found!" << endl;
    }
}
vector<Assignment> Student::getAssignmentsForStudent(string studentName) {
    vector<Assignment> assignments;
    ifstream infile("assignments.txt");
    string line;
    if (!infile.is_open()) {
        cout << "Error opening assignments file!" << endl;
        return assignments;
    }
    while (getline(infile, line)) {
        std::istringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        Assignment assignment;
        assignment.id = stoi(tokens[0]);
        assignment.className = tokens[1];
        assignment.title = tokens[2];
        assignment.description = tokens[3];
        assignment.studentName = tokens[4];
        assignment.grade = stoi(tokens[5]);
        if (assignment.studentName == studentName) {
            assignments.push_back(assignment);
        }
    }
    infile.close();
    return assignments;
}
void Student::assignments() {
    string studentName = this->username;
    vector<Assignment> assignments = getAssignmentsForStudent(studentName);
    if (assignments.empty()) {
        cout << "No assignments found." << endl;
        return;
    }
    cout << "Available options:" << endl;
    cout << "1. View all assignments" << endl;
    cout << "2. View assignment details" << endl;
    cout << "3. Submit assignment" << endl;
    cout << "4. View grades" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            for (Assignment assignment : assignments) {
                cout << "Assignment ID: " << assignment.id << endl;
                cout << "Class: " << assignment.className << endl;
                cout << "Title: " << assignment.title << endl;
                cout << "Description: " << assignment.description << endl;
                cout << "Grade: " << assignment.grade << endl;
                cout << endl;
            }
            break;
        case 2:
            int assignmentId;
            cout << "Enter assignment ID: ";
            cin >> assignmentId;
            bool foundAssignment = false;
            for (Assignment assignment : assignments) {
                if (assignment.id == assignmentId) {
                    foundAssignment = true;
                    cout << "Assignment Details:" << endl;
                    cout << "Class: " << assignment.className << endl;
                    cout << "Title: " << assignment.title << endl;
                    cout << "Description: " << assignment.description << endl;
                    break;
                }
            }
            if (!foundAssignment) {
                cout << "Assignment not found!" << endl;
            }
            break;
        case 3:
            int submitAssignmentId;
            cout << "Enter assignment ID to submit: ";
            cin >> submitAssignmentId;

            bool submitFoundAssignment = false;
            for (Assignment assignment : assignments) {
                if (assignment.id == submitAssignmentId) {
                    submitFoundAssignment = true;
                    string filename;
                    cout << "Enter the filename of your submission: ";
                    cin >> filename;
                    ifstream in(filename);
                    if (!in.is_open()) {
                        cout << "Error opening file!" << endl;
                        break;
                    }
                    ofstream out("submissions/" + studentName + "_" + to_string(assignmentId) + ".txt");
                    out << in.rdbuf();
                    in.close();
                    out.close();
                    cout << "Assignment submitted successfully!" << endl;
                    break;
                }
            }

            if (!submitFoundAssignment) {
                cout << "Assignment not found!" << endl;
            }
            break;
        case 4:
            bool hasGrades = false;
            for (Assignment assignment : assignments) {
                if (assignment.grade != -1) {
                    hasGrades = true;
                    cout << "Assignment ID: " << assignment.id << endl;
                    cout << "Class: " << assignment.className << endl;
                    cout << "Title: " << assignment.title << endl;
                    cout << "Grade: " << assignment.grade << endl;
                    cout << endl;
                }
            }
            if (!hasGrades) {
                cout << "No grades available yet." << endl;
            }
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}
void Student::announcements() {
    ifstream infile("announcements.txt");
    if (!infile.is_open()) {
        cout << "Error opening announcements file!" << endl;
        return;
    }
    vector<string> announcements;
    string line;
    while (getline(infile, line)) {
        announcements.push_back(line);
    }
    infile.close();
    if (announcements.empty()) {
        cout << "No announcements found!" << endl;
    } else {
        cout << "Announcements:" << endl;
        for (const auto& announcement : announcements) {
            cout << "  - " << announcement << endl;
        }
    }
}