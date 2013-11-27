#ifndef SPINSTATE_H
#define	SPINSTATE_H

// SpinState
//
// Holds a quantum state and a basis.
//
// Seto Balian, November 27, 2013

#include <Eigen/Dense>

class SpinState
{
private:
  Eigen::VectorXcd state_;
  ZeemanBasis basis_;

public:

};

#endif	 // SPINSTATE_H
