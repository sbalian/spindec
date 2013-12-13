#ifndef SPININTERACTIONEDGECONTENTS_H_
#define SPININTERACTIONEDGECONTENTS_H_

// SpinInteractionEdgeContents
//
// Edge contents for a spin interaction graph.
//
// Seto Balian, Dec 13, 2013

#include "EdgeContents.h"
#include "SpinInteraction.h"

class SpinInteractionEdgeContents : public EdgeContents
{
private:
  SpinInteraction* interaction_;
  
public:
  
  SpinInteractionEdgeContents();
  SpinInteractionEdgeContents(SpinInteraction* interaction);

  SpinInteraction* get_interaction() const;
  
};

#endif // SPININTERACTIONEDGECONTENTS_H_
