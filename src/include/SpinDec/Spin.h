#ifndef SPIN_H_
#define SPIN_H_

// Spin
//
// A single spin species.
// Contains spin parameters, state and spatial position in Angstroms.
//
// Seto Balian, Mar 25, 2014

#include "SpinDec/SpinParameters.h"
#include "SpinDec/SpinState.h"

#include <Eigen/Dense>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class Spin
{
protected:
  SpinParameters parameters_;
  SpinState state_;
  ThreeVector position_; // Angstroms
  
public:
  Spin();
  Spin(const SpinParameters& parameters,
      const ComplexVector& state_vector,
      const ThreeVector& position);
  const SpinParameters& get_parameters() const;
  const SpinState& get_state() const;
  const ThreeVector& get_position() const;
  
  void set_state(const ComplexVector& state_vector);
  
};

} // namespace SpinDec

#endif // SPIN_H_