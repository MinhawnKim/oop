#ifndef SMART_PTR_STUDENT_H
#define SMART_PTR_STUDENT_H

#include "human.h"

class student : public human {
  private:
    int student_id = -1;
  public:
    student();
    student(char* name);
    student(int student_id);
    student(char* name, int student_id);
    int get_student_id() const;
    int get_id();
};

#endif //SMART_PTR_STUDENT_H
