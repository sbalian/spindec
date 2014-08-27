// See SpinSystemBase.h for description.
// Seto Balian, Aug 27, 2014

#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/Errors.h"

#include <iostream>
#include <iomanip>

namespace SpinDec
{

SpinSystemBase::SpinSystemBase()
{
}

SpinSystemBase::SpinSystemBase(const SpinInteractionGraph& graph,
    const UniformMagneticField& field)
{
  graph_ = graph;
  field_ = field;
  hamiltonian_ = SpinHamiltonian(graph, field);
}

const UniformMagneticField& SpinSystemBase::get_field() const
{
  return field_;
}

SpinOperator SpinSystemBase::evolution_operator(const double time) const
{
  return SpinOperator( hamiltonian_.evolution_matrix(
      eigenstates_,energies_,time),
                       hamiltonian_.get_basis());
}


// options:
// e - energies
// E - eigenstates
// H - Hamiltonian
void SpinSystemBase::print(const char option)
{
  
  std::ios::fmtflags f( cout.flags() );
  
  cout << std::setprecision(10) << std::left << std::scientific;
  
  if (option == 'H') {
    
    cout << hamiltonian_ << endl;
    
    cout.flags( f );
    return;
  }
  
  if (option == 'e') {
    
    cout << energies_ << endl;
    
    cout.flags( f );
    return;
  }
  
  if (option == 'E') {
    
    cout << eigenstates_ << endl;
    
    cout.flags( f );
    return;
  }
  
  
  Errors::quit("Invalid print option.");
  return;

}

SpinState SpinSystemBase::eigenstate(const UInt level_label) const
{
  check_level_label(level_label);
  return SpinState(eigenstates_.col(level_label),
      hamiltonian_.get_basis());
}

double SpinSystemBase::energy(const UInt level_label) const
{
  check_level_label(level_label);
  return energies_(level_label);
}

const SpinState& SpinSystemBase::get_state() const
{
  return state_;
}

const ComplexMatrix SpinSystemBase::get_eigenvector_matrix() const
{
  return eigenstates_;
}

const RealVector SpinSystemBase::get_eigenvalue_vector() const
{
  return energies_;
}

SpinSystemBase::~SpinSystemBase()
{
}

const SpinInteractionGraph& SpinSystemBase::get_graph() const
{
  return graph_;
}

const SpinHamiltonian& SpinSystemBase::get_hamiltonian() const
{
  return hamiltonian_;
}

void SpinSystemBase::set_state(const UInt level_label)
{
  state_ = eigenstate(level_label);
  return;
}


void SpinSystemBase::set_state(const SpinState& state)
{
  if (!(graph_.get_basis().is_equal(state.get_basis()))) {
    Errors::quit("Basis mismatch in setting state.");
  }
  return;
}

} // namespace SpinDec
