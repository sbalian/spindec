#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// SpinInteractionEdge
//
// Edge for a spin interaction graph.
//
// Seto Balian, Mar 12, 2014

#include <utility>
#include "SpinDec/SpinInteractionVertex.h"
#include "SpinDec/SpinInteraction.h"
#include <memory>

namespace SpinDec
{

class SpinInteractionEdge
{
private:
  std::pair<SpinInteractionVertex,SpinInteractionVertex> vertices_;
  std::auto_ptr<SpinInteraction> interaction_;

public:
  SpinInteractionEdge();
  SpinInteractionEdge(const SpinInteractionEdge& other);
  SpinInteractionEdge(const SpinInteractionVertex& vertex1,
                      const SpinInteractionVertex& vertex2,
                      const std::auto_ptr<SpinInteraction>& interaction);
  
  const SpinInteractionVertex& get_vertex1() const;
  const SpinInteractionVertex& get_vertex2() const;
  std::auto_ptr<SpinInteraction> get_interaction() const;
  
  SpinInteractionEdge& operator=( const SpinInteractionEdge& other);

};

} // namespace SpinDec

#endif // SPININTERACTIONEDGE_H_
