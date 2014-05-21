// See SpinSystem.h for description.
// Seto Balian, May 21, 2014

#include "SpinDec/SpinSystem.h"
#include "SpinDec/Errors.h"

#include <iostream>
#include <iomanip>

namespace SpinDec
{

void SpinSystem::diagonalize()
{
  eigenspectrum_ = HermitianEigenspectrum(hamiltonian_.get_matrix(),
      diagonalizer_);
  is_diagonalized_ = true;
}

SpinSystem::SpinSystem()
{
  diagonalizer_ = "Lapack";
  is_diagonalized_ = false;
}

SpinSystem::SpinSystem(const SpinInteractionGraph& graph,
    const UniformMagneticField& field)
{
  diagonalizer_ = "Lapack";
  is_diagonalized_ = false;
  
  graph_ = graph;
  hamiltonian_ = SpinHamiltonian(graph, field);

}

SpinState SpinSystem::eigenstate(const UInt level)
{
  
  if (is_diagonalized_ == false) {
    diagonalize();
  }
  
  return SpinState(eigenspectrum_.get_eigenvector(level-1),
                   hamiltonian_.get_basis());
  
}

double SpinSystem::energy(const UInt level)
{
  if (is_diagonalized_ == false) {
    diagonalize();
  }
  return std::real(eigenspectrum_.get_eigenvalue(level-1));
}

const UniformMagneticField& SpinSystem::get_field() const
{
  return field_;
}

void SpinSystem::set_diagonalizer(const string& diagonalizer)
{
  diagonalizer_ = diagonalizer;
  return;
}

SpinOperator SpinSystem::evolution_operator(const double time)
{
  
  if (is_diagonalized_ == false) {
    diagonalize();
  }
  
  return SpinOperator( hamiltonian_.evolution_matrix(eigenspectrum_,time),
                       hamiltonian_.get_basis());
}

UInt SpinSystem::dimension() const
{
  return hamiltonian_.get_dimension();
}

// options:
// e - energies
// E - eigenstates
// H - Hamiltonian
void SpinSystem::print(const char option)
{
  
  if (is_diagonalized_ == false) {
    diagonalize();
  }
  
  std::ios::fmtflags f( cout.flags() );
  
  cout << std::setprecision(10) << std::left << std::scientific;
  
  if (option == 'H') {
    
    cout << hamiltonian_ << endl;
    
    cout.flags( f );
    return;
  }
  
  if (option == 'e') {
    
    cout << eigenspectrum_.get_eigenvalues().real() << endl;
    
    cout.flags( f );
    return;
  }
  
  if (option == 'E') {
    
    cout << eigenspectrum_.get_eigenvectors() << endl;
    
    cout.flags( f );
    return;
  }
  
  
  Errors::quit("Invalid print option.");
  return;

}


} // namespace SpinDec

