// See SpinSystemBase.h for description.
// Seto Balian, May 29, 2014

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

//SpinSystemBase SpinSystemBase::join( const SpinSystemBase & t_join)
//{
//  
//}

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

SpinSystemBase::~SpinSystemBase()
{
}

} // namespace SpinDec
