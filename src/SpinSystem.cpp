// See SpinSystem.h for description.
// Seto Balian, May 29, 2014

#include "SpinDec/SpinSystem.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void SpinSystem::diagonalize(const string & diagonalizer)
{
  eigenspectrum_ = HermitianEigenspectrum(hamiltonian_.get_matrix(),
      diagonalizer);
  return;
}

void SpinSystem::set_eigenstates()
{
  // just sets, already calculated in constructor
  eigenstates_ = eigenspectrum_.get_eigenvectors();
  return;
}

void SpinSystem::set_energies()
{
  // just sets, already calculated in constructor
  energies_ = eigenspectrum_.get_eigenvalues().real();
  return;
}

SpinSystem::SpinSystem() : SpinSystemBase()
{
}

void SpinSystem::check_level_label(const UInt level_label) const
{
  if (level_label < dimension()) {
    return; // all ok
  } // else
    Errors::quit("Energy levels: 0,1,2,...,dim(Hamiltonian)");
    return;
}

SpinSystem::SpinSystem(const SpinInteractionGraph & graph,
    const UniformMagneticField & field, const string & diagonalizer) :
    SpinSystemBase(graph,field)
{
  diagonalize(diagonalizer);
  set_energies();
  set_eigenstates();
}

SpinSystem::SpinSystem(const SpinInteractionGraph & graph,
    const UniformMagneticField & field) :
    SpinSystemBase(graph,field)
{
  diagonalize("Lapack");
  set_energies();
  set_eigenstates();
}

UInt SpinSystem::dimension() const
{
  return hamiltonian_.get_dimension();
}

} // namespace SpinDec

