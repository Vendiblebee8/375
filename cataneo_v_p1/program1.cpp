#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <getopt.h>
#include <stdlib.h>
#include "parser.h"
#include "card.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

vector<Card> buy;
vector<Card> sell;
vector<Card> tempB;
vector<Card> Max;
ofstream myfile;
Card card;
int setF;
int numB = 0;
int numS = 0;

bool fileOpen(string file, ifstream &fileObj)
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

void readFileB(string file, ifstream &fileObj)
{
    int cash = 0;
    setF = 0;
    string line;
    string name;
    string buyP;
    int setN = 0;
    string sellP;
    while (getline(fileObj, line))
    {
        name = "";
        buyP = -1;
        sellP = -1;
        stringstream ss(line);
        getline(ss, name, ' ');
        getline(ss, buyP, ' ');
        try
        {
            numB = numB + stoi(name);
            cash = stoi(buyP);
            setN++;
            setF++;
        }
        catch (std::invalid_argument const &ex)
        {
            if (card.readB(name, buyP, cash, setN))
            {
                buy.push_back(card);
            }
        }
    }
}
void readFileS(string file, ifstream &fileObj)
{
    int setF = 0;
    string line;
    string name;
    string buyP;
    int setN;
    string sellP;
    while (getline(fileObj, line))
    {
        name = "";
        buyP = -1;
        setN = 0;
        sellP = -1;
        stringstream ss(line);
        getline(ss, name, ' ');
        getline(ss, sellP, ' ');
        try
        {
            numS = +stoi(name);
        }
        catch (std::invalid_argument const &ex)
        {
            if (card.readS(name, sellP))
            {
                sell.push_back(card);
            }
        }
    }
}

vector<Card> computeMaxProfit(vector<Card> I, int cash)
{
    auto start = high_resolution_clock::now();
    int maxProfit = 0;
    int profit = 0;
    vector<Card> S;
    vector<Card> M;
    int sumI = 0;
    int sumS = 0;
    for (int i = 0; i < I.size(); i++)
    {
        sumI = sumI + I.at(i).getB();
    }
    if (sumI <= cash)
    {
        for (int i = 0; i < I.size(); i++)
        {
            M.push_back(I.at(i));
            maxProfit = maxProfit + I.at(i).profit();
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        double dur = duration.count();
        myfile << I.size() << " " << maxProfit << " " << M.size() << " " << dur / (10 ^ 6) << endl;
        for (int i = 0; i < I.size(); i++)
        {
            myfile << I.at(i).getN() << endl;
        }
        return I;
    }
    int power_set_size = pow(2, I.size());
    for (int i = 0; i < power_set_size; i++)
    {
        S.clear();
        for (int j = 0; j < I.size(); j++)
        {
            if (i & (1 << j))
            {
                S.push_back(I.at(j));
            }
        }
        sumS = 0;
        profit = 0;
        for (int i = 0; i < S.size(); i++)
        {
            sumS = sumS + S.at(i).getB();
        }
        if (sumS <= cash)
        {
            for (int i = 0; i < S.size(); i++)
            {
                profit = profit + S.at(i).profit();
            }

            if (profit > maxProfit)
            {
                maxProfit = profit;
                M = S;
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double dur = duration.count();
    myfile << I.size() << " " << maxProfit << " " << M.size() << " " << dur / (10 ^ 6) << endl;
    for (int i = 0; i < M.size(); i++)
    {
        myfile << M.at(i).getN() << endl;
    }
    return M;
}

int main(int argc, char *argv[])
{
    ifstream fin;
    string buyerFile = "default";
    string sellerFile = "default";
    char commands;

    while ((commands = getopt(argc, argv, "m:p:")) != EOF)
    {
        if (commands == 'm')
        {
            sellerFile = optarg;
        }
        if (commands == 'p')
        {
            buyerFile = optarg;
        }
    }
    if (fileOpen(buyerFile, fin))
    {
        readFileB(buyerFile, fin);
        fin.close();
    }

    if (fileOpen(sellerFile, fin))
    {
        readFileS(sellerFile, fin);
        fin.close();
    }
    myfile.open("output.txt");

    for (int i = 0; i < buy.size(); i++)
    {
        for (int j = 0; j < sell.size(); j++)
        {
            if (buy.at(i).getN() == sell.at(j).getN())
            {
                buy.at(i).setNa(to_string(sell.at(j).getS()));
            }
        }
    }
    for (int j = 1; j <= setF; j++)
    {
        tempB.clear();
        for (int i = 0; i < buy.size(); i++)
        {
            if (buy.at(i).getSN() == j)
            {
                tempB.push_back(buy.at(i));
            }
        }
        computeMaxProfit(tempB, tempB.at(0).getC());
    }
    return 0;
}