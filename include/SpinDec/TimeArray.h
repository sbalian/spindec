#ifndef TIMEARRAY_H_
#define TIMEARRAY_H_

// SpinDec::TimeArray
//
// Time array in microseconds.
//
// Seto Balian, Nov 10, 2014

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class TimeArray
{
private:
  DoubleArray time_vector_; // microseconds  
  UInt dimension_; // evolution grid size (1D)
                           // (number of time steps + 1)
  
  void clear(); // std::clear time_vector_ and set dimension to zero
    
public:
  TimeArray();
  TimeArray(const double initial_time,
            const double final_time,
            const UInt num_steps); // calls initialize()
  
  explicit TimeArray(const double single_time);
  
  bool operator==(const TimeArray& time_array) const;
                                          // is time_vector == time_vector_ ?
                                          // element by element

  // clears existing time sets new time to zeros
  void initialize(const double initial_time,
                  const double final_time,
                  const UInt num_steps);
  
  // same as above but with logarithmic time scale (base 10)
  // time_vector_ = 10^initial_exponent ... 10^final_exponent in num_steps steps
  void initialize_logarithmic(const double initial_exponent,
                              const double final_exponent,
                              const UInt num_steps);
  
  double get_time(const UInt index) const;
  const DoubleArray& get_time_vector() const;
  
  UInt num_steps() const; // dimension - 1
  UInt get_dimension() const;
  
  void scale_time(const double scalar);
  
  // Print with cout
  friend std::ostream& operator<<(std::ostream& os,
      TimeArray const & time_array);
  
};

} // namespace SpinDec

#endif // TIMEARRAY_H_
