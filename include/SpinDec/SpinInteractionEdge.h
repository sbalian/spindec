#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/SpinInteraction.h"

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * \brief Edge for a spin interaction graph.
 * 
 * Contains a pair of vertex labels and a spin interaction.
 * 
 */
class SpinInteractionEdge
{
private:
  pair<UInt,UInt> labels_;
  shared_ptr<SpinInteraction> interaction_;

public:
  SpinInteractionEdge();
  SpinInteractionEdge(const SpinInteractionEdge& other);
  SpinInteractionEdge(const UInt label1,
                      const UInt label2,
                      const shared_ptr<SpinInteraction>& interaction);
  
  UInt get_label1() const;
  UInt get_label2() const;
  shared_ptr<SpinInteraction> get_interaction() const;
  
  SpinInteractionEdge& operator=( const SpinInteractionEdge& other);

};

} // namespace SpinDec

#endif // SPININTERACTIONEDGE_H_
