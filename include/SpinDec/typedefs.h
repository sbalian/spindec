#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

// Seto Balian, Jul 28, 2015

#include "SpinDec/config.h"
#include <Eigen/Dense>

#include <complex>
#include <vector>

#include <string>
#include <iostream>

#include <memory>
#include <utility>
#include <map>

#include <boost/shared_ptr.hpp>

/** \file typedefs.h
 * \brief typedefs and "usings"
 * 
 * Custom STL and Eigen typedefs for SpinDec. Also includes some usings,
 * all in the SpinDec namespace.
 */
namespace SpinDec {

/// Unsigned int
typedef unsigned int UInt;

/// Real 3-vector
typedef Eigen::Vector3d ThreeVector;

/// Complex double
typedef std::complex<double> CDouble;

/// Matrix of complex doubles
typedef Eigen::MatrixXcd ComplexMatrix;

/// Vector of complex doubles
typedef Eigen::VectorXcd ComplexVector;

/// Vector of doubles
typedef Eigen::VectorXd RealVector;

/// STL vector of doubles
typedef std::vector<double> DoubleArray;

/// STL vector of integers
typedef std::vector<int> IntArray;

/// STL vector of unsigned integers
typedef std::vector<unsigned int> UIntArray;

/// STL vector of complex doubles
typedef std::vector< CDouble > CDoubleArray;


// using ...


/// STL string
using std::string;

/// Boost shared_ptr
using boost::shared_ptr;

/// STL cout
using std::cout;
/// STL endl
using std::endl;

/// STL pair
using std::pair;

/// STL vector
using std::vector;

/// STL map
using std::map;

}

#endif // TYPEDEFS_H_
