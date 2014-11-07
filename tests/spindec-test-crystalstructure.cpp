// For testing SpinDec
// Seto Balian, Nov 7, 2014

#include "SpinDec/base.h"

using namespace SpinDec;

int main()
{
  
  DiamondCubic diamond_structure(5.43, 54.3);
  
  diamond_structure.write_site_vectors("DiamondCrystalStructure.dat");
  
  // Tested against legacyspindecoherence - obtaiend exact match with diff
  // after removing 0,0,0 from new file
  
  return 0;
}
