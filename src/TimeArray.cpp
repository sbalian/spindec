// See TimeArray.h for description.
// Seto Balian, Nov 11, 2014

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
  
  if (final_time < initial_time) {
    Errors::quit("Can't have final time < initial time.");
  }
  
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

void TimeArray::logarithmic_time()
{
  
  // save the old dimension, initial and final times and num of time steps
  const UInt old_dimension = get_dimension();
  const double initial_time = get_time(0);
  const UInt nsteps = num_steps();
  const double final_time = get_time(nsteps);
  
  // clear the current time array
  clear();
  
  if (initial_time == 0.0) {
    Errors::quit("Can't have time = 0 when constructing log time scale.");
  }
  
  const double new_step = ( std::log10(final_time) -
                            std::log10(initial_time))
                               / static_cast<double>(nsteps);
  
  double exponent = std::log10(initial_time);
  
  time_vector_.push_back(std::pow(10.0,exponent));
  for (UInt i=0;i<nsteps;i++) {
    exponent += new_step;
    time_vector_.push_back(std::pow(10.0,exponent));
  }
  
  dimension_ = old_dimension;
  
  return;
  
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

void TimeArray::scale_time(const double scalar)
{
  for (UInt i=0;i<get_dimension();i++) {
    time_vector_[i]*=scalar;
  }
  return;
}



} // namespace SpinDec

