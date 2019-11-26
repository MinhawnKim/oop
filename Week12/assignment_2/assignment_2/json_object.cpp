#include "json_object.h"
#include "json_dict.h"
#include "json_list.h"
#include "data/Integer.h"
#include "data/String.h"

int json_object::_index = 0;
json_object* json_object::parse(const char* str , int length){
    if(str[0] == '{'){
	return json_dict::parse(str, length);
    }
    else if(str[0] == '\''){
	return String::parse(str, length, str[0]);
    }
    else if(str[0] == '['){
	return json_list::parse(str, length);
    }
    else {
	return Integer::parse(str,length);
    }
}
json_object* json_object::parse(const std::string& str){
    json_object::_index = 0;
    int len = str.length();
    const char* c = str.c_str();
    return parse(c, len);
}
