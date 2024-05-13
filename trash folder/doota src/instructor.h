#include "user.h"
class Instructor : public User {
public:
    void login() override;
    void createCourse(); 
};