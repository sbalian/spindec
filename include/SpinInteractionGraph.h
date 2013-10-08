#ifndef SPININTERACTIONGRAPH_H
#define SPININTERACTIONGRAPH_H

// Spin interaction graph
//
// TODO Describe
//
// Seto Balian 08/10/2013

#include "SpinInteractionNode.h"
#include "SpinInteraction.h"

#include <vector>

class SpinInteractionGraph
{

private:

  std::vector<SpinInteractionNode> nodes_;
  std::vector<SpinInteraction> interactions_;

public:

  SpinInteractionGraph();
  
  void add_node(const SpinInteractionNode & node);
  void add_interaction(const SpinInteraction & interaction);

};


#endif // SPININTERACTIONGRAPH_H

