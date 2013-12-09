// See SpinHamiltonian.h for description.
// Seto Balian, Dec 9, 2013

#include "SpinHamiltonian.h"

void SpinHamiltonian::fill(const SpinInteractionGraph& graph)
{
  // TODO
  return;
}

SpinHamiltonian::SpinHamiltonian() : SpinOperator()
{
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph& graph) :
    SpinOperator()
{
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph& graph,
    const std::string& diagonalizer)
{
}

void SpinHamiltonian::update(const SpinInteractionGraph& graph)
{
}

Eigen::MatrixXcd SpinHamiltonian::evolutionMatrix(const double time) const
{
}
