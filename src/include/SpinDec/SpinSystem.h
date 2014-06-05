#ifndef SPINSYSTEM_H_
#define SPINSYSTEM_H_

// SpinDec::SpinSystem
//
// Diagonalizable concrete spin system.
//
// Seto Balian, Jun 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/HermitianEigenspectrum.h"

namespace SpinDec
{

class SpinSystem : public SpinSystemBase
{
protected:
  void diagonalize(const string & diagonalizer);
  
  HermitianEigenspectrum eigenspectrum_;
  
  virtual void set_eigenstates();
  virtual void set_energies();
  
  virtual void check_level_label(const UInt level_label) const;
  
public:
  
  SpinSystem();
  SpinSystem(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);
  // default diagonalizer is "Lapack"
  SpinSystem(const SpinInteractionGraph & graph,
      const UniformMagneticField & field,
      const string& diagonalizer);

  virtual UInt dimension() const;
  
  virtual std::auto_ptr<SpinSystemBase> clone() const;
  
};

} // namespace SpinDec

#endif // SPINSYSTEM_H_
