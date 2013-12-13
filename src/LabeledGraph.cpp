// See LabeledGraph.h for description.
// Seto Balian, Dec 13, 2013

// TODO Use find and other stl methods?

#include "LabeledGraph.h"
#include "Errors.h"

#include <utility>

LabeledGraph::LabeledGraph()
{
}

std::pair<unsigned int,LabeledVertex> LabeledGraph::get_index_and_vertex(
    const unsigned int vertex_label) const
{
  // Return vertex only if it exists (use labels to check)
  for (unsigned int i=0;i<num_vertices();i++) {
    if (vertex_label == vertices_[i].get_label()) {
      return std::pair<unsigned int,LabeledVertex>(i,vertices_[i]);
    }
  } // else
  Errors::quit("LabeledGraph: Vertex does not exist.");
  return std::pair<unsigned int,LabeledVertex>(0,vertices_[0]);
}

std::pair<unsigned int,Edge> LabeledGraph::get_index_and_edge(
    const unsigned int vertex_label1,
    const unsigned int vertex_label2) const
{
  // Return edge only if it exists (use labels to check)
  for (unsigned int i=0;i<num_edges();i++) {
    if ( (vertex_label1 == edges_[i].get_label1()) &&
         (vertex_label2 == edges_[i].get_label2()) ) {
      return std::pair<unsigned int,Edge>(i,edges_[i]);
    }
  }
  Errors::quit("LabeledGraph: Edge does not exist.");
  return std::pair<unsigned int,Edge>(0,edges_[0]);
}

unsigned int LabeledGraph::get_vertex_index(
    const unsigned int vertex_label) const
{
  return get_index_and_vertex(vertex_label).first;
}

unsigned int LabeledGraph::get_edge_index(const unsigned int vertex_label1,
              const unsigned int vertex_label2) const
{
  return get_index_and_edge(vertex_label1, vertex_label2).first;
}

void LabeledGraph::add_vertex(const LabeledVertex& vertex,
    const VertexContents & contents)
{
  // First see if vertex already exists and quit if it does
  for (unsigned int i=0;i<num_vertices();i++) {
    if (vertex.get_label() == vertices_[i].get_label()) {
      Errors::quit("LabeledGraph: Vertex already exists.");
    }
  }
  // If vertex does not exist, add it
  vertices_.push_back(vertex);
  vertex_contents_.push_back(contents);
  return;
}

void LabeledGraph::add_edge(const Edge& edge,
    const EdgeContents & contents)
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
  } else {
      edges_.push_back(edge);
      edge_contents_.push_back(contents);
  }
  
  return;
  
}

LabeledVertex LabeledGraph::get_vertex(const unsigned int vertex_label) const
{
  return get_index_and_vertex(vertex_label).second;
}

Edge LabeledGraph::get_edge(const unsigned int vertex_label1,
    const unsigned int vertex_label2) const
{
  return get_index_and_edge(vertex_label1, vertex_label2).second;
}

unsigned int LabeledGraph::num_vertices() const
{
  return vertices_.size();
}

unsigned int LabeledGraph::num_edges() const
{
  return edges_.size();
}

VertexContents LabeledGraph::get_vertex_contents_by_index(
    const unsigned int index) const
{
  return vertex_contents_[index];
}

EdgeContents LabeledGraph::get_edge_contents_by_index(
    const unsigned int index) const
{
  return edge_contents_[index];
}

void LabeledGraph::clear()
{
  vertices_.clear();
  edges_.clear();
  return;
}

VertexContents LabeledGraph::get_vertex_contents(
    const unsigned int vertex_label) const
{
  return vertex_contents_[get_vertex_index(vertex_label)];
}

EdgeContents LabeledGraph::get_edge_contents(const unsigned int vertex_label1,
    const unsigned int vertex_label2) const
{
  return edge_contents_[get_edge_index(vertex_label1, vertex_label2)];
}
