#include <stdlib.h>
#include <iostream>
#include "contest.h"
using namespace std;

contest::contest(int id, int Score){
    ID=id;
    score=Score;
    loc=id;
}

contest::contest(){
    ID=-1;
    score=-1;
}

bool contest::read(int id, int Score){
    ID=id;
    score=Score;
    loc=id;
}

int contest::getI(){
    return ID;
}

int contest::getL(){
    return loc;
}

int contest::getS(){
    return score;
}

void contest::setI(int i){
    ID=i;
}

void contest::setS(int i){
    score= score +i;
}

void contest::setL(int i){
    loc = i;
}