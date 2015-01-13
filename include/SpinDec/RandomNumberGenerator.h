#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

// SpinDec::RandomNumberGenerator
//
// Static methods for generating random numbers.
//
// Seto Balian, Jan 13, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/constants.h"

namespace SpinDec
{

class RandomNumberGenerator
{
public:
  // random integer i, min <= 0 <= max, from a uniform distribution
  // (using cstdlib rand())
  static int uniform_c_rand(const int min, const int max);
  
  // if seed is negative, calls clock_seed_uniform_c_rand
  static void seed_uniform_c_rand(const int seed);
  
  static void clock_seed_uniform_c_rand(); // seed with current time
  
  static double normal_c_rand(const double mean, const double stdev);
  
};

} // namespace SpinDec

#endif // RANDOMNUMBERGENERATOR_H_
