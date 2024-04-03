#ifndef ABOL_CLASS_H
#define ABOL_CLASS_H
#include "Teacher.h"

class Class {
public:
    Class();
    int id;
    string name;
    Teacher teacher;
    string subject;
    int gradeLevel;
    Class(int id, const std::string& name, const Teacher& teacher, const std::string& subject, int gradeLevel);
    int getId() const;
    string getName() const;
    Teacher getTeacher() const;
    void setId(int new_id);
    void setName(const string& new_name);
    void setTeacher(const Teacher& new_teacher);
    Class(const std::string& field1, const std::string& field2, int field3);

};


#endif //ABOL_CLASS_H
