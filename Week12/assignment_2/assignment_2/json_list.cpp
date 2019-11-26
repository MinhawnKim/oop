#include "json_list.h"
#include "json_dict.h"
#include "data/Integer.h"
#include "data/String.h"
#include <iostream>
#include <algorithm>
#include <iterator>

json_list::json_list() {
    std::vector<json_object*> v = v;
};
json_object* json_list::parse(const char* str, int length){
    _index++;
    json_object* obj = new json_list();
    while(str[_index] != ']'){
	if(str[_index] == '['){
	    obj->v.push_back(parse(str, length));
	}
	else if(str[_index] == '{'){
	    obj->v.push_back(json_dict::parse(str,length));
	}
	else if(str[_index] == '\''){
	    obj->v.push_back(String::parse(str,length,str[_index]));
	}
	else {
	    obj->v.push_back(Integer::parse(str,length));
	}
	_index++;
    }
    return obj;
};
json_object* json_list::operator[](int key) const {
    return v[key];
};
json_object::_type() json_list::type(){
    return LIST;
};
std::string json_list::to_string(){
    std::string str = "[";
    int it = 0;
    for (it = 0; it < v.size()-1; it++){
	str += v[it]->to_string();
	str += ", ";
    };
    str += v[it]->to_string();
    str += "]";
    return str;
};
