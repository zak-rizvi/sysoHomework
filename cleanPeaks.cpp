/*
 *  syso.cpp
 *  Zak Rizvi
 *  March 10, 2023
 *
 *  This file reads in the Clean Peaks Data
 *  and outputs to terminal an integer representing
 *  the number of MW outputted during "peaks".
 *
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Function declarations
void errorChecker(int argc, char *argv[]);
template<typename streamtype>
void openOrDie(streamtype &stream, std::string filename);

//name: main
//purpose: Executes the program
//arguments: Argument counter and an array of their names
//returns: An integer zero if program is succesfully finished
//effects: Outputs the formatted data to the output file
int main(int argc, char *argv[])
{
    //Checks for correct amount of file provided
    errorChecker(argc, argv);
    //Creates an ifstream for the stations file and opens it
    ifstream infile;
    openOrDie(infile, argv[1]);
    //Output file
    ofstream outfile;
    openOrDie(outfile, argv[2]);
    //Variable declarations
    string day, time;
    double spring = 0;
    double summer = 0;
    double current;
    double daily = 0;
    //Starts read in loop, going by days
    for (int i = 0; i < 336; i++)
    {
        infile >> day >> time >> current;
        if (time == "17:00" or time == "18:00" or time == "19:00" or
        time == "20:00")
        {
            daily += current;
            spring += current;
        }
        if (time == "21:00")
        {
            outfile << day << " " << daily/1000 << endl;
            daily = 0;
        }
    }
    for (int i = 0; i < 408; i++)
    {
        infile >> day >> time >> current;
        if (time == "15:00" or time == "16:00" or time == "17:00" or time 
        == "18:00")
        {
           daily += current;
           summer += current;
        }
        if (time == "19:00")
        {
            outfile << day << " " << (daily * 4)/1000 << endl;
            daily = 0;
        }
    }
    cout << 0.3 * ((spring/1000) + ((summer * 4)/1000)) << endl;
    //Closes the input and output file
    infile.close();
    return 0;
}

//name: errorChecker
//purpose: Checks if the correct amount of files have been provided
//arguments: Argument counter and an array of their names
//returns: None
//effects: Outputs an error message if not correct amount of files
void errorChecker(int argc, char *argv[])
{
    //Checks that the correct amount of arguments have been provided
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " inputFile outputFile";
        exit(EXIT_FAILURE);
    }
}

//name: openOrDie
//purpose: Opens a file and checks if it was opened correctly
//arguments: A streamtype and a filename
//returns: None
//effects: Opens a file and exits the program if file was not opened
template<typename streamtype>
void openOrDie(streamtype &stream, std::string filename)
{
    //Opens file
    stream.open(filename);
    //If file could not be opened, leaves with EXIT_FAILURE
    if (not stream.is_open())
    {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
}