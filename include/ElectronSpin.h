#ifndef ELECTRONSPIN_H
#define ELECTRONSPIN_H

// Electron spin object
//
// TODO Describe
//
// Seto Balian 05/10/2013

#include "Spin.h"
#include <Eigen/Dense>

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  ElectronSpin(const Eigen::Vector3d & position);

};

#endif // ELECTRONSPIN_H

