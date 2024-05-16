#ifndef MARK_H
#define MARK_H
#include <string> // C++ standard string class

class Mark{
    public:
    void getMarkDetails();
    void storeMember();
    void showMarksProf(std::string &coursecode);
    void showMemberData();

    void displayStData();
    void displayMarksStud(int &iD);

    int studentId;
    std::string assignmentTitle;
    int grade;
protected:
    std::string mark;
    std::string courseCode;
};

#endif