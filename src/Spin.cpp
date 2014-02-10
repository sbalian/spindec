// See Spin.h for description.
// Seto Balian, Feb 10, 2014

#include "Spin.h"
#include <iomanip>

namespace SpinDecoherence
{

unsigned int Spin::calc_multiplicity() const
{
  return static_cast<unsigned int>(2.0*get_quantum_number() + 1.0);
}

Spin::Spin(const double quantum_number,
     const double gyromagnetic_ratio,
     const ThreeVector & position,
     const SpinState & state) :
      quantum_number_(quantum_number),
      gyromagnetic_ratio_(gyromagnetic_ratio),
      position_(position),
      state_(state),
      multiplicity_(calc_multiplicity())
{/**/}

Spin::Spin() : Spin(0.0,0.0,ThreeVector::Zero(),SpinState())
{/**/}

double Spin::get_quantum_number() const
{
  return quantum_number_;
}

double Spin::get_gyromagnetic_ratio() const
{
  return gyromagnetic_ratio_;
}

ThreeVector Spin::get_position() const
{
  return position_;
}

SpinState Spin::get_state() const
{
  return state_;
}

unsigned int Spin::get_multiplicity() const
{
  return multiplicity_;
}

std::ostream& operator<<(std::ostream& os, Spin const & spin)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << "Spin:\n";
  
  os << "Quantum number = ";
  os << spin.get_quantum_number() << std::endl;
  
  os << "Gyromagnetic ratio = ";
  os << std::scientific << std::setprecision(4);
  os << spin.get_gyromagnetic_ratio();
  os << " M rad s-1 T-1\n";
  
  os << "Position = ";
  os << std::scientific << std::setprecision(2);
  os << spin.get_position();
  os << " Angstroms\n";

  os << "Multiplicity = " << std::fixed << spin.get_multiplicity() << std::endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}

} // namespace SpinDecoherence
