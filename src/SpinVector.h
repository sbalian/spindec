#ifndef SPINVECTOR_H_
#define	SPINVECTOR_H_

// SpinVector
//
// Multiple Spin container
//
// Seto Balian, Dec 5, 2013

#include "Spin.h"
#include <vector>

class SpinVector {
  
private:
  std::vector<Spin> spin_vector_;
  
public:
  SpinVector();
  SpinVector(const Spin & spin); // single Spin
  
  void push_back(const Spin & spin); // add element
  
  // TODO do [] operator to replace these ...
  Spin get_spin(const unsigned int index) const;
  void set_spin(const unsigned int index, const Spin & spin);
  
  unsigned int size() const; // number of Spins
  
  unsigned int get_multiplicity() const; // total spin multiplicity
  
};

#endif	 // SPINVECTOR_H_
