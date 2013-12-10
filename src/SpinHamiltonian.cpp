// See SpinHamiltonian.h for description.
// Seto Balian, Dec 10, 2013

#include "SpinHamiltonian.h"
#include "BoostEigen.h"

#include <complex>
#include <cmath>

SpinBasis SpinHamiltonian::built_basis(const SpinInteractionGraph& graph) const
{
  // Loop over vectices, get bases from spin states and make the combined
  // (tensor product) basis
  for (unsigned int i=0;i<vertices_)
  
  return SpinBasis();
}

Eigen::MatrixXcd SpinHamiltonian::filled_matrix(
    const SpinInteractionGraph& graph) const
{
  // TODO
  return Eigen::MatrixXcd::Zero(2,2);
}

SpinHamiltonian::SpinHamiltonian() : SpinOperator()
{
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph& graph) :
    SpinOperator(filled_matrix(graph), built_basis(graph))
{
}

void SpinHamiltonian::update(const SpinInteractionGraph& graph)
{
  // TODO
  return;
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

