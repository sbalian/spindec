// See SpinParameters.h for description.
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinParameters.h"
#include <iomanip>

namespace SpinDec
{

SpinParameters::SpinParameters() :
          quantum_number_(0.0),
          gyromagnetic_ratio_(0.0),
          multiplicity_(0)
{/**/}

SpinParameters::SpinParameters(const double quantum_number,
           const double gyromagnetic_ratio) :
      quantum_number_(quantum_number),
      gyromagnetic_ratio_(gyromagnetic_ratio),
      multiplicity_(calc_multiplicity(quantum_number))
{/**/}

double SpinParameters::get_quantum_number() const
{
  return quantum_number_;
}

double SpinParameters::get_gyromagnetic_ratio() const
{
  return gyromagnetic_ratio_;
}

UInt SpinParameters::get_multiplicity() const
{
  return multiplicity_;
}

UInt SpinParameters::calc_multiplicity(const double quantum_number) const
{
  return static_cast<UInt>(2.0*quantum_number + 1.0);
}

std::ostream& operator<<(std::ostream& os,
    SpinParameters const & spin_parameters)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << "Spin:\n";
  
  os << "Quantum number = ";
  os << spin_parameters.get_quantum_number() << std::endl;
  
  os << "Gyromagnetic ratio = ";
  os << std::scientific << std::setprecision(4);
  os << spin_parameters.get_gyromagnetic_ratio();
  os << " M rad s-1 T-1\n";
  
  os << "Multiplicity = " << std::fixed << spin_parameters.get_multiplicity();
  os << std::endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}

} // namespace SpinDec
