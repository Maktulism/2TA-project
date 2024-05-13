#include <fstream>
#include <sstream>
#include <limits>
#include "Teacher.h"
#include "iostream"
#include "string"

using namespace std;

Teacher::Teacher() : User("", "", "", ""), classes() {}

Teacher::Teacher(string teacherName) {
    this->name = teacherName;
}
Teacher::Teacher(string name, string username, string password, string phone_number, vector<Class> classes)
: User(name, username, password, phone_number), classes(classes) {}
void Teacher::displayMenu() {
    cout << "**Teacher Menu**" << endl;
    cout << "1. List Classes" << endl;
    cout << "2. Edit Class" << endl;
    cout << "3. Create Class" << endl;
    cout << "4. Create Assignment" << endl;
    cout << "5. Messaging" << endl;
    cout << "6. Grade Assignments" << endl;
    cout << "7. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            listClasses();
            break;
        case 2:
            editClass();
            break;
        case 3:
            createClass();
            break;
        case 4:
            createAssignment();
            break;
        case 5:
            messaging();
            break;
        case 6:
            gradeAssignments();
            break;
        case 7:
            exit(0);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}
bool Teacher::authenticate(string username, string password) {
    return this->username == username && this->password == password;
}

void Teacher::listClasses() {
    ifstream in("classes.txt");
    string line;
    if (!in.is_open()) {
        cout << "Error opening classes file!" << endl;
        return;
    }
    cout << "**Your Classes**" << endl;
    while (getline(in, line)) {
        std::istringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() < 3) {
            cout << "Error: Invalid class data format in 'classes.txt'." << endl;
            continue;
        }
        cout << "Class name: " << tokens[0] << endl;
        cout << "Subject: " << tokens[1] << endl;
        cout << "Grade level: " << tokens[2] << endl;
        cout << endl;
    }
    in.close();
    if (classes.empty() && !in.is_open()) {
        cout << "No classes found!" << endl;
    }
}
vector<string> Teacher::split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream stream(str);
    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
vector<Class> Teacher::getClassesForTeacher(string teacherUsername) {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        cout << "Error opening classes file!" << endl;
        return {};
    }
    vector<Class> classes;
    string line;
    while (getline(infile, line)) {
        vector<string> fields = split(line, ',');
        Class c(fields[0], fields[1], stoi(fields[2]));
        if (fields[3] == teacherUsername) {
            classes.push_back(c);
        }
    }
    infile.close();
    return classes;
}

void Teacher::editClass() {
    string className;
    cout << "Enter the name of the class to edit: ";
    cin >> className;
    if (!isClassExist(className)) {
        cout << "Class not found!" << endl;
        return;
    }
    Class currentClass = getClassByName(className);
    cout << "Current class details:" << endl;
    cout << "Name: " << currentClass.name << endl;
    cout << "Subject: " << currentClass.subject << endl;
    cout << "Grade level: " << currentClass.gradeLevel << endl;
    string newClassName, newSubject;
    int newGradeLevel;
    bool newClassEntered = false, newSubjectEntered = false, newGradeEntered = false;
    cout << "Enter new class name (or leave blank to keep unchanged): ";
    if (getline(cin, newClassName)) {
        newClassEntered = true;
    }
    cout << "Enter new subject (or leave blank to keep unchanged): ";
    if (getline(cin, newSubject)) {
        newSubjectEntered = true;
    }
    cout << "Enter new grade level (or leave blank to keep unchanged (-1 for unchanged)): ";
    while (!(cin >> newGradeLevel)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid grade level. Please enter an integer: ";
    }
    if (newClassEntered) {
        currentClass.name = newClassName;
    }
    if (newSubjectEntered) {
        currentClass.subject = newSubject;
    }
    if (newGradeLevel != -1) {
        currentClass.gradeLevel = newGradeLevel;
    }
    ofstream outfile("classes.txt", ios::out | ios::trunc);
    if (!outfile.is_open()) {
        cout << "Error opening classes file for update!" << endl;
        return;
    }
    vector<Class> allClasses;
    string line;
    ifstream infile("classes.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            vector<string> fields = split(line, ',');
            Class existingClass(stoi(fields[0]), fields[1], Teacher(), fields[2], stoi(fields[3]));
            allClasses.push_back(existingClass);
        }
        infile.close();
    }
    for (size_t i = 0; i < allClasses.size(); ++i) {
        if (allClasses[i].name == className) {
            allClasses[i] = currentClass;
            break;
        }
    }
    for (const Class& cls : allClasses) {
        outfile << cls.id << "," << cls.name << "," << cls.subject << "," << cls.gradeLevel << endl;
    }
    outfile.close();
    cout << "Class details updated successfully!" << endl;
}
bool Teacher::isClassExist(string className) {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        cout << "Error opening classes file!" << endl;
        return false;
    }
    string line;
    while (getline(infile, line)) {
        vector<string> fields = split(line, ',');
        if (fields[1] == className) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}
