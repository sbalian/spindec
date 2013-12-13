// See LabeledVertex.h for description.
// Seto Balian, Dec 13, 2013

#include "LabeledVertex.h"

LabeledVertex::LabeledVertex() : label_(0)
{
  contents_ = VertexContents();
}

LabeledVertex::LabeledVertex(const unsigned int label,
    const VertexContents & contents) : label_(label)
{
  contents_ = contents;
}

unsigned int LabeledVertex::get_label() const
{
  return label_;
}

VertexContents LabeledVertex::get_contents() const
{
  return contents_;
}
