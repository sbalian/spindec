#ifndef TYPES_H_
#define TYPES_H_

// Custom built in typedefs, usings and consts for SpinDecoherence.
// All in the SpinDecoherence namespace.
// IMPORTANT: Do not include any SpinDecoherence classes here!
// TODO consts OK here?
//
// Seto Balian, Mar 3, 2014

#include <Eigen/Dense>
#include <complex>
#include <vector>
#include <string>
#include <iostream>

namespace SpinDecoherence {

// Real 3-vector
typedef Eigen::Vector3d d3vector;

// Complex double
typedef std::complex<double> cdouble;

// Matrix of complex doubles
typedef Eigen::MatrixXcd cdmatrix;

// Vector of complex doubles
typedef Eigen::VectorXcd cdvector;

// std vector of doubles
typedef std::vector<double> dvector;

// std vector of integers
typedef std::vector<int> ivector;

// std string
using std::string;

// std cout, endl
using std::cout;
using std::endl;

// plus and minus
const bool PLUS  = true;
const bool MINUS = false;
typedef bool sign; // PLUS (=1) or MINUS (=0)
inline double sign_to_double(const sign input)
{
  if (input==true) {
    return 1.0;
  } else {
    return -1.0;
  }
}

}

#endif // TYPES_H_
