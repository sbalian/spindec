#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// Vertex for a spin interaction graph. Contains a label and a spin.
//
// Seto Balian, Mar 6, 2014

#include "SpinDec/Spin.h"

namespace SpinDec
{

class SpinInteractionVertex
{
private:
  unsigned int label_;
  Spin spin_;
  
public:
  SpinInteractionVertex();
  SpinInteractionVertex(const unsigned int label, const Spin& spin);
  
  unsigned int get_label() const;
  const Spin& get_spin() const;
  
  void set_spin(const Spin& spin);
  
};

} // namespace SpinDec

#endif // SPININTERACTIONVERTEX_H_
