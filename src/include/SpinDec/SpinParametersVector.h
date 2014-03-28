#ifndef SPINPARAMETERSVECTOR_H_
#define	SPINPARAMETERSVECTOR_H_

// SpinDec::SpinParametersVector
//
// Multiple SpinParameters container
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinParameters.h"
#include "SpinDec/typedefs.h"

#include <vector>

namespace SpinDec
{

class SpinParametersVector {
  
private:
  std::vector<SpinParameters> spin_parameters_vector_;
  
public:
  SpinParametersVector();
  explicit SpinParametersVector(const SpinParameters & spin_parameters);
  // single SpinParameters object
  
  void push_back(const SpinParameters & spin_parameters); // add element
  
  // Get and set like std::vector
  SpinParameters& operator[](const UInt index);
  const SpinParameters& operator[](const UInt index) const;
  
  UInt size() const; // number of spin parameter objects
  void clear();
  
  UInt multiplicity() const; // total spin multiplicity
  
};

} // namespace SpinDec

#endif  // SPINPARAMETERSVECTOR_H_
