// See Spins.h for description.
// Seto Balian 01/11/2013

#include <vector>

#include "Spin.h"
#include "Spins.h"

Spins::Spins() {
  //
}

void Spins::add_spin(const Spin & spin) {
  spins_.push_back(spin);
  return;
}

unsigned int Spins::num_spins() const {
  return spins_.size();
}

Spin Spins::get_spin(const unsigned int index) const {
  return spins_[index];
}

unsigned int Spins::multiplicity() const {

  unsigned int i;
  unsigned int tot_multiplicity = 1;
  unsigned int n = num_spins();

  for (i=0;i<n;i++) {
    tot_multiplicity = tot_multiplicity*(get_spin(i).multiplicity());
  }
  return tot_multiplicity;
}

void Spins::set_spin(const unsigned int index, const Spin & spin) {
  spins_[index] = spin;  
  return;
}


