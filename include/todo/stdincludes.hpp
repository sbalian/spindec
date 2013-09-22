#ifndef STDINCLUDES_H
#define STDINCLUDES_H

// Standard includes, typedefs, structs
//
// Created  04/09/2012
// Modified 19/09/2012, 20/09/2012, 21/09/2012, 30/09/2012, 02/10/2012,
// 06/10/2012, 07/10/2012, 08/10/2012
// Seto Balian
// V1

using namespace std;

// C/C++ includes
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
#include <complex>
#include <algorithm>
#include <time.h>
#include <utility>
#include <map>
#include <sstream>

// Physical and mathematical constants
#include "constants.hpp"

#include "named.hpp"

// #define EIGEN_USE_MKL_ALL

// Matrix algebra package
#include <Eigen/Dense>     // Eigen: Linear algebra package:
                           // Vectors, matrices and eigensolvers.
                           // v3.1.1

// Complex numbers
typedef complex<double> cmplxd;

// Double vectors
typedef vector<double> darray;

// Int vectors
typedef vector<int> iarray;

// Fractions
struct _frac {
  int num;
  int den;
} ;
typedef struct _frac frac;

// Double triplet
struct _doubleTriplet {
  double d_1;
  double d_2;
  double d_3;
} ;
typedef struct _doubleTriplet doubleTriplet;

// Maps for read profile
typedef map<string,double> map_string_double;
typedef map<string,int> map_string_int;
typedef map<string,bool> map_string_bool;
typedef map<string,string> map_string_string;
typedef map<string,frac> map_string_frac;
typedef map<string,doubleTriplet> map_string_doubleTriplet;

// For zheev routine
// Complex datatype NOTE: INTEL
struct _MKL_Complex16 { double real, imag; };
typedef struct _MKL_Complex16 MKL_Complex16;
// zheev prototype NOTE: INTEL, added "C"
extern "C" void zheev_(const char* jobz,const char* uplo, int* n, MKL_Complex16* a,
  int* lda, double* w, MKL_Complex16* work, int* lwork, double* rwork, int* info );

#endif // STDINCLUDES_H

