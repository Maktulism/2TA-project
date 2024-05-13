#include "User.h"

User::User() = default;
User::User(string name, string username, string password, string phone_number) {
    this->name = name;
    this->username = username;
    this->password = password;
    this->phone_number = phone_number;
}
string User::getName() { return name; }
string User::getUsername() { return username; }
string User::getPassword() { return password; }
string User::getPhoneNumber() { return phone_number; }
void User::setName(string name) { this->name = name; }
void User::setUsername(string username) { this->username = username; }
void User::setPassword(string password) { this->password = password; }
void User::setPhoneNumber(string phone_number) { this->phone_number = phone_number; }