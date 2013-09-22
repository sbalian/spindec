// Given a text file with columns 0, 1, 2, ... n
// this program computes the mean and standard deviation
// on the mean of columns 1 - n, for each row, leaving
// column zero intact.
// This is used for column 0 = time, columns 1 to n
// spin echo intensities for random spatial configurations of the bath,
// as outputed from the donornucbath programs.
//
// Created  03/10/2012
// Modified 11/12/2012, 12/12/2012
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "ft.hpp"

using namespace std;

void args_error () {
  cout << "ERROR: Invalid number of arguments to 'process_raw_donornucbath'" << endl;
  cout << "USAGE: process_raw_donornucbath infilename" << endl;
  cout << "       process_raw_donornucbath infilename printoption" << endl;
  cout << "       process_raw_donornucbath infilename printoption outfilename" << endl;
  cout << "Default printoption is \"abs\"" << endl;
  cout << "Seto Balian - 11/12/2012 - V1" << endl;
  return;
}

int main (int argc, char **argv) {

  // get command line arguments (see USAGE above)
  string infilename;
  string outfilename;
  string print_option = "abs";
  switch(argc)
  {
    case 2:
      infilename  = argv[1];
      outfilename = "proc_" + infilename;
      break;
    case 3:
      infilename    = argv[1];
      outfilename   = "proc_" + infilename;
      print_option  = argv[2];
      break;
    case 4:
      infilename    = argv[1];
      outfilename   = "proc_" + infilename;
      print_option  = argv[2];
      outfilename   = argv[3];

    default:
      args_error();
      return 0;
  }

  // read file
  ft ft_in = ft::read(infilename);

  // ft_in.print(8,"cmplx");


  // calculate the mean
  ft ft_in_mean = ft_in.mean_f();

  // calculate the standard deviation on the mean
  ft ft_in_stdev_mean = ft_in.stdev_mean_f();
  
  // prepare to print
  ft ft_out = ft ( ft_in.get_t() , 2 );
  ft_out.set_f (0,ft_in_mean.get_f(0));
  ft_out.set_f (1,ft_in_stdev_mean.get_f(0));

  ft_out.print(8,outfilename,print_option);

  return 0;
  
}

