#ifndef SPINVECTOR_H_
#define	SPINVECTOR_H_

// SpinVector
//
// Multiple Spin container
//
// Seto Balian, Dec 4, 2013

#include "Spin.h"
#include <vector>

//#include <boost/ptr_container/ptr_vector.hpp>
// TODO use this and make data members of Spin constant again?

class SpinVector {
  
private:
  std::vector<Spin> spin_vector_;
  
public:
  SpinVector(); // null
  SpinVector(const Spin & spin); // single Spin
  
  void push_back(const Spin & spin); // add element
  
  // TODO do [] operator to replace these ...
  // TODO also, return Type& for speed?
  Spin get_spin(const unsigned int index) const;
  void set_spin(const unsigned int index, const Spin & spin);
  
  // Spin& operator[] (const unsigned int index) const; // get and set element
  
  unsigned int size() const; // number of Spins
  
  unsigned int get_multiplicity() const; // total spin multiplicity
  
};

#endif	 // SPINVECTOR_H_
