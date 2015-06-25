#ifndef TIMEARRAY_H_
#define TIMEARRAY_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// Time array in microseconds.
class TimeArray
{
private:
  /// Microseconds.
  DoubleArray time_vector_;
  
  /// Evolution grid size (1D) (number of time steps + 1)
  UInt dimension_;
  
  /// std::clear time_vector_ and set dimension to zero.
  void clear(); 
  
  /// Clears existing time sets new time to zeros.
  void initialize(const double initial_time,
                  const double final_time,
                  const UInt num_steps);
    
public:
  TimeArray();
  
  /// Calls initialize().
  TimeArray(const double initial_time,
            const double final_time,
            const UInt num_steps);
  
  explicit TimeArray(const double single_time);
  
  /// is time_vector == time_vector_ ? (element by element).
  bool operator==(const TimeArray& time_array) const;

  /**
   * Convert to initial_time ... final_time with logarithmic steps (base 10)
   * = num_steps.
   */
  void logarithmic_time();
  
  double get_time(const UInt index) const;
  const DoubleArray& get_time_vector() const;
  
  /// dimension_ - 1.
  UInt num_steps() const;
  UInt get_dimension() const;
  
  void scale_time(const double scalar);
  
  /// Print with cout.
  friend std::ostream& operator<<(std::ostream& os,
      TimeArray const & time_array);
  
};

} // namespace SpinDec

#endif // TIMEARRAY_H_
