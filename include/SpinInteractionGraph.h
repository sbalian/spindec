#ifndef SPININTERACTIONGRAPH_H
#define SPININTERACTIONGRAPH_H

// SpinInteractionGraph
//
// System of spin interaction nodes and vertices.
//
// Seto Balian 31/10/2013

#include "SpinInteractionNode.h"
#include "SpinInteractionVertex.h"

#include <vector>

class SpinInteractionGraph
{

private:

  std::vector<SpinInteractionNode> nodes_;
  std::vector<SpinInteractionVertex> vertices_;

public:

  SpinInteractionGraph();
  
  void add_node(const SpinInteractionNode & node);
  void add_vertex(const SpinInteractionVertex & vertex);

};


#endif // SPININTERACTIONGRAPH_H

