#ifndef SPINHALF_H_
#define SPINHALF_H_

// SpinDec::SpinHalf
//
// A spin-1/2 spin system.
//
// Seto Balian, Sep 24, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"

namespace SpinDec
{

class SpinHalf : public SpinSystemBase
{
  
private:

  double gyromagnetic_ratio_;
  
  virtual void solve_once();
  
  virtual void check_level_label(const UInt level_label) const;

public:
  SpinHalf();
  SpinHalf(const double gyromagnetic_ratio,
      const double field_strength,
      const ThreeVector & position);

  virtual UInt dimension() const;
  
  virtual auto_ptr<SpinSystemBase> clone() const;
  
};

} // namespace SpinDec

#endif // SPINHALF_H_