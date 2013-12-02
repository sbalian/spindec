#ifndef SPININTERACTIONEDGE_H
#define SPININTERACTIONEDGE_H

// SpinInteractionEdge
//
// @todo Describe
//
// Seto Balian, December 2, 2013

#include <utility>
#include "SpinInteractionVertex.h"

class SpinInteractionEdge
{

private:
  std::pair<SpinInteractionVertex,SpinInteractionVertex> edge_;
  
public:

  SpinInteractionEdge(); // 2 vertices with labels 0
  SpinInteractionEdge(const SpinInteractionVertex & vertex1,
                      const SpinInteractionVertex & vertex2);

  std::pair<SpinInteractionVertex,SpinInteractionVertex> get_vertices() const;
  SpinInteractionVertex get_vertex1() const;
  SpinInteractionVertex get_vertex2() const;
  
  void set_vertices(
    const std::pair<SpinInteractionVertex,SpinInteractionVertex> & vertices);
  void set_vertices(const SpinInteractionVertex & vertex1,
                    const SpinInteractionVertex & vertex2);
  void set_vertex1(const SpinInteractionVertex & vertex);
  void set_vertex2(const SpinInteractionVertex & vertex);
  
};

#endif // SPININTERACTIONEDGE_H
