#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// Vertex for a spin interaction graph. Contains a label, a spin, a position
// in real space and a spin state.
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/Spin.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

class SpinInteractionVertex
{
private:
  UInt label_;
  Spin spin_;
  ThreeVector position_;
  SpinState state_;
  
public:
  SpinInteractionVertex();
  SpinInteractionVertex(const UInt label, const Spin& spin,
      const ThreeVector & position, const SpinState & state);
  
  UInt get_label() const;
  const Spin& get_spin() const;
  const ThreeVector& get_position() const;
  const SpinState& get_state() const;
  
};

} // namespace SpinDec

#endif // SPININTERACTIONVERTEX_H_
