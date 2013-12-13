#ifndef LABELEDGRAPH_H_
#define LABELEDGRAPH_H_

// LabeledGraph
//
// Labeled graph.
//
// Seto Balian, Dec 13, 2013

#include "LabeledVertex.h"
#include "Edge.h"

#include "VertexContents.h"
#include "EdgeContents.h"

#include <vector>
#include <utility>

class LabeledGraph
{
protected:

  std::vector<LabeledVertex> vertices_;
  std::vector<VertexContents> vertex_contents_;
  
  std::vector<Edge> edges_;
  std::vector<EdgeContents> edge_contents_;
  
  std::pair<unsigned int,LabeledVertex> get_index_and_vertex(
      const unsigned int vertex_label) const;
  std::pair<unsigned int,Edge> get_index_and_edge(
      const unsigned int vertex_label1,
      const unsigned int vertex_label2) const; 
  
  unsigned int get_vertex_index(const unsigned int vertex_label) const;
  unsigned int get_edge_index(const unsigned int vertex_label1,
                const unsigned int vertex_label2) const;

public:

  LabeledGraph();

  LabeledVertex get_vertex(const unsigned int vertex_label) const;
  Edge get_edge(const unsigned int vertex_label1,
                const unsigned int vertex_label2) const;
  
  VertexContents get_vertex_contents_by_index(
      const unsigned int index) const;
  EdgeContents get_edge_contents_by_index(
      const unsigned int index) const;
  
  VertexContents get_vertex_contents(const unsigned int vertex_label) const;
  
  EdgeContents get_edge_contents(const unsigned int vertex_label1,
                const unsigned int vertex_label2) const;

  unsigned int num_vertices() const;
  unsigned int num_edges() const;

  void add_vertex(const LabeledVertex & vertex,
      const VertexContents & contents);
  void add_edge(const Edge & edge,
      const EdgeContents & contents);

  void clear();
  
};

#endif // LABELEDGRAPH_H_
