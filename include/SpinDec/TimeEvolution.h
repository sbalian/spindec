#ifndef TIMEEVOLUTION_H_
#define TIMEEVOLUTION_H_

// SpinDec::TimeEvolution
//
// Time evolution of a complex variable.
// Time in microseconds.
//
// Seto Balian, Apr 17, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/TimeArray.h"

namespace SpinDec
{

class TimeEvolution
{
private:
  TimeArray time_array_; // in microseconds
  CDoubleArray evolution_;
  
  void print(const char option) const;
  void print(const string& file_name, const char option) const;

  
public:
  TimeEvolution();
  TimeEvolution(const TimeArray& time_array, const CDoubleArray& evolution);

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
  
  void print() const;
  void print_real() const;
  void print_imag() const;
  void print_abs() const;
  
  void print(const string& file_name) const;
  void print_real(const string& file_name) const;
  void print_imag(const string& file_name) const;
  void print_abs(const string& file_name) const;

  void scale_time(const double scalar);
  
  // if evolution <= 1e-4, set to 1e-4
  void finite_zeros();
  
  // true if at least one time step has abs(evolution) exceeding unity
  bool has_greater_than_one() const;
  
};

} // namespace SpinDec

#endif // TIMEEVOLUTION_H_
