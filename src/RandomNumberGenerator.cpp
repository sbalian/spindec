// See RandomNumberGenerator.h for description.
// Seto Balian, Nov 13, 2014

#include "SpinDec/RandomNumberGenerator.h"

#include <cstdlib>
#include <ctime>

namespace SpinDec
{

int RandomNumberGenerator::uniform_c_rand(const int min, const int max)
{
  return std::rand()%(max - min + 1) + min;
}

void RandomNumberGenerator::seed_uniform_c_rand(const int seed)
{
  if (seed < 0) {
    clock_seed_uniform_c_rand();
    return;
  } // else
  std::srand( static_cast<unsigned int>(seed) );
  return;
}

void RandomNumberGenerator::clock_seed_uniform_c_rand()
{
  // TODO what does time return? make sure it's never negative here
  seed_uniform_c_rand(std::time(NULL));
  return;
}


} // namespace SpinDec


// TEST
//g++ -I ../src/include/ -I/home/sbalian/eigen ../src/RandomNumberGenerator.cpp
//#include <iostream>
//int main()
//{
//  SpinDec::RandomNumberGenerator::seed_uniform_c_rand(-1);
//  std::cout << SpinDec::RandomNumberGenerator::uniform_c_rand(-3,3);
//  std::cout << std::endl;
//  return 0;
//}
