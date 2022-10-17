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
#include <algorithm>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "contest.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

ofstream myfile; //allows to write to the output file
contest con; //default contestant
vector<contest> show; //extended heap
vector<contest> pos; //handle array
int sizeM; //max size of handle heap

bool findContestant(int id) //finds out if there is a contestant with the same ID in the game already in O(1)
{
    if (id < pos.size())
    {
        if (pos.at(id).getI() == id)
        {
            return true;
        }
    }
    return false;
}

bool compS(contest a, contest b) //used to fix location values
{
    return (a.getS() < b.getS());
}

void locFix() //fixes the location values
{
    int index = 1;
    sort(show.begin(), show.end(), compS);
    for (int i = 1; i < show.size(); i++)
    {
        if (show.at(i).getI() != -1)
        {
            show.at(i).setL(index);
            pos.at(show.at(i).getI()).setL(index);
            index++;
        }
    }
}

void insertContest(int id, int score) //inserts the contestants and resorts if the new contestant takes up the 
{
    if (findContestant(id) == false)
    {
        if (id <= sizeM)
        {
            if (con.read(id, score) && id <pos.size()){ //inserts an ID that was removed and wants to be added again
                show.insert(show.begin()+id,con);
                for(int i =id+1; i<show.size(); i++){
                    show.at(i).setL(show.at(i).getL()+1);
                    pos.at(show.at(i).getI()).setL(show.at(i).getL());
                }
                myfile << "Contestant <" << id << "> inserted with initial score <" << score << ">." << endl;
            }
            else if (con.read(id, score)) //inserts new id
            {
                show.push_back(con);
                pos.push_back(con);
                myfile << "Contestant <" << id << "> inserted with initial score <" << score << ">." << endl;
            }
            else 
            {
                myfile << "Contestant <" << id << "> could not be inserted because the extended heap is full." << endl;
            }
        }
        else //heap is full
        { 
            myfile << "Contestant <" << id << "> could not be inserted because the extended heap is full." << endl;
        }
    }
    else //id already exist
    {
        myfile << "Contestant <" << id << "> is already in the extended heap: cannot insert." << endl;
    }
}


void eliminateWeakest() //removes lowest score then fixes location values
{
    if (show.size() >= 2)
    {
        int minI = 1;
        for (int i = 1; i < show.size() - 1; i++)
        {
            if (show.at(minI).getS() > show.at(i + 1).getS())
            {
                minI = i + 1;
            }
        }
        myfile << "Contestant <" << minI << "> with current lowest score <" << pos.at(minI).getS() << "> eliminated." << endl;
        pos.at(show.at(minI).getI()).setI(-1);
        show.erase(show.begin() + minI);
        locFix();
    }
    else
    {
        myfile << "No contestant can be eliminated since the extended heap is empty." << endl;
    }
}

void earnPoints(int id, int score) //adds to contestant score and then fixes score locations
{
    if (id < sizeM) //valid id check
    {
        if (pos.at(id).getI() != -1) //valid id check
        {
            pos.at(id).setS(score);
            show.at(pos.at(id).getL()).setS(score);
            locFix();
            myfile << "Contestant <" << id << ">'s score increased by <" << score << "> points to <" << pos.at(id).getS() << ">." << endl;
        }
        else
        {
            myfile << "Contestant <" << id << "> is not in the extended heap." << endl;
        }
    }
    else
    {
        myfile << "Contestant <" << id << "> is not in the extended heap." << endl;
    }
}

void losePoints(int id, int score) //subtracts from contestant score and then fixes score locations
{
    if (id < sizeM) //valid id check
    {
        if (pos.at(id).getI() != -1) //valid id check
        {
            pos.at(id).setS(-1 * score);
            show.at(pos.at(id).getL()).setS(-1 * score);
            locFix();
            myfile << "Contestant <" << id << ">'s score decreased by <" << score << "> points to <" << pos.at(id).getS() << ">." << endl;
        }
        else
        {
            myfile << "Contestant <" << id << "> is not in the extended heap." << endl;
        }
    }
    else
    {
        myfile << "Contestant <" << id << "> is not in the extended heap." << endl;
    }
}

void showContestants() //shows all contestants and current ranking
{
    if (show.size() > 1) //non empty contestant list check
    {
        for (int i = 1; i < show.size(); i++)
        {
            if (show.at(i).getI() > 0)
            {
                myfile << "Contestant <" << show.at(i).getI() << "> in extended heap location <" << show.at(i).getL() << "> with score <" << show.at(i).getS() << ">." << endl;
            }
        }
    }
}

