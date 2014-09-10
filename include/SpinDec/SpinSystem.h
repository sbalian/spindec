#ifndef SPINSYSTEM_H_
#define SPINSYSTEM_H_

// SpinDec::SpinSystem
//
// Diagonalizable concrete spin system.
//
// Seto Balian, Sep 10, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/HermitianEigenspectrum.h"

namespace SpinDec
{

class SpinSystem : public SpinSystemBase
{
protected:
  void diagonalize();
  HermitianEigenspectrum eigenspectrum_;
  
  virtual void set_eigenstates();
  virtual void set_energies();
  
  virtual void check_level_label(const UInt level_label) const;
  
public:
  
  SpinSystem();
  SpinSystem(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);
  
  virtual UInt dimension() const;
  
  virtual auto_ptr<SpinSystemBase> clone() const;
  
  void update_positions(const UIntArray& vertex_labels,
      const vector<ThreeVector>& positions);
  
};

} // namespace SpinDec

#endif // SPINSYSTEM_H_
