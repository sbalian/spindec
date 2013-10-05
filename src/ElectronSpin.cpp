// See ElectronSpin.h for description.
// Seto Balian 05/10/2013

#include "ElectronSpin.h"
#include "Spin.h"

#include <Eigen/Dense>

// TODO use mathandphys constants class ...

ElectronSpin::ElectronSpin() : Spin(0.5,1.760859708e5,Eigen::Vector3d::Zero())
{
// Uses the free electron gyromagnetic ratio in M rad s-1 (SOURCE: Wikipedia)
}

ElectronSpin::ElectronSpin(const Eigen::Vector3d & position)
                  : Spin(0.5,1.760859708e5,Eigen::Vector3d::Zero())
{
// Uses the free electron gyromagnetic ratio in M rad s-1 (SOURCE: Wikipedia)
}




ElectronSpin::ElectronSpin(0.5,gamma_e,Eigen::Vector3d::Zero())

ElectronSpin::ElectronSpin() : Spin(0.5,1.7591e,Eigen::Vector3d::Zero())
{

}

ElectronSpin::ElectronSpin(const Eigen::Vector3d & position)
{

}
