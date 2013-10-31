// See NuclearSpin.h for description.
// Seto Balian 31/10/2013

#include "NuclearSpin.h"
#include "Spin.h"

NuclearSpin::NuclearSpin () : Spin() {
//
}

NuclearSpin::NuclearSpin(const double quantum_number,
                         const double gyromagnetic_ratio,
                         const Eigen::Vector3d & position) :
                         Spin(quantum_number,gyromagnetic_ratio,position) {
  //
}
