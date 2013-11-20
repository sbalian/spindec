// See SpinInteractionGraph.h for description.
// Seto Balian 20/11/2013

#include "SpinInteractionGraph.h"
#include "SpinInteractionNode.h"
#include "SpinInteractionVertex.h"

#include <vector>

SpinInteractionGraph::SpinInteractionGraph() {
  //
}

void SpinInteractionGraph::add_node(const SpinInteractionNode & node)
{
  nodes_.push_back(node);
  return;
}

void SpinInteractionGraph::add_vertex(const unsigned int node_label1,
                                      const unsigned int node_label2,
                                const std::string & interaction_type,
                                      const double strength)
{
  vertices_.push_back(SpinInteractionVertex(node_label1,node_label2,
                interaction_type,strength));
  return;
}

std::vector<SpinInteractionNode> SpinInteractionGraph::get_nodes() const {
  return nodes_;
}

SpinInteractionNode SpinInteractionGraph::get_node(
                                              const unsigned int index) const {
  return get_nodes()[index];
}


void SpinInteractionGraph::add_vertex(const unsigned int node_label1,
                                      const unsigned int node_label2)
{
  vertices_.push_back(SpinInteractionVertex(node_label1,node_label2,"",0.0));
  return;
}

unsigned int SpinInteractionGraph::num_nodes() const {
  
  return nodes_.size();
  
}


unsigned int SpinInteractionGraph::num_vertices() const {
  
  return vertices_.size();
  
}


unsigned int SpinInteractionGraph::multiplicity() const {

  unsigned int i;
  unsigned int tot_multiplicity = 1;
  unsigned int n = num_nodes();

  for (i=0;i<n;i++) {
    tot_multiplicity *= get_node(i).get_spin().multiplicity();
  }
  
  return tot_multiplicity;
  
}