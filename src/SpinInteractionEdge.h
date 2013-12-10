#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// SpinInteractionEdge
//
// Edge for a spin interaction graph.
// For the interaction between the vertices.
//
// Seto Balian, Dec 10, 2013

#include "SpinInteraction.h"
#include "Edge.h"

class SpinInteractionEdge : public Edge
{

private:

  SpinInteraction* interaction_;

public:

  SpinInteractionEdge();
  SpinInteractionEdge(const unsigned int label1,
      const unsigned int label2,
      SpinInteraction* interaction);
  
  SpinInteraction* get_interaction() const;
  
};

#endif // SPININTERACTIONEDGE_H_
