#ifndef SPINSYSTEM_H_
#define SPINSYSTEM_H_

// SpinDec::SpinSystem
//
// Diagonalizable concrete spin system.
//
// Seto Balian, May 27, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/HermitianEigenspectrum.h"


namespace SpinDec
{

class SpinSystem : public SpinSystemBase
{
private:
  void diagonalize(const string & diagonalizer);
  
  HermitianEigenspectrum eigenspectrum_;
  
  virtual void set_eigenstates();
  virtual void set_energies();
  
  virtual void check_level(const UInt level) const;
  
public:
  
  SpinSystem();
  SpinSystem(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);
  // default diagonalizer is "Lapack"
  SpinSystem(const SpinInteractionGraph & graph,
      const UniformMagneticField & field,
      const string& diagonalizer);
  
  // Levels 1,2,3, ... dimension(Hamiltonian)
  virtual SpinState eigenstate(const UInt level) const;
  // energy eigenvalue in M rad s-1
  virtual double energy(const UInt level) const;
  
  virtual UInt dimension() const; // Hamiltonian dimension
  
};

} // namespace SpinDec

#endif // SPINSYSTEM_H_
