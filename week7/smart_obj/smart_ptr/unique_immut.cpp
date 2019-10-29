//
// Created by 김혁진 on 14/10/2019.
//

#include "unique_immut.h"

namespace ptr {
unique_immut::unique_immut() {
    _mgr = new mgr();
}

unique_immut::unique_immut(Object *obj) {
    _mgr = new mgr(obj);
}

unique_immut::unique_immut(const unique_immut &immut) {
    if (immut._mgr) {
        int val = immut._mgr->ptr->get();
        _mgr = new mgr(val);
    }
}

unique_immut::~unique_immut() {
    release();
}
void unique_immut::release(){
    if(_mgr != nullptr){
	delete(_mgr);
	_mgr = nullptr;
    }
}
Object* unique_immut::get() const{
    if(_mgr == nullptr){
        return nullptr;
    }
    return _mgr->ptr;
}

unique_immut unique_immut::operator+(unique_immut &unique){
    int val = get()->get() + unique.get()->get();
    release();
    unique.release();
    unique_immut ui(new Object(val));
    return ui;
}
unique_immut unique_immut::operator-(unique_immut &unique){
    int val = get()->get() - unique.get()->get();
    unique_immut ui(new Object(val));
    release();
    unique.release();
    return ui;
}
unique_immut unique_immut::operator*(unique_immut &unique){
    int val = get()->get() * unique.get()->get();
    unique_immut ui(new Object(val));
    release();
    unique.release();
    return ui;
}
unique_immut unique_immut::operator/(unique_immut &unique){
    int val = get()->get() / unique.get()->get();
    unique_immut ui(new Object(val));
    release();
    unique.release();
    return ui;
}
Object* unique_immut::operator->(){
    return _mgr->ptr;
}
unique_immut& unique_immut::operator=(unique_immut& r){
    if(_mgr == r._mgr){
	return *this;
    }
    unique_immut ui(r);
    release();
    r.release();
    return ui;
}
} // end of namespace ptr
