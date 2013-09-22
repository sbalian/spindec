// Created 19/02/2013 V1
// Seto Balian

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {

// Read command line parameters
if (argc != 2) { // argument count = 2, including the executable name
  cout << "memoryTime" << endl;
  cout << "------------" << endl;
  cout << "Given a two column data file, COL1: time, COL2: echo, " << endl; 
  cout << "reports the value of time when echo is just < (initial echo)/e." << endl;
  cout << "------------" << endl;
  cout << "USAGE: memoryTime infilename" << endl;
  cout << "------------" << endl;
  cout << "Seto Balian - 19/02/2013 - V1" << endl;
  return 1;
}

// get input file name
string input_file_name = argv[1];

// Read from file

// start input file stream
ifstream infile(input_file_name.c_str());

double time, initial_echo, echo;

cout << scientific << setprecision(12) << left;

infile >> time;
infile >> initial_echo;
cout << "Initial echo is " << initial_echo << endl;

while(true) {

infile >> time;
infile >> echo;

if ( echo < (initial_echo/exp(1.0))) {
  cout << "Memory time is " << time << endl;
  infile.close();
  return 0;
}

}

return 0;


}
