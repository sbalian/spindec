#ifndef SPINHALFSTATES_H_
#define SPINHALFSTATES_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinHalfParameters.h"

namespace SpinDec
{

/// Spin-1/2 spin states.
class SpinHalfStates : public SpinState
{
protected:
  
  /// Basis is (0.5,-0.5).
  SpinHalfStates(); 
  
  /**
   * Depending on sign of gyromagnetic_ratio, spin up or spin down.
   * See derived classes SpinUp and SpinDown.
   */ 
  virtual void init(const double gyromagnetic_ratio) = 0;
  
  // All these not allowed TODO any other way of doing this?
  virtual void set_state_vector(const ComplexVector & state_vector);
  virtual void set_element(const UInt index,
      const CDouble& element);
  virtual void set_element(const UInt index,
        const double element);
  
  virtual ~SpinHalfStates();

};

} // namespace SpinDec

#endif // SPINHALFSTATES_H_
