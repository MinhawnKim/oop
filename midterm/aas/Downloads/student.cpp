#include "student.h"

student::student() {
name = nullptr;
}

student::student(char* name) {
this->name = name;
}

student::student(int student_id) {
name = nullptr;
	this->student_id = student_id;
}

student::student(char *name, int student_id) {
this->name = name;
this->student_id = student_id;
}

int student::get_student_id()const{
return student_id;
}


int student::get_id(){
return 1;
}
