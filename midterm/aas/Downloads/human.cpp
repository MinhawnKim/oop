//
// Created by 김혁진 on 2019/10/28.
//

#include "human.h"

human::human() {
name = new char;
}

human::human(char name[]) {
this->name = name;
}

char *human::get_name() const{
return this->name;
}

int human::get_id(){
return 0;
}
