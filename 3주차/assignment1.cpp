#include <iostream>

void code(){

}

char rodata(){

    return 'a';
}

int main(){
    int static data = 1;
    int static bss;
    int * list = new int[1];
    list[0] = 0;
    int *heap = list;
    int stack = 1;

    std::cout << "code\t" << (void*) code  << std::endl; 
    /*(void*): 함수를 리턴하지않고 주소값으로 출력하겠다*/
    std::cout << "Rodata\t" << (void*) rodata << std::endl;
    std::cout << "data\t" << &data << std::endl;
    std::cout << "BSS\t" << &bss << std::endl;
    std::cout << "HEAP\t" << heap << std::endl;
    std::cout << "Stack\t" << &stack << std::endl;
    return 0;
}

