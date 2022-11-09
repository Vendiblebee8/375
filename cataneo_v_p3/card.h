#ifndef CARD_H
#define CARD_H
#include <stdlib.h>
#include <iostream>
#include <vector> 
#include <string>

using namespace std;

class Card{
    public:
    Card(int Wg, int Val, int num); // card constructor
    Card(); //default constructor
    bool readB(int Wg, int Val, int num); // reads the inputs in to the card
    int getW(); //gets the weight
    int getV(); //gets the value/profit
    int getN(); //gets the assigned number
    void setN(int n); //sets the assigned number
    private:
    int wg;
    int val;
    int number;
};

#endif