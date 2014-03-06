#ifndef TIMEEVOLUTION_H_
#define TIMEEVOLUTION_H_

// TimeEvolution
//
// Time evolution of a complex variable.
// Time in microseconds.
//
// Seto Balian, Mar 6, 2014

#include "SpinDec/types.h"
#include <iostream>

namespace SpinDec
{

class TimeEvolution
{
private:
  dvector time_; // microseconds
  cdvector evolution_;  
  
  unsigned int dimension_; // evolution grid size (1D)
                           // (number of time steps + 1)
  
  void clear(); // std::clear time_ and evolution_ and set dimension to zero
  
  TimeEvolution(const dvector& time,
                const cdvector& evolution);
  
  bool is_time_equal(const dvector& time) const; // is time = time_ ?
                                                 // element by element
  
public:
  TimeEvolution();
  TimeEvolution(const double initial_time,
                const double final_time,
                const unsigned int num_steps); // calls initialize()
  
  // clears existing time and evolution, sets new time and sets new evolution
  // to zeros
  void initialize(const double initial_time,
                  const double final_time,
                  const unsigned int num_steps);
  
  // same as above but with logarithmic time scale (base 10)
  // time = 10^initial_exponent ... 10^final_exponent in num_steps steps
  void initialize_logarithmic(const double initial_exponent,
                              const double final_exponent,
                              const unsigned int num_steps);
  
  double get_time(const unsigned int index) const;
  const cdouble& get_evolution(const unsigned int index) const;
  
  void set_evolution_zeros();
  void set_evolution_ones();
  
  const dvector& get_time() const;
  const cdvector& get_evolution() const;
  
  unsigned int num_steps() const; // dimension - 1
  unsigned int get_dimension() const;
  
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
