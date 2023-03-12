/*
 *  syso.cpp
 *  Zak Rizvi
 *  March 10, 2023
 *
 *  This file reads in the data from a file and averages out
 *  the hourly data by the day. It outputs these results in a
 *  user provided output file.
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
    //Creates an ofstream for the output file and opens it
    ofstream outfile;
    openOrDie(outfile, argv[2]);
    //Variable declarations
    string temp1, temp2;
    double total = 0;
    double current, average;
    //Starts read in loop, going by days
    for (int q = 0; q < 33; q++)
    {
        //Breaks down hours
        for (int i = 0; i < 24; i++)
        {
            //Breaks down by 5 minute intervals
            for (int j = 0; j < 12; j++)
            {
                //Reads in from the file skipping over null data
                infile >> temp1 >> temp2 >> current;
                //If this is the first time reading from this date,
                //outfiles the date to the output file
                if ( i == 0 and j == 0)
                {
                    outfile << temp1 << "   ";
                }
                //Adds the current read in value to the total
                total += current;
            }
            //Stores the average value by hour
            average = total/12;
            //Outputs this value
            outfile << average << " ";
            //Resets the total so it can be reused
            total = 0; 
        }
        //Creates a seperate line for the next day
        outfile << endl;
    }
    //Closes the input and output file
    infile.close();
    outfile.close();
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
        cerr << "Usage: " << argv[0] << " inputFile outputFile ";
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