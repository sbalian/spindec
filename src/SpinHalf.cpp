// See SpinHalf.h for description.
// Seto Balian, Jun 2, 2014

#include "SpinDec/SpinHalf.h"
#include "SpinDec/SpinHalfStates.h"
#include "SpinDec/SpinUp.h"
#include "SpinDec/SpinDown.h"
#include "SpinDec/SpinHalfParameters.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void SpinHalf::set_energies()
{
  RealVector eigenvalues(2);
  const double mod_energy = 
      std::abs(gyromagnetic_ratio_)*field_.get_magnitude()/2.0;
  eigenvalues(0) = -mod_energy;
  eigenvalues(1) =  mod_energy;
  energies_ = eigenvalues;
  return;
}

void SpinHalf::set_eigenstates()
{
  
  SpinState spin_up = SpinUp(SpinHalfParameters(gyromagnetic_ratio_));
  SpinState spin_down = SpinDown(SpinHalfParameters(gyromagnetic_ratio_));

  ComplexMatrix eigenvectors(2,2);  

  eigenvectors.col(0) = spin_up.get_state_vector();
  eigenvectors.col(1) = spin_down.get_state_vector();

  eigenstates_ = eigenvectors;
  return;
  
}

void SpinHalf::check_level_label(const UInt level_label) const
{
  
  if (level_label < dimension()) {
    return; // ok
  }
  Errors::quit("A spin-1/2 has two levels, labeled 0 and 1.");
  return;
}

SpinHalf::SpinHalf(const double gyromagnetic_ratio,
    const double field_strength,
    const ThreeVector& position) : SpinSystemBase()
{
  gyromagnetic_ratio_ = gyromagnetic_ratio;
    
  field_ = UniformMagneticField(field_strength);
  graph_.add_vertex(SpinHalfParameters(gyromagnetic_ratio),position);
  hamiltonian_ = SpinHamiltonian(graph_, field_);
  
  set_energies();
  set_eigenstates();
  
}

SpinHalf::SpinHalf()
{
  gyromagnetic_ratio_ = 0.0;
  set_energies();
  set_eigenstates();
}

UInt SpinHalf::dimension() const
{
  return 2;
}

auto_ptr<SpinSystemBase> SpinHalf::clone() const
{
  return auto_ptr<SpinSystemBase>( new SpinHalf(*this) );
}

} // namespace SpinDec

