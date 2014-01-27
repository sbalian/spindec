#ifndef SPINVECTOR_H_
#define	SPINVECTOR_H_

// SpinVector
//
// Multiple Spin container
//
// Seto Balian, Jan 22, 2014

#include "Spin.h"
#include <vector>

class SpinVector {
  
private:
  std::vector<Spin> spin_vector_;
  
public:
  SpinVector();
  SpinVector(const Spin & spin); // single Spin
  
  void push_back(const Spin & spin); // add element
  
  // Get and set like std::vector
  Spin& operator[](const unsigned int index);
  Spin& operator[](const unsigned int index) const;
  
  unsigned int size() const; // number of Spins
  void clear();
  
  unsigned int get_multiplicity() const; // total spin multiplicity
  
};

#endif	 // SPINVECTOR_H_
