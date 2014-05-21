// For testing SpinDec
// Seto Balian, May 21, 2014

#include <iostream>
#include <iomanip>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  
  SpinDonor donor(0.480,4.5,1.75e5,-44.0,1450.0,20,9,
                  ThreeVector(),ThreeVector(),false);
  cout << donor.get_basis() << endl;

  return 0;

}
