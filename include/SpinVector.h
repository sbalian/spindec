#ifndef SPINVECTOR_H
#define	SPINVECTOR_H

// SpinVector
//
// Multiple Spin container
//
// Seto Balian, December 2, 2013

#include "Spin.h"
#include <vector>
//#include <boost/ptr_container/ptr_vector.hpp>
// @todo use this and make data members of Spin constant again?                                               

class SpinVector {
  
private:
  std::vector<Spin> spin_vector_;
  
public:
  SpinVector();
  SpinVector(const Spin & spin); // single Spin
  
  void push_back(const Spin & spin); // add element
  
  // @todo do [] operator to replace these ...
  // @todo also, return Type& for speed?
  Spin get_spin(const unsigned int index) const;
  void set_spin(const unsigned int index, const Spin & spin);
  
  // Spin& operator[] (const unsigned int index) const; // get and set element
  
  unsigned int size() const; // number of Spins
  
  unsigned int get_multiplicity() const; // total spin multiplicity
  
};

#endif	 // SPINVECTOR_H
