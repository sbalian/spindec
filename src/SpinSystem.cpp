// See SpinSystem.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/SpinSystem.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void SpinSystem::solve_once()
{
  
  // solve only once
  if (is_solved_ == true) {
    return;
  } else {
      is_solved_ = true;
  }
  
  eigenspectrum_ = HermitianEigenspectrum(hamiltonian_.get_matrix());
  eigenstates_ = eigenspectrum_.get_eigenvectors();
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

SpinSystem::SpinSystem(const SpinHamiltonian & hamiltonian) :
    SpinSystemBase(hamiltonian)
{
  
}

UInt SpinSystem::dimension() const
{
  return hamiltonian_.get_dimension();
}

auto_ptr<SpinSystemBase> SpinSystem::clone() const
{
  return auto_ptr<SpinSystemBase> (new SpinSystem(*this));
}


}// namespace SpinDec

