#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
enum UserType {
  ADMIN,
  TEACHER,
  STUDENT
};
class User {
protected:
  string name;
  string username;
  string password;
  string phone_number;
public:
  User() {}
  User(string name, string username, string password, string phone_number) {
    this->name = name;
    this->username = username;
    this->password = password;
    this->phone_number = phone_number;
  }
  virtual void displayMenu() = 0;
  virtual bool authenticate(string username, string password) = 0;
  string getName() { return name; }
  string getUsername() { return username; }
  string getPassword() { return password; }
  string getPhoneNumber() { return phone_number; }
  void setName(string name) { this->name = name; }
  void setUsername(string username) { this->username = username; }
  void setPassword(string password) { this->password = password; }
  void setPhoneNumber(string phone_number) { this->phone_number = phone_number; }
};
class Class {
public:
    Class() = default;
    int id;
    string name;
    // Forward declaration of Teacher class
    class Teacher;
    
    string subject;
    int gradeLevel;
      Class(const std::string& name, const std::string& subject, int gradeLevel)
      : id(-1), name(name), subject(subject), gradeLevel(gradeLevel) {}
  int getId() const { return id; }
  string getName() const { return name; }
  Teacher& getTeacher() const { return *teacher; } // Use pointer dereference
  void setId(int new_id) { id = new_id; }
  void setName(const string& new_name) { name = new_name; }
  void setTeacher(Teacher* new_teacher);
Class(const std::string& field1, const std::string& field2, int field3)
    : name(field1),
      subject(field2),
      gradeLevel(field3){} 
private:
Teacher* teacher; // Use pointer 
};
class Assignment {
 public:
  int id;
  string className; 
  string title;
  string description; 
  string studentName; 
  int grade;
};
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

