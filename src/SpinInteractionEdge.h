#ifndef SPININTERACTIONEDGE_H_
#define SPININTERACTIONEDGE_H_

// SpinInteractionEdge
//
// Edge for a spin interaction graph.
// Holds the two labels for its vertices and the object for the interaction
// between the vertices.
//
// Seto Balian, Dec 6, 2013

#include <utility>
#include "SpinInteractionVertex.h"
#include "SpinInteraction.h"

class SpinInteractionEdge
{

private:

  std::pair<unsigned int,unsigned int> labels_;
  SpinInteraction* interaction_;
  
public:

  SpinInteractionEdge();
  SpinInteractionEdge(const unsigned int label1,
      const unsigned int label2,
      SpinInteraction* interaction);
  
  unsigned int get_label1() const;
  unsigned int get_label2() const;
  SpinInteraction* get_interaction() const;
  
  void set_label1(const unsigned int label1);
  void set_label2(const unsigned int label2);
  void set_interaction(SpinInteraction* interaction);
  
};

#endif // SPININTERACTIONEDGE_H_
