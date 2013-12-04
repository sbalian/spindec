#ifndef SINGLESPINBASIS_H_
#define	SINGLESPINBASIS_H_

// SingleSpinBasis
//
// Basis for a single spin.
//
// Seto Balian, Dec 4, 2013

#include "SpinBasis.h"

class SingleSpinBasis : public SpinBasis
{

private:

  void build(const Spin & spin); // build using multiplicity
    
public:

  SingleSpinBasis(); // null
  SingleSpinBasis(const Spin & spin); // uses multiplicity to build basis
                                       // automatically
  
  SingleSpinBasis(const Eigen::ArrayXd & basis); // custom build
  
  virtual unsigned int num_spins() const;
  
  double get_element(const unsigned int index) const;
  
  virtual ~SingleSpinBasis();

};

#endif	 // SINGLESPINBASIS_H_
