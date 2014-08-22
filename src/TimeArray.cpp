// See TimeArray.h for description.
// Seto Balian, Aug 1, 2014

#include "SpinDec/TimeArray.h"
#include "SpinDec/Errors.h"

#include <algorithm>
#include <iomanip>

namespace SpinDec
{

void TimeArray::clear()
{
  time_vector_.clear();
  dimension_ = 0;
  return;
}

TimeArray::TimeArray() : dimension_(0)
{
}

TimeArray::TimeArray(const double single_time)
{
  initialize(single_time,single_time,0);
}

TimeArray::TimeArray(const double initial_time,
    const double final_time, const UInt num_steps)
{
  initialize(initial_time,final_time,num_steps);
}

bool TimeArray::operator==(const TimeArray& time_array) const
{
  const UInt n = time_array.get_dimension();
  if (n != get_dimension()) {
    Errors::quit("TimeArray time dimension mismatch.");
    return false;
  }
  // TODO This may not be OK with doubles ... test it
  return  std::equal(time_array.get_time_vector().begin(),
      time_array.get_time_vector().begin() + n,
      get_time_vector().begin());
}

void TimeArray::initialize(const double initial_time,
    const double final_time, const UInt num_steps)
{
  clear();
  dimension_ = num_steps + 1;
  
  const double time_step = (final_time - initial_time) /
                      static_cast<double>(num_steps);
  
  double time_var = initial_time;
  time_vector_.push_back(time_var);
  for (UInt i=0;i<num_steps;i++) {
    time_var += time_step;
    time_vector_.push_back(time_var);
  }
    
  return;
}

void TimeArray::initialize_logarithmic(const double initial_exponent,
    const double final_exponent, const UInt num_steps)
{
  clear();
  dimension_ = num_steps + 1;
  
  const double exponent_step = (final_exponent - initial_exponent) /
                      static_cast<double>(num_steps);
  
  double exponent = initial_exponent;
  time_vector_.push_back(std::pow(10.0,exponent));
  
  for (UInt i=0;i<num_steps;i++) {
    exponent += exponent_step;
    time_vector_.push_back(std::pow(10.0,exponent));
  }
  
  return;
}

double TimeArray::get_time(const UInt index) const
{
  if (index >= get_dimension()) {
    Errors::quit("Invalid index to retrieve time.");
  }
  return time_vector_[index];
}

const DoubleArray& TimeArray::get_time_vector() const
{
  return time_vector_;
}

UInt TimeArray::num_steps() const
{
  return get_dimension() - 1;
}

UInt TimeArray::get_dimension() const
{
  return dimension_;
}

std::ostream& operator<<(std::ostream& os, TimeArray const & time_array)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << std::scientific << std::setprecision(4);
  os << std::left;

  os << "Time evolution (time units: microseconds)" << std::endl;
  for (UInt i=0;i<time_array.get_dimension();i++) {
    os << std::setw(12) << time_array.get_time(i) << std::endl;
  }
  os << endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}


} // namespace SpinDec

