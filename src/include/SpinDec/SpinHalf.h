#ifndef SPINHALF_H_
#define SPINHALF_H_

// SpinDec::SpinHalf
//
// A spin-1/2 spin system.
//
// Seto Balian, May 27, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"

namespace SpinDec
{

class SpinHalf : public SpinSystemBase
{
  
private:

  double gyromagnetic_ratio_;
  
  virtual void set_energies();
  virtual void set_eigenstates();
  
  virtual void check_level(const UInt level) const;

public:
  SpinHalf();
  SpinHalf(const double gyromagnetic_ratio,
      const double field_strength,
      const ThreeVector & position);

  virtual UInt dimension() const;
  
  virtual SpinState eigenstate(const UInt level) const;
  virtual double energy(const UInt level) const; 
  
};

} // namespace SpinDec

#endif // SPINHALF_H_
