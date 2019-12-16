#include "puyo.cpp"
#include <ctime>
#include <stdio.h>


using namespace std;

int main(){

    puyo game = puyo();

    game.print();
    int nInput;
    int nRandom;

    srand((unsigned int)time(0));
    while(true){
	nRandom = rand()%3 +1;
	if(!game.can_make(nRandom)){
	    break;
	}
	game.make(nRandom);
	game.print();
	
	while(true){
	    if(game.movable_vec.empty()){
		break;
	    }
	    nInput = getchar();
	    int flushinput =getchar();
	    game.move(nInput);
	    game.print();
	}

	game.gravity();
	
	while(game.explosion()){
	    game.print();
	    game.gravity();
	}

    }


    return 0;
}
