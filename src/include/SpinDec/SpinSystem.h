#ifndef SPINSYSTEM_H_
#define SPINSYSTEM_H_

// SpinDec::SpinSystem
//
// This has a spin interaction graph together with it's spin Hamiltonian.
// Energy levels counted in increasing energy starting from 1!
//
// Seto Balian, May 21, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinInteractionGraph.h"
#include "SpinDec/SpinHamiltonian.h"
#include "SpinDec/HermitianEigenspectrum.h"

#include "SpinDec/UniformMagneticField.h"

#include "SpinState.h"
#include "SpinOperator.h"

namespace SpinDec
{

class SpinSystem
{
private:
  SpinInteractionGraph graph_;
  SpinHamiltonian hamiltonian_;
  HermitianEigenspectrum eigenspectrum_;
  
  UniformMagneticField field_;

  bool is_diagonalized_;
  string diagonalizer_; // default is "Lapack"
  
  void diagonalize();

public:
  SpinSystem();
  SpinSystem(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);
  
  SpinState eigenstate(const UInt level);
  double energy(const UInt level);
  
  const UniformMagneticField& get_field() const;
  
  void set_diagonalizer(const string & diagonalizer);
  
  SpinOperator evolution_operator(const double time);
  
  UInt dimension() const; // Hamiltonian dimension
  
  // options:
  // e - energies
  // E - eigenstates
  // H - Hamiltonian
  void print(const char option);
  
};

} // namespace SpinDec

#endif // SPINSYSTEM_H_
