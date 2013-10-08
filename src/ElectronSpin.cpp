// See ElectronSpin.h for description.
// Seto Balian 08/10/2013

#include "ElectronSpin.h"
#include "Spin.h"
#include "MathPhysConstants.h"

#include <Eigen/Dense>


ElectronSpin::ElectronSpin() :
      Spin(0.5,MathPhysConstants::electron_gyromagnetic_ratio(),
      Eigen::Vector3d::Zero())
{
//
}


ElectronSpin::ElectronSpin(const Eigen::Vector3d & position) :
      Spin(0.5,MathPhysConstants::electron_gyromagnetic_ratio(),
      position)
{
//
}

