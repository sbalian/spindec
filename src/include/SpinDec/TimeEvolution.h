#ifndef TIMEEVOLUTION_H_
#define TIMEEVOLUTION_H_

// TimeEvolution
//
// Time evolution of a complex variable.
// Time in microseconds.
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/typedefs.h"
#include <iostream>

namespace SpinDec
{

class TimeEvolution
{
private:
  DoubleArray time_; // microseconds
  CDoubleArray evolution_;  
  
  UInt dimension_; // evolution grid size (1D)
                           // (number of time steps + 1)
  
  void clear(); // std::clear time_ and evolution_ and set dimension to zero
  
  TimeEvolution(const DoubleArray& time,
                const CDoubleArray& evolution);
  
  bool is_time_equal(const DoubleArray& time) const; // is time == time_ ?
                                                 // element by element
  
public:
  TimeEvolution();
  TimeEvolution(const double initial_time,
                const double final_time,
                const UInt num_steps); // calls initialize()
  
  // clears existing time and evolution, sets new time and sets new evolution
  // to zeros
  void initialize(const double initial_time,
                  const double final_time,
                  const UInt num_steps);
  
  // same as above but with logarithmic time scale (base 10)
  // time = 10^initial_exponent ... 10^final_exponent in num_steps steps
  void initialize_logarithmic(const double initial_exponent,
                              const double final_exponent,
                              const UInt num_steps);
  
  double get_time(const UInt index) const;
  const CDouble& get_evolution(const UInt index) const;
  
  void set_evolution_zeros();
  void set_evolution_ones();
  
  const DoubleArray& get_time() const;
  const CDoubleArray& get_evolution() const;
  
  UInt num_steps() const; // dimension - 1
  UInt get_dimension() const;
  
  // adds evolutions element by element
  TimeEvolution operator+(const TimeEvolution& to_add) const;
  // multiplies evolutions element by element
  TimeEvolution operator*(const TimeEvolution& to_multiply) const;
  // divides evolutions element by element
  TimeEvolution operator/(const TimeEvolution& to_divide) const;
  
  // Print with cout
  friend std::ostream& operator<<(std::ostream& os,
      TimeEvolution const & time_evolution);
  
};

} // namespace SpinDec

#endif // TIMEEVOLUTION_H_
