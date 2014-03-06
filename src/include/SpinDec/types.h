#ifndef TYPES_H_
#define TYPES_H_

// Custom built in typedefs, usings and consts for SpinDec.
// All in the SpinDec namespace.
// IMPORTANT: Do not include any SpinDec classes here!
// TODO consts OK here?
//
// Seto Balian, Mar 6, 2014

#include <Eigen/Dense>
#include <complex>
#include <vector>
#include <string>
#include <iostream>

namespace SpinDec {

// Real 3-vector
typedef Eigen::Vector3d ThreeVector;

// Complex double
typedef std::complex<double> cdouble;

// Matrix of complex doubles
typedef Eigen::MatrixXcd ComplexMatrix;

// Vector of complex doubles
typedef Eigen::VectorXcd ComplexVector;

// std vector of doubles
typedef std::vector<double> dvector;

// std vector of integers
typedef std::vector<int> ivector;

// std vector of unsigned integers
typedef std::vector<unsigned int> uivector;

// std vector of complex doubles
typedef std::vector< cdouble > cdvector;

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
