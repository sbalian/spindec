#ifndef SPINHAMILTONIAN_H
#define SPINHAMILTONIAN_H

// Static methods to fill a spin Hamiltonian
//
// Created  04/09/2012
// Modified 19/09/2012, 20/09/2012, 22/09/2012, 26/09/2012, 27/09/2012, 28/09/2012, 02/10/2012, 18/03/2013, 16/05/2013
// Modified 17/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "spins.hpp"
#include "qoperator.hpp"

using namespace Eigen;

class spinHamiltonian
{

public:

   static void Dipolar(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                       const int spin_ID_1, const int spin_ID_2, const double strength);
                                                                          // dipolar

   static void Dipolar(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                       const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only);
                                                                          // dipolar

   static void Ising(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                     const int spin_ID_1, const int spin_ID_2, const double strength);
                                                                          // hyperfine

   static void IsoHyperfine(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                             const int spin_ID_1, const int spin_ID_2, const double strength);
                                                                          // hyperfine

   static void IsoHyperfine(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                             const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only);
                                                                          // hyperfine

//   static void IsoHyperfine(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
//                             const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only,
//                             const int truncation_spin_ID_1, const int truncation_spin_ID_2,
//                             const int leaking_spin_ID);

//   static void Dipolar(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
//                       const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only,
//                             const int truncation_spin_ID_1, const int truncation_spin_ID_2,
//                             const int leaking_spin_ID);

   static void Zeeman(qoperator & hamiltonian, const spins & spins_in, const MatrixXd high_field_basis, const double magnetic_field);

};

#endif // SPINHAMILTONIAN_H


