#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

// Seto Balian, Jun 24, 2015

#include "Constants.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// Static methods for generating random numbers.
class RandomNumberGenerator
{
public:
  
  /**
   * Random integer \f$ {\rm min} \leq i \leq {\rm max}\f$ from a uniform
   * distribution using cstdlib rand().
   */
  static int uniform_c_rand(const int min, const int max);
  
  /// If seed is negative, calls clock_seed_uniform_c_rand().
  static void seed_uniform_c_rand(const int seed);
  
  /// Seed with current time.
  static void clock_seed_uniform_c_rand();
  
  static double normal_c_rand(const double mean, const double stdev);
  
};

} // namespace SpinDec

#endif // RANDOMNUMBERGENERATOR_H_
