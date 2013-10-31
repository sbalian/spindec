#ifndef ELECTRONSPIN_H
#define ELECTRONSPIN_H

// Electron spin
//
// Spin object with set spin quantum number (S = 1/2)
// and gyromagnetic ratio (for the free electron).
//
// Seto Balian 31/10/2013

#include "Spin.h"

#include <Eigen/Dense>

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  ElectronSpin(const Eigen::Vector3d & position);

};

#endif // ELECTRONSPIN_H

