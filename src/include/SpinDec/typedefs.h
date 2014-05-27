#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

// SpinDec::typedefs
//
// Custom STL and Eigen typedefs for SpinDec.
// Also includes some usings ...
// All in the SpinDec namespace.
//
// Seto Balian, May 27, 2014

#include <Eigen/Dense>

#include <complex>
#include <vector>

#include <string>
#include <iostream>

#include <memory>
#include <utility>

namespace SpinDec {

// unsigned int
typedef unsigned int UInt;

// Real 3-vector
typedef Eigen::Vector3d ThreeVector;

// Complex double
typedef std::complex<double> CDouble;

// Matrix of complex doubles
typedef Eigen::MatrixXcd ComplexMatrix;

// Vector of complex doubles
typedef Eigen::VectorXcd ComplexVector;

// Vector of doubles
typedef Eigen::VectorXd RealVector;

// std vector of doubles
typedef std::vector<double> DoubleArray;

// std vector of integers
typedef std::vector<int> IntArray;

// std vector of unsigned integers
typedef std::vector<unsigned int> UIntArray;

// std vector of complex doubles
typedef std::vector< CDouble > CDoubleArray;

// using ...
// std string
using std::string;

// std auto_ptr
using std::auto_ptr;

// std cout, endl
using std::cout;
using std::endl;

// std pair
using std::pair;

// std vector
using std::vector;

}

#endif // TYPEDEFS_H_
