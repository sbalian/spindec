// For testing SpinDec
// Seto Balian, Nov 7, 2014

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  
  const UInt upper_level = 12;
  const UInt lower_level = 9;
  
  SpinDonor donor(0.480,4.5,1.75e5,-44.0,1450.0,lower_level-1,upper_level-1,
                  ThreeVector(0.0,0.0,0.0),ThreeVector(0.0,0.0,0.0),true);
  
  cout << donor.get_hamiltonian().get_graph().get_basis() << endl;

  return 0;

}
