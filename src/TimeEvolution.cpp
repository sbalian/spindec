// See TimeEvolution.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/TimeEvolution.h"
#include "SpinDec/Errors.h"

#include <iomanip>

namespace SpinDec
{


TimeEvolution::TimeEvolution()
{/**/}

TimeEvolution::TimeEvolution(const TimeArray& time_array)
{
  time_array_ = time_array;
  set_evolution_zeros();
}

const CDouble& TimeEvolution::evolution(
    const UInt index) const
{
  if (index >= dimension()) {
    Errors::quit("Invalid index to retrieve evolution.");
  }
  return evolution_[index];
}

void TimeEvolution::set_evolution_zeros()
{
  evolution_.clear();
  for (UInt i=0;i<dimension();i++) {
    evolution_.push_back(CDouble(0.0,0.0));
  }
}

void TimeEvolution::set_evolution_ones()
{
  evolution_.clear();
  for (UInt i=0;i<dimension();i++) {
    evolution_.push_back(CDouble(1.0,0.0));
  }
}

const CDoubleArray& TimeEvolution::get_evolution() const
{
  return evolution_;
}

const TimeArray& TimeEvolution::get_time_array() const
{
  return time_array_;
}


UInt TimeEvolution::dimension() const
{  
  return time_array_.get_dimension();
}

TimeEvolution::TimeEvolution(const TimeArray& time_array,
    const CDoubleArray& evolution)
{
  time_array_ = time_array;
  evolution_ = evolution;
}

TimeEvolution TimeEvolution::operator+(
    const TimeEvolution& to_add) const
{
  if ( !(to_add.get_time_array() == get_time_array()) ) {
    Errors::quit("TimeEvolution time vectors not equal.");
  }

  CDoubleArray new_evolution;
  for (UInt i=0;i<dimension();i++) {
    new_evolution.push_back( evolution(i)+to_add.evolution(i) );
  }
  
  return TimeEvolution(get_time_array(),new_evolution);
}

TimeEvolution TimeEvolution::operator *(
    const TimeEvolution& to_multiply) const
{
  if ( !(to_multiply.get_time_array() == get_time_array()) ) {
    Errors::quit("TimeEvolution time vectors not equal.");
  }

  CDoubleArray new_evolution;
  for (UInt i=0;i<dimension();i++) {
    new_evolution.push_back( evolution(i)*to_multiply.evolution(i));
  }
  
  return TimeEvolution(get_time_array(),new_evolution);
  
}

TimeEvolution TimeEvolution::operator /(
    const TimeEvolution& to_divide) const
{
  if ( !(to_divide.get_time_array() == get_time_array()) ) {
    Errors::quit("TimeEvolution time vectors not equal.");
  }

  CDoubleArray new_evolution;
  for (UInt i=0;i<dimension();i++) {
    new_evolution.push_back( evolution(i)/to_divide.evolution(i) );
  }
  
  return TimeEvolution(get_time_array(),new_evolution);

}

void TimeEvolution::print(const char option)  const
{
  
  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  cout << std::scientific;
  cout << std::left;

  cout << "# Time evolution (time units: ms)" << std::endl;
  for (UInt i=0;i<dimension();i++) {
    cout << std::setprecision(4); //         convert us -> ms here
    cout << std::setw(15) << get_time_array().get_time(i)/1000.0;
    cout << std::setprecision(10);
    
    if (option == 'r') {
      cout << std::setw(30) << std::real(evolution(i)) << std::endl;
      continue;
    }
    if (option == 'i') {
      cout << std::setw(30) << std::imag(evolution(i)) << std::endl;
      continue;
    }
    if (option == 'a') {
      cout << std::setw(30) << std::abs(evolution(i)) << std::endl;
      continue;
    } // else ...
    cout << std::setw(30) << evolution(i) << std::endl;
  }
  cout << endl;
  
  // Restore formatting
  std::cout.flags( f );

  
  return;
}



void TimeEvolution::print() const
{
  print('c');
  return;
}

void TimeEvolution::print_real() const
{
  print('r');
  return;
}

void TimeEvolution::print_imag() const
{
  print('i');
  return;
}

void TimeEvolution::print_abs() const
{
  print('a');
  return;
}


} // namespace SpinDec

