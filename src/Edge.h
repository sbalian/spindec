#ifndef EDGE_H_
#define EDGE_H_

// Edge
//
// Edge in a labeled graph.
//
// Seto Balian, Dec 10, 2013

#include "LabeledVertex.h"
#include <utility>

class Edge
{
private:

  std::pair<unsigned int,unsigned int> labels_;

public:

  Edge();
  Edge(const unsigned int label1,
       const unsigned int label2);
  
  unsigned int get_label1() const;
  unsigned int get_label2() const;
  
};

#endif // EDGE_H_
