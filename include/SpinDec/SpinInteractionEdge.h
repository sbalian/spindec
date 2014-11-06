#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// SpinDec::SpinInteractionEdge
//
// Edge for a spin interaction graph. Contains a pair of vertex labels and
// a spin interaction.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/SpinInteraction.h"

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class SpinInteractionEdge
{
private:
  pair<UInt,UInt> labels_;
  auto_ptr<SpinInteraction> interaction_;

public:
  SpinInteractionEdge();
  SpinInteractionEdge(const SpinInteractionEdge& other);
  SpinInteractionEdge(const UInt label1,
                      const UInt label2,
                      const auto_ptr<SpinInteraction>& interaction);
  
  UInt get_label1() const;
  UInt get_label2() const;
  auto_ptr<SpinInteraction> get_interaction() const;
  
  SpinInteractionEdge& operator=( const SpinInteractionEdge& other);

};

} // namespace SpinDec

#endif // SPININTERACTIONEDGE_H_
