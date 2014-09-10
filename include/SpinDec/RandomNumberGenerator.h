#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

// SpinDec::RandomNumberGenerator
//
// Static methods for generating random numbers.
//
// Seto Balian, Aug 4, 2014

#include "SpinDec/typedefs.h"

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
  
};

} // namespace SpinDec

#endif // RANDOMNUMBERGENERATOR_H_
