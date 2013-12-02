#ifndef SPININTERACTIONGRAPH_H
#define SPININTERACTIONGRAPH_H

// SpinInteractionGraph
//
// @todo Describe
//
// Seto Balian, December 2, 2013

#include "SpinInteractionVertex.h"
#include "SpinInteractionEdge.h"

#include <vector>

class SpinInteractionGraph
{

private:
  std::vector<SpinInteractionVertex> isolated_vertices_;
  std::vector<SpinInteractionEdge> edges_;

public:

  SpinInteractionGraph();// no vertices, no edges
  
  void add_isolated_vertex(const SpinInteractionVertex & isolated_vertex);
  void add_edge(const SpinInteractionEdge & edge);
  
  SpinInteractionVertex get_isolated_vertex(const unsigned int index) const;
  SpinInteractionEdge get_edge(const unsigned int index) const;
  
  unsigned int num_isolated_vertices() const;
  unsigned int num_edges() const;
  
  void clear();

};

#endif // SPININTERACTIONGRAPH_H
