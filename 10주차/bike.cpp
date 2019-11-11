#include "bike.h"

bike::bike() : vehicle(){
}
bike::bike(int wheel_number,int max_speed):vehicle(wheel_number, max_speed){

}
bike::bike(int wheel_number,int max_speed,char* bike_name):vehicle(wheel_number, max_speed){
    this->bike_name = bike_name;
}
bike::bike(int wheel_number,int max_speed,char* bike_name,int bike_number):vehicle(wheel_number, max_speed){
    this->bike_name = bike_name;
    this->bike_number = bike_number;
}
bike::bike(int wheel_number,int max_speed,char* bike_name,int bike_number,bool has_name):vehicle(wheel_number, max_speed, has_name){
    this->bike_name = bike_name;
    this->bike_number = bike_number;
}

int bike::get_bike_number(){
    return this->bike_number;
}

char* bike::get_bike_name(){
    return this->bike_name;
}

const char* bike::get_class_name(){
    return "bike";
}
void bike::set_bike_name(char* bike_name){
    this->bike_name = bike_name;
    return;
}
void bike::set_bike_number(int bike_number){
    this->bike_number = bike_number;
    return;
}
