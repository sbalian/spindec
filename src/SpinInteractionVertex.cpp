// See SpinInteractionVertex.h for description.
// Seto Balian, Dec 3, 2013

#include "SpinInteractionVertex.h"

SpinInteractionVertex::SpinInteractionVertex()
{
  label_ = 0;
}

SpinInteractionVertex::SpinInteractionVertex(const unsigned int label)
{
  label_ = label;
}

unsigned int SpinInteractionVertex::get_label() const
{
  return label_;
}
