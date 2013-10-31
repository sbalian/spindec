#ifndef SPINS_H
#define SPINS_H

// Spins
//
// For multiple Spin objects.
//
// Seto Balian 31/10/2013

#include "Spin.h"
#include <vector>

class Spins
{

private:
  std::vector<Spin> spins_;

public:

  Spins();
  void add_spin(const Spin & spin);
  unsigned int num_spins() const;
  Spin get_spin(const unsigned int index) const;
  unsigned int multiplicity() const;
  void set_spin(const unsigned int index, const Spin & spin);

  
};

#endif // SPINS_H

