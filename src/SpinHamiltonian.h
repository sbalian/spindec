#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// SpinHamiltonian
//
// Effective spin Hamiltonian built from spin interaction graphs.
// Can diagonalize and get unitary time evolution matrix.
// Units: M rad s-1.
//
// Seto Balian, Dec 9, 2013

#include <Eigen/Dense>
#include <string>

#include "SpinInteractionGraph.h"
#include "SpinOperator.h"

class SpinHamiltonian : public SpinOperator
{
private:

  HermitianEigenspectrum eigenspectrum_; // eigenvectors and eigenvalues

  // Fill methods
  void fill(const SpinInteractionGraph & graph);

public:

  SpinHamiltonian();
  SpinHamiltonian(const SpinInteractionGraph & graph);
  // default diagonalizer "Eigen"
  SpinHamiltonian(const SpinInteractionGraph & graph,
      const std::string & diagonalizer);
  // see Eigenspectrum.h for diagonalizer types
  
  // TODO describe
  void update(const SpinInteractionGraph & graph);
  
  // Unitary matrix
  // U = \sum{n} ( |E_n> exp(- i E_n t) <E_n| )
  // E_n: eigenvalues
  // |E_n>: eigenvectors
  // t: time (real double) units: microseconds (energies in M rad s-1)
  Eigen::MatrixXcd evolutionMatrix(const double time) const;

};

#endif // SPINHAMILTONIAN_H_
