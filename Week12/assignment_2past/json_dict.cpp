#include "json_list.h"
#include "/data/String.h"
#include "/data/Integer.h"

void json_dict::put(json_object* key, json_object* val){
 v.push_back(key, val);
}
int json_dict::find(json_object* key){
    int index = 0;
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        if (*it == key) {
            break;
        }
        index += 1;
    }   
    return index;
}

static json_object*
json_dict::parse(const char *, int length){
}

_type json_dict::type(){
    return DICT;
}

std::string json_dict::to_string(){
    std::string str = "{";
    int index = 0;
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        if (*it == 30) {
            break;
        }
        index += 1;
    }
return "{" + +"" + "" +

}


