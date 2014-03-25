#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// Vertex for a spin interaction graph. Contains a label, spin parameters,
// and a position in real space.
//
// Seto Balian, Mar 25, 2014

#include "SpinDec/SpinParameters.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

class SpinInteractionVertex
{
private:
  UInt label_;
  SpinParameters spin_parameters_;
  ThreeVector position_;
  
public:
  SpinInteractionVertex();
  SpinInteractionVertex(const UInt label, const SpinParameters& spin_parameters,
      const ThreeVector & position);
  
  UInt get_label() const;
  const SpinParameters& get_spin_parameters() const;
  const ThreeVector& get_position() const;
  
};

} // namespace SpinDec

#endif // SPININTERACTIONVERTEX_H_
