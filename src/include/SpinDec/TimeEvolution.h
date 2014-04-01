#ifndef TIMEEVOLUTION_H_
#define TIMEEVOLUTION_H_

// SpinDec::TimeEvolution
//
// Time evolution of a complex variable.
// Time in microseconds.
//
// Seto Balian, Apr 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/TimeArray.h"

namespace SpinDec
{

class TimeEvolution
{
private:
  TimeArray time_array_; // in microseconds
  CDoubleArray evolution_;
  
  TimeEvolution(const TimeArray& time_array, const CDoubleArray& evolution);
  
public:
  TimeEvolution();
  explicit TimeEvolution(const TimeArray& time_array); // evolution set to zeros
  
  const CDouble& evolution(const UInt index) const;
  
  void set_evolution_zeros();
  void set_evolution_ones();
  
  const CDoubleArray& get_evolution() const;
  const TimeArray& get_time_array() const;

  
  UInt dimension() const; // number of time steps
  
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
