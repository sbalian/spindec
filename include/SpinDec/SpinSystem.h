#ifndef SPINSYSTEM_H_
#define SPINSYSTEM_H_

// SpinDec::SpinSystem
//
// Diagonalizable concrete spin system.
//
// Seto Balian, Oct 23, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"

#include "SpinDec/HermitianEigenspectrum.h"

namespace SpinDec
{

class SpinSystem : public SpinSystemBase
{
protected:
    
  HermitianEigenspectrum eigenspectrum_;
  
  virtual void solve_once();
  
  virtual void check_level_label(const UInt level_label) const;
  
public:
  
  SpinSystem();
  explicit SpinSystem(const SpinHamiltonian& hamiltonian);
  
  virtual UInt dimension() const;
  
  virtual auto_ptr<SpinSystemBase> clone() const;
  
  
};

} // namespace SpinDec

#endif // SPINSYSTEM_H_
