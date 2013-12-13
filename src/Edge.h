#ifndef EDGE_H_
#define EDGE_H_

// Edge
//
// Edge in a labeled graph.
//
// Seto Balian, Dec 13, 2013

#include "EdgeContents.h"
#include <utility>

class Edge
{
private:
  std::pair<unsigned int,unsigned int> labels_;
  EdgeContents contents_;

public:

  Edge();
  Edge(const unsigned int label1,
       const unsigned int label2, const EdgeContents & contents);
  
  unsigned int get_label1() const;
  unsigned int get_label2() const;
  
  EdgeContents get_contents() const;
  
};

#endif // EDGE_H_
