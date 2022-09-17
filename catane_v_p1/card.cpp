#include <stdlib.h>
#include <iostream>
#include "card.h"
using namespace std;

Card::Card(string Name, string BuyP, string SellP, int cash, int SetN){
    name=Name;
    buyP=BuyP;
    setN=SetN;
    sellP=SellP;
    cash =-1;
}

Card::Card(){
    name ="";
    buyP = "";
    setN = 0;
    sellP = "";
    cash=-1;
}

bool Card::readB(string Name, string BuyP, int Cash, int SetN){
    name=Name;
    buyP=BuyP;
    setN=SetN;
    cash=Cash;
    return true;
}

bool Card::readS(string Name, string SellP){
    name=Name;
    setN=0;
    sellP=SellP;
    cash=-1;
    return true;
}

string Card::getN(){
    return name;
}

int Card::getB(){
    return stoi(buyP);
}

int Card::getS(){
    return stoi(sellP);
}

int Card::getSN(){
    return setN;
}

int Card::getC(){
    return cash;
}

int Card::profit(){
    return stoi(sellP)-stoi(buyP);
}

void Card::setNa(string SellP){
    sellP=SellP;
}

void Card::show(){
    cout << name << " " << buyP << " " << sellP << " " << setN << endl;
}