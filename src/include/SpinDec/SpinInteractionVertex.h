#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// Vertex for a spin interaction graph. Contains a label, spin parameters,
// spin state and a position in real space.
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinParameters.h"
#include "SpinDec/typedefs.h"

#include "SpinDec/SpinState.h"

namespace SpinDec
{

class SpinInteractionVertex
{
private:
  UInt label_;
  
  SpinParameters spin_parameters_;
  SpinState state_;
  ThreeVector position_;
  
public:
  SpinInteractionVertex();
  SpinInteractionVertex(const UInt label,
                        const SpinParameters& spin_parameters,
                        const SpinState& state,
                        const ThreeVector & position);
  
  UInt get_label() const;
 
  const SpinParameters& get_spin_parameters() const;
  const SpinState& get_state() const;
  const ThreeVector& get_position() const;
  
};

} // namespace SpinDec

#endif // SPININTERACTIONVERTEX_H_
