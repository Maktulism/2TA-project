#include <fstream>
#include <sstream>
#include "Admin.h"

void Admin::createTeacher() {
    string name, username, password, phone_number;
    cout << "Enter teacher name: ";
    cin >> name;
    cout << "Enter teacher username: ";
    cin >> username;
    cout << "Enter teacher password: ";
    cin >> password;
    cout << "Enter teacher phone number: ";
    cin >> phone_number;
    if (this->isUsernameTaken(username)) {
        cout << "Username already taken!" << endl;
        return;
    }
    if (!this->isValidPassword(password)) {
        cout << "Password is not strong enough!" << endl;
        return;
    }
    ofstream out("teachers.json");
    out << "{";
    out << "\"name\": \"" << name << "\",";
    out << "\"username\": \"" << username << "\",";
    out << "\"password\": \"" << password << "\",";
    out << "\"phone_number\": \"" << phone_number << "\"";
    out << "}";
    out.close();
    cout << "Teacher created successfully!" << endl;
}
void Admin::editDeleteTeacher() {
    string username;
    cout << "Enter teacher username: ";
    cin >> username;
    if (!isTeacherExist(username)) {
        cout << "Teacher not found!" << endl;
        return;
    }
    int choice;
    cout << "1. Edit teacher" << endl;
    cout << "2. Delete teacher" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            editTeacher(username);
            break;
        case 2:
            deleteTeacher(username);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}
