// See LabeledVertex.h for description.
// Seto Balian, Dec 11, 2013

#include "LabeledVertex.h"

LabeledVertex::LabeledVertex() : label_(0)
{
}

LabeledVertex::LabeledVertex(const unsigned int label) : label_(label)
{
}

unsigned int LabeledVertex::get_label() const
{
  return label_;
}
