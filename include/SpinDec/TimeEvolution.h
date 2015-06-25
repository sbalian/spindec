#ifndef TIMEEVOLUTION_H_
#define TIMEEVOLUTION_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/TimeArray.h"

namespace SpinDec
{

/**
 * \brief Time evolution of a complex variable.
 * 
 * Time in microseconds.
 * 
 */
class TimeEvolution
{
private:
  /// In microseconds.
  TimeArray time_array_;
  CDoubleArray evolution_;
  
  void print(const char option) const;
  void print(const string& file_name, const char option) const;

  
public:
  TimeEvolution();
  TimeEvolution(const TimeArray& time_array, const CDoubleArray& evolution);

  // Evolution set to zeros.
  explicit TimeEvolution(const TimeArray& time_array);
  
  const CDouble& evolution(const UInt index) const;
  
  void set_evolution_zeros();
  void set_evolution_ones();
  
  const CDoubleArray& get_evolution() const;
  const TimeArray& get_time_array() const;

  /// Number of time steps.
  UInt dimension() const;
  
  /// Adds evolutions element by element.
  TimeEvolution operator+(const TimeEvolution& to_add) const;
  /// Multiplies evolutions element by element.
  TimeEvolution operator*(const TimeEvolution& to_multiply) const;
  /// Divides evolutions element by element.
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
  
  /// If evolution \f$ \leq 10^{-4}\f$, set to \f$10^{-4}\f$.
  void finite_zeros();
  
  /// True if at least one time step has abs(evolution) exceeding unity.
  bool has_greater_than_one() const;
  
};

} // namespace SpinDec

#endif // TIMEEVOLUTION_H_
