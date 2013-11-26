// See SpinInteractionGraph.h for description.
// Seto Balian, November 26, 2013

#include "SpinInteractionGraph.h"

#include <vector>

SpinInteractionGraph::SpinInteractionGraph() {
  Named::set_class_name("SpinInteractionGraph");
}

void SpinInteractionGraph::add_node(const SpinInteractionNode & node)
{
  nodes_.push_back(node);
  return;
}

void SpinInteractionGraph::add_vertex(const unsigned int node_label1,
                                      const unsigned int node_label2,
                                const SpinInteraction & interaction)
{
  vertices_.push_back(SpinInteractionVertex(node_label1,node_label2,
                                            interaction));
  return;
}

std::vector<SpinInteractionNode> SpinInteractionGraph::get_nodes() const {
  return nodes_;
}

SpinInteractionNode SpinInteractionGraph::get_node(
                                              const unsigned int index) const {
  return get_nodes()[index];
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
