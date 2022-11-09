/*“I have done this assignment completely on my own. I have not
copied it, nor have I given my solution to anyone else. I understand that if I am involved
in plagiarism or cheating I will have to sign an official form to admit that I have cheated
and that this form will be stored in my official university record. I also understand that I
will receive a grade of 0 for the involved assignment for the first offense and that I will
receive a grade of “F” for the course for any additional offense.”
Vincenzo Cataneo
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <getopt.h>
#include <stdio.h>
#include "card.h"
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

ofstream myfile;    // allows to write to the output file
vector<Card> listF; // all readins from input
vector<Card> listC; // current problem set
vector<Card> used;  // used cards in results
vector<Card> used1; //used for list comparisons
vector<Card> used2;
vector<string> include; //temporay list of used
vector<string> bestset; //final list of used
vector<double> tempB; //fractal tracker 
int length = 0;
int size = 0; //size of the set
int sizeL = 0; //size left in a set
int cap = 0; //knapsack weight
int capT = 0; //knapsack weight left
int func; //what algorithm to use
int number = 1; //numbered items in list
int maxprofit = 0; //max profit of list
int wgT = 0; //weight tracker
Card card; //default card to read onto

bool fileOpen(string file, ifstream &fileObj) // opens the desired file
{
    fileObj.open(file);
    if (fileObj.is_open())
    {
        return true;
    }
    else
    {
        cout << "does not open" << endl;
        return false;
    }
}

void readFile(string file, ifstream &fileObj, string output) // reads in the input file and runs given commands
{
    bool ran = false;
    myfile.open(output); // opens the output file
    string line;

    while (getline(fileObj, line))
    {
        string wt = "";
        string val = "";
        stringstream ss(line);
        getline(ss, wt, ' ');
        getline(ss, val, ' ');
        card.readB(stoi(wt), stoi(val), number);
        number++;
        listF.push_back(card);
    }
}

bool cmp(Card a, Card b) //use in the sort to sort the problem set by their (value/weight)
{
    double c1 = (double)a.getV() / a.getW();
    double c2 = (double)b.getV() / b.getW();
    return c1 > c2;
}

int max(int a, int b) { return (a > b) ? a : b; } //used to find the maximum value of two inputs

double Greed1() //simple greed function used to get the highest weight ratio items in
{
    sort(listC.begin(), listC.end(), cmp);
    double result = 0.0;
    for (int i = 0; i < listC.size(); i++)//goes through the whole list
    {
        if (listC.at(i).getW() <= capT) //checks to see if the current items weight fits in the solution and if true adds it
        {
            capT -= listC.at(i).getW();
            result += listC.at(i).getV();
            used.push_back(listC.at(i));
        }
    }
    return result;
}

double Greed2() //does the same as greed1 but also checks if 1 big item is greater than that
{
    sort(listC.begin(), listC.end(), cmp);
    double result = 0.0;
    double max = 0;
    for (int i = 0; i < listC.size(); i++)
    {
        if (listC.at(i).getW() <= capT)
        {
            capT -= listC.at(i).getW();
            wgT += listC.at(i).getW();
            result += listC.at(i).getV();
            used1.push_back(listC.at(i));
        }
    }
    max = result;
    result = 0.0;
    capT = cap;
    for (int i = 0; i < listC.size(); i++)
    {
        if (listC.at(i).getV() / listC.at(i).getW() <= cap)
        {
            if (result < listC.at(i).getV())
            {
                used2.clear();
                result = listC.at(i).getV();
                used2.push_back(listC.at(i));
            }
        }
        else
        {
            break;
        }
    }
    if (max > result)
    {
        used = used1;
        return max;
    }
    used = used2;
    return result;
}

double KWF(int n, int w, int p){ //used the calculate the upperbound of the promising function
    //cout << "kwf" << endl;
    int bound = p;
    for(int j = n; j<=listC.size();j++){
        tempB.push_back(0);
    }
    while((w<cap) && (n<listC.size())){
        if(w+listC.at(n).getW()<=cap){
            //cout << n << " " << tempB.size() << endl;
            tempB.at(n)=1;
            w=w+listC.at(n).getW();
            bound = bound + listC.at(n).getV();
        }
        else{
            tempB.at(n)=((double)cap-w)/listC.at(n).getW();
            w=cap;
            bound = bound + listC.at(n).getV() * tempB.at(n);
        }
        n=n+1;
    }
    return bound;
}

int promising(int i, int weight, int profit) //checks to see if the path is promsing or not 
{
    //cout << "prom" << endl;
    if (weight >= cap)
        return 0;
    int bound = KWF(i+1,weight,profit);
    if (bound > maxprofit)
    {
        return 1;
    }
    else
        return 0;
}

void knapsack(int n, int p, int w) //the knapsack algorithm used to calculate max profit
{
    if (w <= cap && p > maxprofit) //if the weight is smaller than the cap and profit would be greater than previous profit set new max profit
    {
        maxprofit = p;
        length = n;
        wgT += w;
        bestset = include;
    }
    if (promising(n, w, p)) //checks to see if the next path is promising
    {
        include.push_back("yes"); //adds the item to the list
        knapsack(n + 1, p + listC.at(n + 1).getV(), w + listC.at(n + 1).getW()); //checks if the next node is the new max
        include.push_back("no"); 
        knapsack(n + 1, p, w);
    }
}

int backtrack() //backtrack call but is just mostly setup for knapsack and then gives the calc function the max
{
    sort(listC.begin(), listC.end(), cmp);
    card.readB(0,0,0);
    listC.insert(listC.begin(),card);
    maxprofit = 0;
    length = 0;
    knapsack(0, 0, 0);
    for(int i=1;i<bestset.size();i++){
        if(bestset.at(i)=="yes"){
            used.push_back(listC.at(i));
        }
    }
    return maxprofit;
}

void calc() //returns all temp vectors to empty and decides which function to run
{
    tempB.clear();
    bestset.clear();
    include.clear();
    used.clear();
    used1.clear();
    used2.clear();
    auto start = high_resolution_clock::now();
    int result;
    if (func == 0)
    {
        result = Greed1();
    }
    if (func == 1)
    {
        result = Greed2();
    }
    if (func == 2)
    {
        result = backtrack();
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double dur = duration.count();
    myfile << size << " " << result << " " << dur / (10 ^ 3); //prints the ouput excluding which items were used
    for (int i = 0; i < used.size(); i++) //adds which items were used to the output
    {
        if (used.at(i).getN() != 0)
        {
            myfile << " " << used.at(i).getN();
        }
    }

    myfile << endl;
}

int main(int argc, char *argv[])
{
    listF.push_back(card); //puts item to the front of the list to fill slot 1
    int cur = 2; //used to keep track of where the pointer is in the main list when making sub list
    ifstream fin;
    char commands;
    string input = "default";
    string output = "default";
    input = argv[1];          // gets input file name
    output = argv[2];         // gets output file name
    func = stoi(argv[3]);     // gets what type of algorithm you wish to use
    if (fileOpen(input, fin)) // opens input file
    {
        readFile(input, fin, output); // reads in input file
        fin.close();                  // closes input file
    }
    card.readB(0, 0, 0);
    size = listF.at(1).getW();
    sizeL = size;
    cap = listF.at(1).getV();
    capT = cap;
    number = 1;
    for (int i = 1; i <= size; i++) //creating sub list for each sub problem
    {
        listF.at(cur).setN(number);
        number++;
        listC.push_back(listF.at(cur));
        cur++;
        sizeL--;
        if (sizeL == 0 && cur < listF.size()) //once the sub list is made it does the sub problem then restarts the varible to make the next sub list
        {
            calc();
            size = listF.at(cur).getW(); // wg
            sizeL = size;
            cap = listF.at(cur).getV(); // val
            capT = cap;
            i = 0;
            cur++;
            listC.clear();
            number = 1;
        }
        else if (sizeL == 0) //when there are no more sub list to be made
        {
            calc();
            break;
        }
    }
}