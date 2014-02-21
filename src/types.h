#ifndef TYPES_H_
#define TYPES_H_

// Custom built in types for SpinDecoherence.
// IMPORTANT: Do not include any SpinDecoherence classes here!
//
// Seto Balian, Feb 21, 2014

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

// std string
using std::string;

// std cout, endl
using std::cout;
using std::endl;

}

#endif // TYPES_H_
