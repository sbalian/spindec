#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
// Also contains a uniform magnetic field all vertices see.
// TODO generalise to non-uniform magnetic fields.
//
// Seto Balian, Dec 6, 2013

#include "SpinInteractionVertex.h"
#include "SpinInteractionEdge.h"
#include "UniformMagneticField.h"

#include <vector>

class SpinInteractionGraph
{

private:
  std::vector<SpinInteractionVertex> vertices_;
  std::vector<SpinInteractionEdge> edges_;
  
  UniformMagneticField field_;
  

public:

  SpinInteractionGraph();
  SpinInteractionGraph(const UniformMagneticField & field);
  
  void add_vertex(const SpinInteractionVertex & vertex);
  void add_edge(const SpinInteractionEdge & edge);
  
  SpinInteractionVertex get_vertex(const unsigned int index) const;
  SpinInteractionEdge get_edge(const unsigned int index) const;
  
  UniformMagneticField get_field() const;
  void set_field(const UniformMagneticField & field);
  
  unsigned int num_vertices() const;
  unsigned int num_edges() const;
  
  void clear();

};

#endif // SPININTERACTIONGRAPH_H_
