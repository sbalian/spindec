#ifndef NUCLEARSPIN_H
#define NUCLEARSPIN_H

// Nuclear spin
//
// Just a Spin.
//
// Seto Balian 01/11/2013

#include "Spin.h"

class NuclearSpin : public Spin
{

public:

  NuclearSpin();
  NuclearSpin(const double quantum_number,
              const double gyromagnetic_ratio,
              const Eigen::Vector3d & position);


};

#endif // NUCLEARSPIN_H