Class Teacher::getClassByName(string className) {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        throw runtime_error("Error opening classes file!");
    }
    string line;
    while (getline(infile, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() >= 1 && tokens[0] == className) {
            int id = stoi(tokens[1]);
            string subject = tokens[2];
            int gradeLevel = stoi(tokens[3]);
            Teacher teacher(this->getName());
            return Class(id, className, teacher, subject, gradeLevel);
        }
    }
    throw runtime_error("Class not found!");
}
void Teacher::updateClassDetails(Class c) {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        throw runtime_error("Error opening classes file!");
    }
    ofstream outfile("classes.tmp");
    if (!outfile.is_open()) {
        throw runtime_error("Error creating temporary file!");
    }
    string line;
    bool found = false;
    while (getline(infile, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() >= 1 && stoi(tokens[0]) == c.getId()) {
            outfile << c.getId() << "," << c.getName() << "," << c.getTeacher().getName() << "," << c.subject << "," << c.gradeLevel << endl;  // Use member variables directly
            found = true;
        } else {
            outfile << line << endl;
        }
    }
    if (!found) {
        throw runtime_error("Class not found!");
    }
    infile.close();
    outfile.close();
    remove("classes.txt");
    rename("classes.tmp", "classes.txt");
    cout << "Class details updated successfully!" << endl;
}
bool Teacher::updateClass(string className, string newClassName, string newSubject, string newGradeLevel) {
    ifstream infile("classes.txt");
    if (!infile.is_open()) {
        throw runtime_error("Error opening classes file!");
    }
    ofstream outfile("classes.tmp");
    if (!outfile.is_open()) {
        throw runtime_error("Error creating temporary file!");
    }
    string line;
    bool found = false;
    while (getline(infile, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() >= 1 && tokens[0] == className) {
            outfile << newClassName << "," << newSubject << "," << newGradeLevel << endl;
            found = true;
        } else {
            outfile << line << endl;
        }
    }
    if (!found) {
        return false;
    }
    infile.close();
    outfile.close();
    remove("classes.txt");
    rename("classes.tmp", "classes.txt");
    cout << "Class details updated successfully!" << endl;
    return true;
}
void Teacher::saveClass(Class c) {
    ofstream out("classes.txt", ios::app);
    out << c.name << "," << c.subject << "," << c.gradeLevel << endl;
    out.close();
}
void Teacher::createClass() {
    string className, subject;
    int gradeLevel;
    cout << "Enter class name: ";
    cin >> className;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter grade level: ";
    cin >> gradeLevel;
    Class newClass(className, subject, gradeLevel);
    saveClass(newClass);
    cout << "Class created successfully!" << endl;
}
void Teacher::createAssignment() {
    string className, assignmentTitle, description;
    cout << "Enter class name: ";
    cin >> className;
    cout << "Enter assignment title: ";
    cin >> assignmentTitle;
    cout << "Enter assignment description: ";
    cin.ignore();
    getline(cin, description);
    Assignment newAssignment;
    newAssignment.className = className;
    newAssignment.title = assignmentTitle;
    newAssignment.description = description;
    saveAssignment(newAssignment);
    cout << "Assignment created successfully!" << endl;
}
void Teacher::saveAssignment(Assignment a) {
    ofstream out("assignments.txt", ios::app);
    out << a.className << "," << a.title << "," << a.description << endl;
    out.close();
}
void Teacher::messaging() {
    string className, message;
    cout << "Enter class name: ";
    cin >> className;
    cout << "Enter message: ";
    cin.ignore();
    getline(cin, message);
    addClassComment(className, message);
    cout << "Message added as a comment successfully!" << endl;
}
void Teacher::addClassComment(string className, string message) {
    ofstream out("classes.txt", ios::app);
    out << className << "," << message << endl;
    out.close();
}
void Teacher::gradeAssignments() {
    listClasses();
    string className;
    cout << "Enter class name: ";
    cin >> className;
    vector<Assignment> assignments = getAllAssignments(className);
    for (Assignment assignment : assignments) {
        cout << "Assignment title: " << assignment.title << endl;
        cout << "Assignment description: " << assignment.description << endl;
        cout << "Student name: " << assignment.studentName << endl;
        int grade;
        cout << "Enter grade (0-100): ";
        cin >> grade;
        saveGrade(assignment.id, grade);
        cout << "Grade saved successfully!" << endl;
    }
}
void Teacher::saveGrade(int assignmentId, int grade) {
    ifstream in("assignments.txt");
    ofstream out("temp_assignments.txt");
    string line;
    bool foundAssignment = false;
    while (getline(in, line)) {
        std::stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (stoi(tokens[0]) == assignmentId) {
            tokens[tokens.size() - 1] = to_string(grade);
            foundAssignment = true;
            out << tokens[0];
            for (int i = 1; i < tokens.size(); i++) {
                out << "," << tokens[i];
            }
            out << endl;
        } else {
            out << line << endl;
        }
    }
    in.close();
    out.close();
    if (foundAssignment) {
        remove("assignments.txt");
        rename("temp_assignments.txt", "assignments.txt");
        cout << "Grade updated successfully!" << endl;
    } else {
        cout << "Assignment not found!" << endl;
        remove("temp_assignments.txt");
    }
}

vector<Assignment> Teacher::getAllAssignments(string className) {
    vector<Assignment> assignments;
    ifstream in("assignments.txt");
    string line;
    while (getline(in, line)) {
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
        if (assignment.className == className) {
            assignments.push_back(assignment);
        }
    }
    in.close();
    return assignments;
}