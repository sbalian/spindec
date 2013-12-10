// See LabeledGraph.h for description.
// Seto Balian, Dec 10, 2013

#include "LabeledGraph.h"
#include "Errors.h"

// TODO Use find and other stl methods?

LabeledGraph::LabeledGraph()
{
}

void LabeledGraph::add_vertex(const LabeledVertex& vertex)
{
  // First see if vertex already exists and quit if it does
  for (unsigned int i=0;i<num_vertices();i++) {
    if (vertex.get_label() == vertices_[i].get_label()) {
      Errors::quit("LabeledGraph: Vertex already exists.");
    }
  }
  // If vertex does not exist, add it
  vertices_.push_back(vertex);
  return;
}

void LabeledGraph::add_edge(const Edge& edge)
{
  unsigned int labels_found = 0; // number of labels found
  // First see if the two vertex labels specified by edge exist
  // and quit if either one doesn't
  for (unsigned int i=0;i<num_vertices();i++) {
    if ( edge.get_label1() == vertices_[i].get_label() ) {
      labels_found++;
    }
    if ( edge.get_label2() == vertices_[i].get_label() ) {
      labels_found++;
    }

  }
  
  if (labels_found != 2) {
    Errors::quit("LabeledGraph: Vertices don't exist for added edge.");
  }
  
  return;
  
}

LabeledVertex LabeledGraph::get_vertex(const unsigned int vertex_label) const
{
  // Return vertex only if it exists (use labels to check)
  for (unsigned int i=0;i<num_vertices();i++) {
    if (vertex_label == vertices_[i].get_label()) {
      return vertices_[i];
    }
  } // else
  Errors::quit("LabeledGraph: Vertex does not exist.");
  return LabeledVertex();
}

Edge LabeledGraph::get_edge(const unsigned int vertex_label1,
    const unsigned int vertex_label2) const
{
  // Return edge only if it exists (use labels to check)
  for (unsigned int i=0;i<num_edges();i++) {
    if ( (vertex_label1 == edges_[i].get_label1()) &&
         (vertex_label2 == edges_[i].get_label2()) ) {
      return edges_[i];
    }
  }
  Errors::quit("LabeledGraph: Edge does not exist.");
  return Edge();
}

unsigned int LabeledGraph::num_vertices() const
{
  return vertices_.size();
}

unsigned int LabeledGraph::num_edges() const
{
  return edges_.size();
}

void LabeledGraph::clear()
{
  vertices_.clear();
  edges_.clear();
  return;
}
