#include <stdlib.h>
#include <iostream>
#include "card.h"
using namespace std;

Card::Card(int Wg, int Val, int num){
    wg=Wg;
    val=Val;
    number=num;
}

Card::Card(){
    wg=0;
    val=0;
    number=0;
}

bool Card::readB(int Wg, int Val, int num){
    wg=Wg;
    val=Val;
    number=num;
    return true;
}

int Card::getV(){
    return val;
}

int Card::getW(){
    return wg;
}

int Card::getN(){
    return number;
}

void Card::setN(int n){
    number = n;
}