void createTeacher() {
  string name, username, password, phone_number;
  cout << "Enter teacher name: ";
  cin >> name;
  cout << "Enter teacher username: ";
  cin >> username;
  cout << "Enter teacher password: ";
  cin >> password;
  cout << "Enter teacher phone number: ";
  cin >> phone_number;
  if (isUsernameTaken(username)) {
    cout << "Username already taken!" << endl;
    return;
  }
  if (!isValidPassword(password)) {
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
void editDeleteTeacher() {
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
void deleteTeacher(string username) {
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
void editTeacher(string username) {
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
vector<Class>getAllClasses() {
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

bool isStudentExist(string studentUsername) {
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
bool isClassExist(string className) {
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
void addStudentToClass() {
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
void addStudentToClassData(string studentUsername, string className) {
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
void removeStudentFromClass() {
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
void removeStudentFromClassData(string studentUsername, string className) {
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
void manageClasses() {
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
void listClasses() {
  vector<Class> classes = getAllClasses();
  if (classes.empty()) {
    cout << "No classes found!" << endl;
  } else {
    for (Class c : classes) {
      cout << "Class ID: " << c.getId() << endl;
      cout << "Class Name: " << c.getName() << endl;
      cout << "Teacher: " << c.getTeacher().getName() << endl;
      cout << "-----------------------" << endl;
    }
  }
}
void createStudent() {
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
void deleteStudent(string username) {
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
void editStudent(string username) {
  ifstream infile("students.json");
  if (!infile.is_open()) {
    std::cout << "Error opening student data file!" << std::endl;
    return;
  }
  std::string studentData;
  std::string line;
  while (getline(infile, line)) {
    studentData += line + "\n";
  }
  infile.close();
  if (studentData.find("\"" + username + "\"") == std::string::npos) {
    std::cout << "Student with username " << username << " not found." << std::endl;
    return;
  }
  std::string newName, newStudentID, newPhoneNumber;
  std::cout << "Enter new name (leave blank for no change): ";
  std::getline(std::cin, newName);
  std::cout << "Enter new student ID (leave blank for no change): ";
  std::getline(std::cin, newStudentID);
  std::cout << "Enter new phone number (leave blank for no change): ";
  std::getline(std::cin, newPhoneNumber);
  bool found = false;
  std::string updatedData;
  std::istringstream iss(studentData);
  while (getline(iss, line)) {
    if (line.find("\"" + username + "\"") != std::string::npos) {
      if (!newName.empty()) {
        line = line.replace(line.find("name") + 7, username.length(), newName);
      }
      if (!newStudentID.empty()) {
        line = line.replace(line.find("student_id") + 13, username.length(), newStudentID);
      }
      if (!newPhoneNumber.empty()) {
        line = line.replace(line.find("phone_number") + 15, username.length(), newPhoneNumber);
      }
      found = true;
    }
    updatedData += line + "\n";
  }
  if (!found) {
    std::cout << "Error: Could not update student information." << std::endl;
    return;
  }
  ofstream outfile("students_updated.json");
  outfile << updatedData;
  outfile.close();
  remove("students.json");
  rename("students_updated.json", "students.json");
  std::cout << "Student information updated successfully." << std::endl;
}
void editDeleteStudent() {
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
bool isUsernameTaken(string username) {
  vector<string> usernames = {"user1", "user2", "user3"};
  for (string user : usernames) {
    if (user == username) {
      return true;
    }
  }
  return false;
}
bool isValidPassword(string password) {
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
bool isTeacherExist(string username) {
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
};
class Teacher : public User {
  vector<Class> classes;
public:
  Teacher() : User("", "", "", ""), classes() {}
  Teacher(string teacherName) {
    this->name = teacherName;
  }
  Teacher(string name, string username, string password, string phone_number, vector<Class> classes) 
      : User(name, username, password, phone_number), classes(classes) {}
  void displayMenu() {
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
  bool authenticate(string username, string password) {
    return this->username == username && this->password == password;
  }
private:

void listClasses() {
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
vector<string> split(const string& str, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream stream(str);
  while (getline(stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}
vector<Class> getClassesForTeacher(string teacherUsername) {
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
void editClass() {
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
bool isClassExist(string className) {
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
Class getClassByName(string className) {
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
void updateClassDetails(Class c) {
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
bool updateClass(string className, string newClassName, string newSubject, string newGradeLevel) {
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
void saveClass(Class c) {
  ofstream out("classes.txt", ios::app);
  out << c.name << "," << c.subject << "," << c.gradeLevel << endl;
  out.close();
}
void createClass() {
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
void createAssignment() {
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
void saveAssignment(Assignment a) {
  ofstream out("assignments.txt", ios::app);
  out << a.className << "," << a.title << "," << a.description << endl;
  out.close();
}
void messaging() {
  string className, message;
  cout << "Enter class name: ";
  cin >> className;
  cout << "Enter message: ";
  cin.ignore();
  getline(cin, message);
  addClassComment(className, message);
  cout << "Message added as a comment successfully!" << endl;
}
void addClassComment(string className, string message) {
  ofstream out("classes.txt", ios::app);
  out << className << "," << message << endl;
  out.close();
}
void gradeAssignments() {
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
void saveGrade(int assignmentId, int grade) {
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
vector<Assignment> getAllAssignments(string className) {
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
};
class Student : public User {
  vector<string> classes;
public:
  Student() {}
  Student(string name, string username, string password, string phone_number, vector<string> classes) : User(name, username, password, phone_number), classes(classes) {}
  void displayMenu() {
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
  bool authenticate(string username, string password) {
    return this->username == username && this->password == password;
  }
private:
void listClasses() {
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
vector<Assignment> getAssignmentsForStudent(string studentName) {
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
void assignments() {
  string studentName = this->username;
  vector<Assignment> assignments = getAssignmentsForStudent(studentName);

  // Check if there are no assignments
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
    // View all assignments
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

    // View assignment details
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

    // Submit assignment
    case 3: {
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
    }

    // View grades
    case 4: {
      bool hasGrades = false;
      for (Assignment assignment : assignments) {
        if (assignment.grade != -1) {
          hasGrades = true;
          cout << "Assignment ID: " << assignment.id << endl;
          cout << "Class: " << assignment.className << endl;
          cout << "Title: " << assignment.title << endl;
          cout << "Grade: " << assignment.grade << endl;
          cout << endl;
          break;
        }
      }
      if (!hasGrades) {
        cout << "No grades available yet." << endl;
      }
      break;
    }

    // Default case (not necessary here, but can be added for completeness)
    default:
      cout << "Invalid choice." << endl;
  }
}

void announcements() {
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
};
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