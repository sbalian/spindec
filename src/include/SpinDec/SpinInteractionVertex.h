#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinDec::SpinInteractionVertex
//
// Vertex for a spin interaction graph. Contains a label, spin parameters, a
// spin basis and a position in real space.
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinParameters.h"
#include "SpinDec/typedefs.h"

#include "SpinDec/SpinBasis.h"

namespace SpinDec
{

class SpinInteractionVertex
{
private:
  UInt label_;
  
  SpinParameters spin_parameters_;
  SpinBasis basis_;
  ThreeVector position_;
  
public:
  SpinInteractionVertex();
  
  SpinInteractionVertex(const UInt label,
                        const SpinParameters& spin_parameters,
                        const ThreeVector & position); // Zeeman basis built
                                                       // from spin parameters
  
  SpinInteractionVertex(const UInt label,
                        const SpinParameters& spin_parameters,
                        const SpinBasis& basis,
                        const ThreeVector & position);
  
  UInt get_label() const;
 
  const SpinParameters& get_spin_parameters() const;
  const SpinBasis& get_basis() const;
  const ThreeVector& get_position() const;

};

} // namespace SpinDec

#endif // SPININTERACTIONVERTEX_H_
