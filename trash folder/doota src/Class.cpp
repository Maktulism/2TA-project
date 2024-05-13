#include <string>
#include "Class.h"
Class::Class() = default;
Class::Class(int id, const std::string& name, const Teacher* teacher, const std::string& subject, int gradeLevel)
  : id(id), name(name), teacher(teacher), subject(subject), gradeLevel(gradeLevel) {}
int Class::getId() const { return id; }
string Class::getName() const { return name; }
Teacher* Class::getTeacher() const  { return teacher; }
void Class::setId(int new_id) { id = new_id; }
void Class::setName(const string& new_name) { name = new_name; }
void Class::setTeacher(const Teacher* new_teacher) {
  teacher = &new_teacher;
}
Class::Class(const std::string& field1, const std::string& field2, int field3)
        : name(field1),
          subject(field2),
          gradeLevel(field3){}
