#ifndef CONTEST_H
#define CONTEST_H
#include <stdlib.h>
#include <iostream>
#include <vector> 
#include <string>

using namespace std;

class contest{
    public:
    contest(int id, int Score); //contructs the contestant
    contest(); //makes a base contestant
    int getI(); //gets ID
    int getS(); //gets the score
    int getL(); //gets the location
    void setI(int i); //sets ID
    void setS(int i); //sets the score
    void setL(int i); //sets the location
    bool read(int id, int Score); //sets the values of a contestant

    private:
    int ID; //ID or <k> value
    int score; //score or <s> value
    int loc; //location or <j> value
};

#endif