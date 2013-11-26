#ifndef SINGLESPINZEEMANBASIS_H
#define	SINGLESPINZEEMANBASIS_H

// SingleSpinZeemanBasis
//
// Zeeman basis for a single spin.
//
// Seto Balian, November 26, 2013

#include "ZeemanBasis.h"

class SingleSpinZeemanBasis : public ZeemanBasis
{
public:
  
  SingleSpinZeemanBasis(); // clear() in constructor ensures this is 1D

  // add magnetic quantum number
  void add_magnetic_quantum_number(const double magnetic_quantum_number);
  
  void build(const unsigned int multiplicity,
             const double spin_quantum_number); // using multiplicity

  // like tensor product,
  // for example, SingleSpinZeemanBasis.combine(ZeemanBasis)
  // SingleSpinZeemanBasis = 0.5
  //                        -0.5
  //              ZeemanBasis = 4.5
  //                           -4.5
  // ZeemanBasis changes to
  //                      4.5  0.5
  //                     -4.5 -0.5
  //                      4.5  0.5
  //                     -4.5 -0.5
  void combine(ZeemanBasis & basis) const;
  
  void clear(); // set ZeemanBasis::basis_ to zero length 1D array

};

#endif	 // SINGLESPINZEEMANBASIS_H
