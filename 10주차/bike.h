#ifndef BIKE_H
#define BIKE_H

#include "vehicle.h"

class bike : public vehicle{
private:
    char* bike_name;
    int bike_number;
public:
    bike();
    explicit bike(int,int);
    explicit bike(int,int,char*);
    explicit bike(int,int,char*,int);
    explicit bike(int,int,char*,int,bool);
    
    int get_bike_number();
    char* get_bike_name();
    const char*get_class_name();
    void set_bike_name(char*);
    void set_bike_number(int);
};
#endif
