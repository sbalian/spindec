// See SpinHamiltonian.h for description.
// Seto Balian 21/11/2013

#include "SpinHamiltonian.h"

SpinHamiltonian::SpinHamiltonian() {
  //
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph & interaction_graph)
{
  
  interaction_graph_ = interaction_graph;
  
}
