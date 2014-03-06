#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// SpinInteractionEdge
//
// Edge for a spin interaction graph.
//
// Seto Balian, Mar 6, 2014

#include <utility>
#include "SpinDec/SpinInteractionVertex.h"
#include "SpinDec/SpinInteraction.h"

namespace SpinDec
{

class SpinInteractionEdge
{
private:
  std::pair<SpinInteractionVertex,SpinInteractionVertex> vertices_;
  SpinInteraction* interaction_;
  
public:
  SpinInteractionEdge();
  SpinInteractionEdge(const SpinInteractionVertex& vertex1,
                      const SpinInteractionVertex& vertex2,
                      SpinInteraction* interaction);
  
  const SpinInteractionVertex& get_vertex1() const;
  const SpinInteractionVertex& get_vertex2() const;
  SpinInteraction* get_interaction() const;
  
};

} // namespace SpinDec

#endif // SPININTERACTIONEDGE_H_
