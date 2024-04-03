#ifndef ABOL_USER_H
#define ABOL_USER_H
#include "string"

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
    User();
    User(string name, string username, string password, string phone_number);
    virtual void displayMenu() = 0;
    virtual bool authenticate(string username, string password) = 0;
    string getName();
    string getUsername();
    string getPassword();
    string getPhoneNumber();
    void setName(string name);
    void setUsername(string username);
    void setPassword(string password);
    void setPhoneNumber(string phone_number);
};


#endif //ABOL_USER_H
