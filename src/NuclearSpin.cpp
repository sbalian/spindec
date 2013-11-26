// See NuclearSpin.h for description.
// Seto Balian, November 26, 2013

#include "NuclearSpin.h"
#include "Spin.h"

NuclearSpin::NuclearSpin () : Spin() {
  Named::set_class_name("NuclearSpin");
}

NuclearSpin::NuclearSpin(const double quantum_number,
                         const double gyromagnetic_ratio,
                         const Eigen::Vector3d & position) :
                         Spin(quantum_number,gyromagnetic_ratio,position) {
  Named::set_class_name("NuclearSpin");
}
