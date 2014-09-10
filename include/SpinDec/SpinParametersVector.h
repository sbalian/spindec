#ifndef SPINPARAMETERSVECTOR_H_
#define	SPINPARAMETERSVECTOR_H_

// SpinDec::SpinParametersVector
//
// Multiple SpinParameters container
//
// Seto Balian, Apr 1, 2014

#include "SpinDec/SpinParameters.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

class SpinParametersVector {
  
private:
  std::vector<SpinParameters> spin_parameters_vector_;
  
public:
  
  SpinParametersVector();
  
  // First element set
  explicit SpinParametersVector(const SpinParameters & spin_parameters);
    
  // Get and set like std::vector
  SpinParameters& operator[](const UInt index);
  const SpinParameters& operator[](const UInt index) const;
  
  // Add element
  void push_back(const SpinParameters & spin_parameters);
  
  // number of SpinParameter objects
  UInt size() const;
  
  // clear the std::vector data member
  void clear();
  
  // Total spin multiplicity = product of individual multiplicities
  UInt multiplicity() const;
  
};

} // namespace SpinDec

#endif  // SPINPARAMETERSVECTOR_H_
