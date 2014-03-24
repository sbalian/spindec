// See TimeEvolution.h for description.
// Seto Balian, Mar 24, 2014

#include "SpinDec/TimeEvolution.h"
#include <cmath>
#include <algorithm>
#include "SpinDec/Errors.h"

#include <iomanip>

namespace SpinDec
{

void TimeEvolution::clear()
{
  time_.clear();
  evolution_.clear();
  dimension_ = 0;
  return;
}

TimeEvolution::TimeEvolution(const DoubleArray& time,
              const CDoubleArray& evolution)
{
  time_ = time;
  evolution_ = evolution;
  dimension_ = time.size();
}

bool TimeEvolution::is_time_equal(const DoubleArray& time) const
                                         // is time = time_?
                                         // element by element
{
  const UInt n = time.size();
  if (n != get_time().size()) {
    Errors::quit("TimeEvolution time dimension mismatch.");
    return false;
  }
  
  // TODO This may not be OK with doubles ... test it
  return  std::equal(time.begin(), time.begin() + n, get_time().begin());
  
}


TimeEvolution::TimeEvolution() : dimension_(0)
{/**/}

TimeEvolution::TimeEvolution(const double initial_time,
    const double final_time, const UInt num_steps)
{
  initialize(initial_time,final_time,num_steps);
}

void TimeEvolution::initialize(const double initial_time,
                const double final_time,
                const UInt num_steps)
{
  
  clear();
  dimension_ = num_steps + 1;
  
  const double time_step = (final_time - initial_time) /
                      static_cast<double>(num_steps);
  
  double time = initial_time;
  time_.push_back(time);
  for (UInt i=0;i<num_steps;i++) {
    time += time_step;
    time_.push_back(time);
  }
  
  set_evolution_zeros();
  
  return;

}

void TimeEvolution::initialize_logarithmic(const double initial_exponent,
                            const double final_exponent,
                            const UInt num_steps)
{
  clear();
  dimension_ = num_steps + 1;
  
  const double exponent_step = (final_exponent - initial_exponent) /
                      static_cast<double>(num_steps);
  
  double exponent = initial_exponent;
  time_.push_back(std::pow(10.0,exponent));
  
  for (UInt i=0;i<num_steps;i++) {
    exponent += exponent_step;
    time_.push_back(std::pow(10.0,exponent));
  }
  
  set_evolution_zeros();
  
  return;
  
}

double TimeEvolution::get_time(const UInt index) const
{
  if (index >= get_dimension()) {
    Errors::quit("Invalid index to retrieve time.");
  }
  return time_[index];
}

const CDouble& TimeEvolution::get_evolution(
    const UInt index) const
{
  if (index >= get_dimension()) {
    Errors::quit("Invalid index to retrieve evolution.");
  }
  return evolution_[index];
}

void TimeEvolution::set_evolution_zeros()
{
  evolution_.clear();
  for (UInt i=0;i<get_dimension();i++) {
    evolution_.push_back(CDouble(0.0,0.0));
  }
}

void TimeEvolution::set_evolution_ones()
{
  evolution_.clear();
  for (UInt i=0;i<get_dimension();i++) {
    evolution_.push_back(CDouble(1.0,0.0));
  }
}

const DoubleArray& TimeEvolution::get_time() const
{
  return time_;
}

const CDoubleArray& TimeEvolution::get_evolution() const
{
  return evolution_;
}

UInt TimeEvolution::num_steps() const
{
  return get_dimension() - 1;
}

UInt TimeEvolution::get_dimension() const
{  
  return dimension_;
}

TimeEvolution TimeEvolution::operator+(
    const TimeEvolution& to_add) const
{
  if (is_time_equal(to_add.get_time()) == false) {
    Errors::quit("TimeEvolution time vectors not equal.");
  }

  CDoubleArray new_evolution;
  for (UInt i=0;i<get_dimension();i++) {
    new_evolution.push_back( get_evolution()[i]+to_add.get_evolution()[i] );
  }
  
  return TimeEvolution(get_time(),new_evolution);
  
}

TimeEvolution TimeEvolution::operator *(
    const TimeEvolution& to_multiply) const
{
  if (is_time_equal(to_multiply.get_time()) == false) {
    Errors::quit("TimeEvolution time vectors not equal.");
  }

  CDoubleArray new_evolution;
  for (UInt i=0;i<get_dimension();i++) {
    new_evolution.push_back( get_evolution()[i]*to_multiply.get_evolution()[i]);
  }
  
  return TimeEvolution(get_time(),new_evolution);

}

TimeEvolution TimeEvolution::operator /(
    const TimeEvolution& to_divide) const
{
  if (is_time_equal(to_divide.get_time()) == false) {
    Errors::quit("TimeEvolution time vectors not equal.");
  }

  CDoubleArray new_evolution;
  for (UInt i=0;i<get_dimension();i++) {
    new_evolution.push_back( get_evolution()[i]/to_divide.get_evolution()[i] );
  }
  
  return TimeEvolution(get_time(),new_evolution);

}

std::ostream& operator<<(std::ostream& os, TimeEvolution const & time_evolution)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << std::scientific << std::setprecision(4);
  os << std::left;

  os << "Time evolution (time units: microseconds)" << std::endl;
  for (UInt i=0;i<time_evolution.get_dimension();i++) {
    os << std::setw(12) << time_evolution.get_time(i);
    os << std::setw(12) << time_evolution.get_evolution(i) << std::endl;
  }
  os << endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}



} // namespace SpinDec

