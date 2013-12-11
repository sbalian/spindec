#ifndef LABELEDGRAPH_H_
#define LABELEDGRAPH_H_

// LabeledGraph
//
// Labeled graph.
//
// Seto Balian, Dec 11, 2013

#include "LabeledVertex.h"
#include "Edge.h"

#include <vector>

class LabeledGraph
{
protected:

  std::vector<LabeledVertex> vertices_;
  std::vector<Edge> edges_;

public:

  LabeledGraph();

  LabeledVertex get_vertex(const unsigned int vertex_label) const;
  Edge get_edge(const unsigned int vertex_label1,
                const unsigned int vertex_label2) const;
  
  unsigned int num_vertices() const;
  unsigned int num_edges() const;

  virtual void add_vertex(const LabeledVertex & vertex);
  virtual void add_edge(const Edge & edge);

  void clear();
  
  virtual ~LabeledGraph();

};

#endif // LABELEDGRAPH_H_
