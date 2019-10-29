//
// Created by 김혁진 on 14/10/2019.
//

#include "shared_mut.h"

namespace ptr {
shared_mut::shared_mut() {
    _mgr = new mgr();
}

shared_mut::shared_mut(Object* _obj) {
    _mgr = new mgr(_obj);
}

shared_mut::~shared_mut() {
    release();
}
shared_mut::shared_mut(const shared_mut& a){
    std::cout<<"cop"<<std::endl;
    release();
    _mgr = a._mgr;
    increase();
}
void shared_mut::release(){
    _mgr->count -= 1;
    if(_mgr->count == 0){
	delete(_mgr);
	_mgr = nullptr;
    }
    _mgr = new mgr();
    
}
Object* shared_mut::get() const {
    if(_mgr == nullptr){
	return nullptr;
    }
    return _mgr->ptr;

}
int shared_mut::count() {
    return _mgr->count;
}
void shared_mut::increase() {
    this->_mgr->count++;
}
shared_mut shared_mut::operator+(const shared_mut &shared){
 shared_mut n(new Object(get()->get() + shared.get()->get()));
 std::cout<<"+oper"<<std::endl;
 return n;
}
shared_mut shared_mut::operator-(const shared_mut &shared){
 shared_mut n(new Object(get()->get() - shared.get()->get()));
    return n;
}
shared_mut shared_mut::operator*(const shared_mut &shared){
 shared_mut n(new Object(get()->get() * shared.get()->get()));
    return n;
}
shared_mut shared_mut::operator/(const shared_mut &shared){
 shared_mut n(new Object(get()->get() / shared.get()->get()));
    return n;
}
Object* shared_mut::operator->(){
    return _mgr->ptr;
}
shared_mut& shared_mut::operator=(const shared_mut &r){
    std::cout<<"OKOK"<<std::endl;
    release();
    _mgr = r._mgr;
    increase();
    return *this;
}
} // end of namespace ptr
