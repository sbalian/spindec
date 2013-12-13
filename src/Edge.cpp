// See Edge.h for description.
// Seto Balian, Dec 13, 2013

#include "Edge.h"
#include "Errors.h"

Edge::Edge()
{
  contents_ = EdgeContents();
}

Edge::Edge(const unsigned int label1, const unsigned int label2,
    const EdgeContents & contents)
{
  contents_ = contents;
  labels_.first = label1;
  labels_.second = label2;
  if (label1 == label2) {
    Errors::quit("Edge: Labels must be different.");
  }
}

unsigned int Edge::get_label1() const
{
  return labels_.first;
}

unsigned int Edge::get_label2() const
{
  return labels_.second;
}

EdgeContents Edge::get_contents() const
{
  return contents_;
}