void Admin::deleteTeacher(string username) {
    string confirmation;
    cout << "Are you sure you want to delete this teacher? (y/n): ";
    cin >> confirmation;
    if (confirmation != "y") {
        cout << "Deletion canceled!" << endl;
        return;
    }
    ifstream infile("teachers.json");
    ofstream outfile("teachers_updated.json");
    string line;
    while (getline(infile, line)) {
        if (line.find("\"" + username + "\"") == string::npos) {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove("teachers.json");
    rename("teachers_updated.json", "teachers.json");
    cout << "Teacher deleted successfully!" << endl;
}
void Admin::editTeacher(string username) {
    ifstream infile("teachers.json");
    if (!infile.is_open()) {
        std::cout << "Error opening teacher data file!" << std::endl;
        return;
    }
    std::string teacherData;
    std::string line;
    while (getline(infile, line)) {
        teacherData += line + "\n";
    }
    infile.close();
    if (teacherData.find("\"" + username + "\"") == std::string::npos) {
        std::cout << "Teacher with username " << username << " not found." << std::endl;
        return;
    }
    std::string newName, newSubject, newGradeLevel;
    std::cout << "Enter new name (leave blank for no change): ";
    std::getline(std::cin, newName);
    std::cout << "Enter new subject (leave blank for no change): ";
    std::getline(std::cin, newSubject);
    std::cout << "Enter new grade level (leave blank for no change): ";
    std::getline(std::cin, newGradeLevel);
    bool found = false;
    std::string updatedData;
    std::istringstream iss(teacherData);
    while (getline(iss, line)) {
        if (line.find("\"" + username + "\"") != std::string::npos) {
            if (!newName.empty()) {
                line = line.replace(line.find("name") + 7, username.length(), newName);
            }
            if (!newSubject.empty()) {
                line = line.replace(line.find("subject") + 10, username.length(), newSubject);
            }
            if (!newGradeLevel.empty()) {
                line = line.replace(line.find("gradeLevel") + 13, username.length(), newGradeLevel);
            }
            found = true;
        }
        updatedData += line + "\n";
    }
    if (!found) {
        std::cout << "Error: Could not update teacher information." << std::endl;
        return;
    }
    ofstream outfile("teachers_updated.json");
    outfile << updatedData;
    outfile.close();
    remove("teachers.json");
    rename("teachers_updated.json", "teachers.json");
    std::cout << "Teacher information updated successfully." << std::endl;
}
vector<Class> Admin::getAllClasses() {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        throw runtime_error("Error opening classes file!");
    }
    vector<Class> classes;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int id, gradeLevel;
        string name, teacherName, subject;
        iss >> id >> name >> teacherName >> subject >> gradeLevel;
        Teacher teacher(teacherName);
        Class classObj{id, name, teacher, subject, gradeLevel};
        classes.push_back(classObj);
    }
    infile.close();
    return classes;
}
bool Admin::isStudentExist(string studentUsername) {
    ifstream infile("students.json");
    if (!infile.is_open()) {
        cerr << "Error opening student data file!" << endl;
        return false;
    }
    bool exists = false;
    string line;
    while (getline(infile, line)) {
        if (line.find("\"username\": \"" + studentUsername + "\"") != string::npos) {
            exists = true;
            break;
        }
    }
    infile.close();
    return exists;
}
bool Admin::isClassExist(string className) {
    ifstream infile("classes.json");
    if (!infile.is_open()) {
        cerr << "Error opening class data file!" << endl;
        return false;
    }
    bool exists = false;
    string line;
    while (getline(infile, line)) {
        if (line.find("\"name\": \"" + className + "\"") != string::npos) {
            exists = true;
            break;
        }
    }
    infile.close();
    return exists;
}
void Admin::addStudentToClass() {
    string studentUsername, className;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter class name: ";
    cin >> className;
    if (!isStudentExist(studentUsername)) {
        cout << "Student not found!" << endl;
        return;
    }
    if (!isClassExist(className)) {
        cout << "Class not found!" << endl;
        return;
    }
    addStudentToClassData(studentUsername, className);
    cout << "Student added to class successfully!" << endl;
}
void Admin::addStudentToClassData(string studentUsername, string className) {
    if (studentUsername.empty() || className.empty()) {
        cerr << "Error: Username or class name is empty!" << endl;
        return;
    }
    ifstream infile("students.json");
    ofstream outfile("temp.json");
    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening student data files!" << endl;
        return;
    }
    bool studentExists = false;
    string line;
    while (getline(infile, line)) {
        if (line.find("\"username\": \"" + studentUsername + "\"") != string::npos) {
            studentExists = true;
            break;
        }
    }
    infile.close();
    if (!studentExists) {
        cerr << "Error: Student with username " << studentUsername << " does not exist!" << endl;
        return;
    }
    infile.open("classes.json");
    bool classExists = false;
    while (getline(infile, line)) {
        if (line.find("\"name\": \"" + className + "\"") != string::npos) {
            classExists = true;
            break;
        }
    }
    infile.close();

    if (!classExists) {
        cerr << "Error: Class with name " << className << " does not exist!" << endl;
        return;
    }
    infile.open("students.json");
    outfile.open("temp.json");
    bool studentAdded = false;
    while (getline(infile, line)) {
        if (line.find("\"username\": \"" + studentUsername + "\"") != string::npos) {
            if (!studentAdded) {
                line += ", \"class\": \"" + className + "\"";
                studentAdded = true;
            }
        }
        outfile << line << endl;
    }
    infile.close();
    outfile.close();
    remove("students.json");
    rename("temp.json", "students.json");

    if (studentAdded) {
        cout << "Student " << studentUsername << " successfully added to class " << className << endl;
    } else {
        cerr << "Error adding student to class!" << endl;
    }
}
void Admin::removeStudentFromClass() {
    string studentUsername, className;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter class name: ";
    cin >> className;
    if (!isStudentExist(studentUsername)) {
        cout << "Student not found!" << endl;
        return;
    }
    if (!isClassExist(className)) {
        cout << "Class not found!" << endl;
        return;
    }
    removeStudentFromClassData(studentUsername, className);
    cout << "Student removed from class successfully!" << endl;
}
void Admin::removeStudentFromClassData(string studentUsername, string className) {
    if (studentUsername.empty() || className.empty()) {
        cerr << "Error: Username or class name is empty!" << endl;
        return;
    }
    ifstream infile("students.json");
    ofstream outfile("temp.json");
    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening student data files!" << endl;
        return;
    }
    bool studentExists = false;
    string line;
    while (getline(infile, line)) {
        if (line.find("\"username\": \"" + studentUsername + "\"") != string::npos) {
            studentExists = true;
            break;
        }
    }
    infile.close();
    if (!studentExists) {
        cerr << "Error: Student with username " << studentUsername << " does not exist!" << endl;
        return;
    }
    infile.open("classes.json");
    bool classExists = false;
    while (getline(infile, line)) {
        if (line.find("\"name\": \"" + className + "\"") != string::npos) {
            classExists = true;
            break;
        }
    }
    infile.close();
    if (!classExists) {
        cerr << "Error: Class with name " << className << " does not exist!" << endl;
        return;
    }
    infile.open("students.json");
    outfile.open("temp.json");
    bool studentRemoved = false;
    while (getline(infile, line)) {
        if (line.find("\"username\": \"" + studentUsername + "\"") != string::npos) {
            if (!studentRemoved) {
                size_t pos = line.find("\"class\": \"" + className + "\"");
                if (pos != string::npos) {
                    line.erase(pos, line.length() - pos);
                    studentRemoved = true;
                }
            }
        }
        outfile << line << endl;
    }
    infile.close();
    outfile.close();
    remove("students.json");
    rename("temp.json", "students.json");
    if (studentRemoved) {
        cout << "Student " << studentUsername << " successfully removed from class " << className << endl;
    } else {
        cerr << "Error removing student from class!" << endl;
    }
}
void Admin::manageClasses() {
    listClasses();
    int choice;
    cout << "1. Add student to class" << endl;
    cout << "2. Remove student from class" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            addStudentToClass();
            break;
        case 2:
            removeStudentFromClass();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Admin::listClasses() {
    vector<Class> classes = getAllClasses();
    if (classes.empty()) {
        cout << "No classes found!" << endl;
    } else {
        for (Class& c : classes) {
            cout << "Class ID: " << c.getId() << endl;
            cout << "Class Name: " << c.getName() << endl;
            cout << "Teacher: " << c.getTeacher().getName() << endl;
            cout << "-----------------------" << endl;
        }
    }
}
void Admin::createStudent() {
    string name, username, password, phone_number, student_id;
    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student username: ";
    cin >> username;
    cout << "Enter student password: ";
    cin >> password;
    cout << "Enter student phone number: ";
    cin >> phone_number;
    cout << "Enter student ID: ";
    cin >> student_id;
    if (isUsernameTaken(username)) {
        cout << "Username already taken!" << endl;
        return;
    }
    if (!isValidPassword(password)) {
        cout << "Password is not strong enough!" << endl;
        return;
    }
    ofstream out("students.json");
    out << "{";
    out << "\"name\": \"" << name << "\",";
    out << "\"username\": \"" << username << "\",";
    out << "\"password\": \"" << password << "\",";
    out << "\"phone_number\": \"" << phone_number << "\",";
    out << "\"student_id\": \"" << student_id << "\"";
    out << "}";
    out.close();
    cout << "Student created successfully!" << endl;
}
void Admin::deleteStudent(string username) {
    string confirmation;
    cout << "Are you sure you want to delete student " << username << "? (y/n): ";
    cin >> confirmation;
    if (confirmation != "y") {
        cout << "Deletion canceled!" << endl;
        return;
    }
    string studentDataFilename = "students.json";
    ifstream infile(studentDataFilename);
    if (!infile.is_open()) {
        cerr << "Error opening student data file!" << endl;
        return;
    }
    ofstream outfile("temp.json");
    if (!outfile.is_open()) {
        cerr << "Error creating temporary file!" << endl;
        return;
    }
    bool studentDeleted = false;
    string line;
    while (getline(infile, line)) {
        if (line.find("\"username\": \"" + username + "\"") == string::npos) {
            outfile << line << endl;
        } else {
            studentDeleted = true;
        }
    }
    infile.close();
    outfile.close();
    if (studentDeleted) {
        remove(studentDataFilename.c_str());
        rename("temp.json", studentDataFilename.c_str());
        cout << "Student " << username << " deleted successfully!" << endl;
    } else {
        cerr << "Error: Student with username " << username << " not found!" << endl;
    }
}
void Admin::editDeleteStudent() {
    string username;
    cout << "Enter student username: ";
    cin >> username;
    if (!isStudentExist(username)) {
        cout << "Student not found!" << endl;
        return;
    }
    int choice;
    cout << "1. Edit student" << endl;
    cout << "2. Delete student" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            editStudent(username);
            break;
        case 2:
            deleteStudent(username);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}
bool Admin::isUsernameTaken(string username) {
    vector<string> usernames = {"user1", "user2", "user3"};
    for (string user : usernames) {
        if (user == username) {
            return true;
        }
    }
    return false;
}
bool Admin::isValidPassword(string password) {
    if (password.length() < 8) {
        return false;
    }
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    for (char c : password) {
        if (isupper(c)) {
            hasUpperCase = true;
        } else if (islower(c)) {
            hasLowerCase = true;
        }
    }
    if (!hasUpperCase || !hasLowerCase) {
        return false;
    }
    bool hasNumber = false;
    for (char c : password) {
        if (isdigit(c)) {
            hasNumber = true;
            break;
        }
    }
    if (!hasNumber) {
        return false;
    }
    return true;
}

bool Admin::isTeacherExist(string username) {
    ifstream infile("teachers.json");
    if (!infile.is_open()) {
        cerr << "Error opening teacher data file!" << endl;
        return false;
    }
    string line;
    while (getline(infile, line)) {
        size_t pos = line.find("\"username\": \"" + username + "\"");
        if (pos != string::npos) {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}