void showLocation(int id) //shows the current location/ranking of a contestant
{
    if (id < pos.size()) //valid id check
    {
        if (pos.at(id).getI() != -1)
        {
            myfile << "Contestant <" << id << "> stored in extended heap location <" << pos.at(id).getL() << ">." << endl;
        }
        else
        {
            myfile << "There is no Contestant <" << id << "> in the extended heap: handle[<" << id << ">] = -1." << endl;
        }
    }
    else
    {
        myfile << "There is no Contestant <" << id << "> in the extended heap: handle[<" << id << ">] = -1." << endl;
    }
}

void showHandles() //shows the status of all contestant IDs up to the given max
{
    for (int i = 1; i < pos.size(); i++) //shows the status of all IDs up to the max in the handle array
    {
        showLocation(i);
    }
    if (pos.size() - 1 < sizeM) //checks to see if the handle array reached max capacity 
    {
        for (int i = pos.size(); i <= sizeM; i++) //if not then shows the status of unused IDs
        {
            myfile << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i << ">] = -1." << endl;
        }
    }
}

void crownWinner() //removes all the contestants other than the highest scoring one
{
    locFix();
    int length = show.size();
    while (length != 1) //loop to delete the lowest score till 1 element is left
    {
        show.erase(show.begin());
        length--;
    }
    myfile << "Contestant <" << show.at(0).getI() << "> wins with score <" << show.at(0).getS() << ">!";
}

bool fileOpen(string file, ifstream &fileObj) //opens the desired file
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

void readFile(string file, ifstream &fileObj, string output) //reads in the input file and runs given commands
{
    bool ran = false;
    myfile.open(output); //opens the output file
    string line;
    while (getline(fileObj, line))
    {
        string id = "";
        string score = "";
        string command = "";
        stringstream ss(line);
        getline(ss, command, ' ');
        getline(ss, id, ' ');
        getline(ss, score, ' ');
        //processes all given commands line by line
        if (ran == false)
        {
            sizeM = stoi(command);
            ran = true;
        }
        else if (command.find("insertContestant") != string::npos)
        {
            myfile << command << " " << id << " " << score << endl;
            id = id.substr(1, 2);
            score = score.substr(1, 2);
            insertContest(stoi(id), stoi(score));
        }
        else if (command.find("findContestant") != string::npos)
        {
            myfile << command << " " << id << endl;
            id = id.substr(1, 1);
            if (findContestant(stoi(id)))
            {
                myfile << "Contestant <" << id << "> is in the extended heap with score <" << pos.at(stoi(id)).getS() << ">." << endl;
            }
            else
            {
                myfile << "Contestant <" << id << "> is not in the extended heap." << endl;
            }
        }
        else if (command.find("losePoints") != string::npos)
        {
            myfile << command << " " << id << " " << score << endl;
            id = id.substr(1, 2);
            score = score.substr(1, 2);
            losePoints(stoi(id), stoi(score));
        }

        else if (command.find("earnPoints") != string::npos)
        {
            myfile << command << " " << id << " " << score << endl;
            id = id.substr(1, 2);
            score = score.substr(1, 2);
            earnPoints(stoi(id), stoi(score));
        }
        else if (command.find("eliminateWeakest") != string::npos)
        {
            myfile << "eliminateWeakest" << endl;
            eliminateWeakest();
        }
        else if (command.find("showContestants") != string::npos)
        {
            myfile << "showContestants" << endl;
            showContestants();
        }
        else if (command.find("showHandles") != string::npos)
        {
            myfile << "showHandles" << endl;
            showHandles();
        }
        else if (command.find("showLocation") != string::npos)
        {
            myfile << "showLocation " << id << endl;
            id = id.substr(1, 2);
            showLocation(stoi(id));
        }
        else if (command.find("crownWinner") != string::npos)
        {
            myfile << "crownWinner" << endl;
            crownWinner();
        }
    }
}

int main(int argc, char *argv[])
{
    ifstream fin;
    char commands;
    string input = "default";
    string output = "default";
    show.push_back(con); //fills index 0
    pos.push_back(con); //fills index 0
    input = argv[1]; //gets input file name
    output = argv[2]; //gets output file name
    if (fileOpen(input, fin)) //opens input file
    {
        readFile(input, fin, output); //reads in input file
        fin.close(); //closes input file
    }
}