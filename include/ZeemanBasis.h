#ifndef ZEEMANBASIS_H
#define ZEEMANBASIS_H

// ZeemanBasis
//
// Holds magnetic quantum numbers (Zeeman basis).
//
// Seto Balian, November 26, 2013

#include <Eigen/Dense>
#include <vector>
#include "Named.h"

class ZeemanBasis : public Named
{

private:
  Eigen::ArrayXXd basis_; // Zeeman basis.
                          // cols -> spin slots
                          // rows -> product states,
                          // e.g. for 2 electrons,
                          // this can be   0.5  0.5
                          //               0.5 -0.5
                          //              -0.5  0.5
                          //              -0.5 -0.5
                          // ie {|e>} = {|m_S_1 , m_S_2 >}

public:

  ZeemanBasis();
  ZeemanBasis(const Eigen::ArrayXXd & basis);
  
  Eigen::ArrayXXd get_basis() const;
  void set_basis(const Eigen::ArrayXXd & basis);
    
  // for example, ZeemanBasis B1 = 0.5
  //                              -0.5
  // ZeemanBasis B2 = 4.5
  //                 -4.5
  // B1.append(B2) changes B1 to 0.5  4.5
  //                            -0.5 -4.5
  void append(const ZeemanBasis & to_append);
  
  // this is the rows of basis_
  unsigned int dimension() const;
  
  // this is the cols of basis_
  unsigned int num_spins() const;
  
  void clear(); // set ZeemanBasis::basis_ to zero dimension 2D array
  
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
  
};

#endif // ZEEMANBASIS_H
