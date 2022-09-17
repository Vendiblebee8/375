#ifndef CARD_H
#define CARD_H
#include <stdlib.h>
#include <iostream>
#include <vector> 
#include <string>

using namespace std;

class Card{
    public:
    Card(string Name, string BuyP, string SellP, int cash, int SetN);
    Card();
    string getN();
    int getB();
    int getS();
    int getSN();
    bool readB(string Name, string BuyP, int cash, int SetN);
    bool readS(string Name, string SellP);
    void setNa(string SellP);
    void show();
    int getC();
    int profit();

    private:
    string name;
    string buyP;
    string sellP;
    int cash;
    int setN;
};

#endif