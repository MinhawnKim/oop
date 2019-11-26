#include "json_list.h"
#include "json_dict.h"
#include "data/String.h"
#include "data/Integer.h"

json_object* json_object::parse(const char * ch, int length){
	if(ch[_index] == '['){
;	    return json_list::parse(ch, length);
	}
	if(ch[_index] == '{'){
;	    return json_dict::parse(ch,length);
	}
	if(ch[_index] == '''){
;	    return String::parse(ch,length);
	}
	if(ch[_index] == '"'){
;	    return String::parse(ch, length);
	}
	if(int(ch[_index]) <= 9){
;	   return Integer::parse(ch, length);
	}
    }
    return this;
}

static json_object* json_object::parse(const std::string& str){
    int len = str.length();
    int json_object::_index = 0;
    return this->parse(str, len);
}

