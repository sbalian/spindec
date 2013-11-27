#ifndef SPININTERACTIONGRAPH_H
#define SPININTERACTIONGRAPH_H

// SpinInteractionGraph
//
// System of spin interaction nodes and vertices.
//
// Seto Balian, November 27, 2013

#include "SpinInteractionNode.h"
#include "SpinInteractionVertex.h"
#include "SpinInteraction.h"

#include <vector>
#include <string>

class SpinInteractionGraph
{

private:
  std::vector<SpinInteractionNode> nodes_;
  std::vector<SpinInteractionVertex> vertices_;

public:

  SpinInteractionGraph();
  
  void add_node(const SpinInteractionNode & node);
  void add_vertex(const unsigned int node_label1,
                  const unsigned int node_label2,
                  const SpinInteraction & interaction);
  
  std::vector<SpinInteractionNode> get_nodes() const;
  SpinInteractionNode get_node(const unsigned int index) const;
 
  unsigned int num_nodes() const;
  unsigned int num_vertices() const;
  
  unsigned int multiplicity() const; // total multiplicity from all spins in
                                     // all nodes

};

#endif // SPININTERACTIONGRAPH_H
