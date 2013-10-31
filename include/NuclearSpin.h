#ifndef NUCLEARSPIN_H
#define NUCLEARSPIN_H

// Nuclear spin
//
// Just a Spin.
//
// Seto Balian 31/10/2013

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

