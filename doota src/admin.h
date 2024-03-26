#include "user.h"
class Admin : public User {
public:
    void login() override;
    void createInstructor();
};
