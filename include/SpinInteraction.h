#ifndef SPININTERACTION_H
#define SPININTERACTION_H

// Spin interaction
//
// TODO Describe
//
// Seto Balian 04/10/2013

#include "SpinInteractionNode.h"

#include <utility>
#include <string>

class SpinInteraction
{

private:
  std::pair<SpinInteractionNode,SpinInteractionNode> nodes_;
  double strength_; // in M rad s-1

public:

  SpinInteraction();
  
  SpinInteraction(const SpinInteractionNode & node1,
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

  // TODO something like this ...
  void set_interaction(const std::string & option);
  void set_interaction(const double strength);

};


#endif // SPININTERACTION_H

