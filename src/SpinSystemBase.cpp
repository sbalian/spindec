// See SpinSystemBase.h for description.
// Seto Balian, Sep 29, 2014

#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/Errors.h"
#include "SpinDec/TwoStateSuperposition.h"

#include <iostream>
#include <iomanip>

namespace SpinDec
{

SpinSystemBase::SpinSystemBase() : is_solved_(false), is_state_set_(false)
{
}

SpinSystemBase::SpinSystemBase(const SpinHamiltonian& hamiltonian) :
    is_solved_(false), is_state_set_(false)
{
  hamiltonian_ = hamiltonian;
}

EvolutionOperator SpinSystemBase::evolution_operator(const double time)
{
  
  solve_once();
  
  return EvolutionOperator(hamiltonian_.get_basis(),
      eigenstates_,energies_,time);
  
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

SpinState SpinSystemBase::eigenstate(const UInt level_label)
{
  
  solve_once();

  check_level_label(level_label);
  return SpinState(eigenstates_.col(level_label),
      hamiltonian_.get_basis());
}

double SpinSystemBase::energy(const UInt level_label)
{

  solve_once();

  check_level_label(level_label);
  return energies_(level_label);
}

const SpinState& SpinSystemBase::get_state() const
{
  
  if (is_state_set_ == false) {
    Errors::quit("State not set.");
  }
  
  return state_;
  
}

const ComplexMatrix& SpinSystemBase::get_eigenvector_matrix()
{
  
  solve_once();
  
  return eigenstates_;
}

const RealVector& SpinSystemBase::get_eigenvalue_vector()
{
  
  solve_once();

  return energies_;
}

PiPulse SpinSystemBase::pi_pulse(const UInt level_label1,
    const UInt level_label2)
{
  SpinState level1 = eigenstate(level_label1);
  SpinState level2 = eigenstate(level_label2);
  
  vector<SpinState> other_states;
  for (UInt i=0;i<dimension();i++) {
    
    if (i == level_label1) {
      continue;
    }
    if (i == level_label2) {
      continue;
    }
    
    other_states.push_back(eigenstate(i));
    
  }
  
  return PiPulse(level1,level2,other_states);
  
}

void SpinSystemBase::set_state(const CDouble& c0,
    const UInt level_label0, const CDouble& c1, const UInt level_label1)
{
    
  state_ = TwoStateSuperposition(c0,eigenstate(level_label0),
      c1,eigenstate(level_label1));
  is_state_set_ = true;
  return;
  
}

SpinSystemBase::~SpinSystemBase()
{
}

const SpinHamiltonian& SpinSystemBase::get_hamiltonian() const
{
  return hamiltonian_;
}

void SpinSystemBase::set_state(const UInt level_label)
{
  state_ = eigenstate(level_label);
  is_state_set_ = true;
  return;
}

void SpinSystemBase::set_state(const SpinState& state)
{
  
  
  if (!(get_hamiltonian().get_basis().is_equal(state.get_basis()))) {
    Errors::quit("Basis mismatch in setting state.");
  }
  state_ = state;
  
  is_state_set_ = true;
  return;
  
}

void SpinSystemBase::update_positions(const UIntArray& vertex_labels,
    const vector<ThreeVector>& positions)
{
  if (vertex_labels.size() != positions.size()) {
    Errors::quit("Vertex label and position arrays must be of the same size.");
    return;
  }
  
  hamiltonian_.update_positions(vertex_labels,positions);
 
  is_solved_ = false;
  solve_once(); // ie solve again ...
  
 
  
  return;

}


} // namespace SpinDec

