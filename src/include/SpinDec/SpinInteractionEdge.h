#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// SpinDec::SpinInteractionEdge
//
// Edge for a spin interaction graph. Contains a pair of vertices and
// a spin interaction.
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinInteractionVertex.h"
#include "SpinDec/SpinInteraction.h"

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class SpinInteractionEdge
{
private:
  pair<SpinInteractionVertex,SpinInteractionVertex> vertices_;
  auto_ptr<SpinInteraction> interaction_;

public:
  SpinInteractionEdge();
  SpinInteractionEdge(const SpinInteractionEdge& other);
  SpinInteractionEdge(const SpinInteractionVertex& vertex1,
                      const SpinInteractionVertex& vertex2,
                      const auto_ptr<SpinInteraction>& interaction);
  
  const SpinInteractionVertex& get_vertex1() const;
  const SpinInteractionVertex& get_vertex2() const;
  auto_ptr<SpinInteraction> get_interaction() const;
  
  SpinInteractionEdge& operator=( const SpinInteractionEdge& other);

};

} // namespace SpinDec

#endif // SPININTERACTIONEDGE_H_
