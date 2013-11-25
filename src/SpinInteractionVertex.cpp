// See SpinInteractionVertex.h for description.
// Seto Balian 25/11/2013

#include "SpinInteractionVertex.h"

#include <utility>

SpinInteractionVertex::SpinInteractionVertex()
{
  set_labels(0,0);
  set_strength(0.0);
  Named::set_class_name("SpinInteractionVertex");
}

SpinInteractionVertex::SpinInteractionVertex(const unsigned int label1,
                                 const unsigned int label2,
                                const std::string & interaction_type,
                                 const double strength)
{
  set_labels(label1,label2);
  set_interaction_type(interaction_type);
  set_strength(strength);
  Named::set_class_name("SpinInteractionVertex");
}


unsigned int SpinInteractionVertex::get_label1() const
{
  return labels_.first;
}

unsigned int SpinInteractionVertex::get_label2() const
{
  return labels_.second;
}

std::string SpinInteractionVertex::get_interaction_type() const
{
 return interaction_type_; 
}


double SpinInteractionVertex::get_strength() const
{
  return strength_;
}

void SpinInteractionVertex::set_labels(const unsigned int label1,
                                const unsigned int label2)
{
  set_label1(label1);
  set_label2(label2);
  return;
}

void SpinInteractionVertex::set_label1(const unsigned int label)
{
  labels_.first = label;
  return;
}

void SpinInteractionVertex::set_label2(const unsigned int label)
{
  labels_.second = label;
  return;
}

void SpinInteractionVertex::set_interaction_type(const std::string & 
                                                          interaction_type)
{
  interaction_type_ = interaction_type;
  return;
  
}


void SpinInteractionVertex::set_strength(const double strength)
{
  strength_ = strength;
  return;
}

