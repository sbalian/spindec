#ifndef SPININTERACTIONVERTEX_H
#define SPININTERACTIONVERTEX_H

// SpinInteractionVertex
//
// Interaction between a pair of nodes each containing one Spin.
// Holds the strength of the interaction.
//
// Seto Balian 01/11/2013

#include "SpinInteractionNode.h"

#include <utility>
#include <string>

class SpinInteractionVertex
{

private:
  std::pair<SpinInteractionNode,SpinInteractionNode> nodes_;
  double strength_; // in M rad s-1

public:

  SpinInteractionVertex();
  
  SpinInteractionVertex(const SpinInteractionNode & node1,
                        const SpinInteractionNode & node2,
                        const double strength);

  SpinInteractionNode get_node1() const;
  SpinInteractionNode get_node2() const;
  double get_strength() const;

  void set_nodes(const SpinInteractionNode & node1,
                 const SpinInteractionNode & node2);

  void set_node1(const SpinInteractionNode & node);
  void set_node2(const SpinInteractionNode & node);

  void set_strength(const double strength);


};

#endif // SPININTERACTIONVERTEX_H

