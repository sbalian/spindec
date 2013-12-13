// See SpinHamiltonian.h for description.
// Seto Balian, Dec 13, 2013

#include "SpinHamiltonian.h"
#include "BoostEigen.h"

#include <complex>

void SpinHamiltonian::build_basis(const SpinInteractionGraph& graph) const
{
  // TODO  
  return;
}

void SpinHamiltonian::fill_matrix(
    const SpinInteractionGraph& graph) const
{
  // TODO
  return;
}

SpinHamiltonian::SpinHamiltonian() : SpinOperator(),
    field_(UniformMagneticField())
{
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph& graph,
    const UniformMagneticField & field) :
    SpinOperator(),
    field_(field)
{
  build_basis(graph);
  fill_matrix(graph);
}

void SpinHamiltonian::update(const SpinInteractionGraph& graph)
{
  // TODO
  return;
}

UniformMagneticField SpinHamiltonian::get_field() const
{
  return field_;
}

Eigen::MatrixXcd SpinHamiltonian::evolutionMatrix(
    const HermitianEigenspectrum & spectrum, const double time) const
{
  return BoostEigen::unitarySpectralDecomposition(
                       spectrum.get_eigenvectors(),
                       BoostEigen::exp( spectrum.get_eigenvalues() * 
                                        std::complex<double>(0.0,-time) ) 
                                                 );
}
