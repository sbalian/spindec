#ifndef ZEEMANBASIS_H
#define ZEEMANBASIS_H

// ZeemanBasis
//
// Holds magnetic quantum numbers (Zeeman basis) for a single spin or multiple
// spins.
//
// Seto Balian, November 27, 2013

#include <Eigen/Dense>
#include <vector>

class ZeemanBasis
{
  Eigen::Array basis_;
  // Stores magnetic quantum numbers for multiple spins
  // Columns: spins
  // Rows: magnetic quantum numbers
  // For example, for 2 electrons, this can be
  //                  0.5  0.5 -> |0.5,0.5>
  //                  0.5 -0.5
  //                 -0.5  0.5
  //                 -0.5 -0.5

public:
  
  virtual ZeemanBasis join(const ZeemanBasis & operand) = 0;
  // For example, ZeemanBasis B1 = 0.5
  //                              -0.5
  // ZeemanBasis B2 = 4.5
  //                 -4.5
  // B1.join(B2) gives 0.5  4.5
  //                  -0.5 -4.5

  
  // Number of basis states
  virtual unsigned int dimension() const;
  
  // Number of spins
  virtual unsigned int num_spins() const = 0;
  
  // Clear the basis
  void clear() = 0;
  
  // quickly build the basis using the multiplicites of spins
  void build(const std::vector<double> & spin_quantum_numbers);
  
  // Suppose basis is |m0, m1, m2> with m1=m2=m3=+/-0.5.
  // For example, given indices (0,1) and a to_keep array, 0.5 -0.5
  //                                                      -0.5  0.5
  // This truncates the original basis (of dimension 8) to
  //  0.5 -0.5  0.5
  //  0.5 -0.5 -0.5
  // -0.5  0.5  0.5
  // -0.5  0.5 -0.5
  void truncate(const std::vector<unsigned int> & spin_indices,
                     const Eigen::ArrayXXd & to_keep);
  
  virtual ~ZeemanBasis();
  
};

#endif // ZEEMANBASIS_H
