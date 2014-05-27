#ifndef SPINSYSTEMBASE_H_
#define SPINSYSTEMBASE_H_

// SpinDec::SpinSystem
//
// Abstract base class for spin systems.
//
// Seto Balian, May 27, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinInteractionGraph.h"
#include "SpinDec/SpinHamiltonian.h"

#include "SpinDec/UniformMagneticField.h"

#include "SpinDec/SpinState.h"

namespace SpinDec
{

class SpinSystemBase
{
protected:
  SpinInteractionGraph graph_;
  SpinHamiltonian hamiltonian_;

  UniformMagneticField field_;
  
  RealVector energies_;
  ComplexMatrix eigenstates_;
  
  // calculate and set ...
  virtual void set_eigenstates() = 0;
  virtual void set_energies() = 0;
  
  virtual void check_level(const UInt level) const = 0;
  
public:
  SpinSystemBase();
  SpinSystemBase(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);
  
  const UniformMagneticField& get_field() const;

  // Levels 1,2,3, ... dimension(Hamiltonian)
  // some levels may be excluded!
  virtual SpinState eigenstate(const UInt level) const = 0;
  // energy eigenvalue in M rad s-1
  virtual double energy(const UInt level) const = 0; 

  SpinOperator evolution_operator(const double time) const;
  
  virtual UInt dimension() const = 0; // Hamiltonian dimension
  
  //SpinSystemBase join( const SpinSystem & t_join);
  
  // options:
  // e - energies
  // E - eigenstates
  // H - Hamiltonian
  void print(const char option);
  
  virtual ~SpinSystemBase();
  
};

} // namespace SpinDec

#endif // SPINSYSTEMBASE_H_
