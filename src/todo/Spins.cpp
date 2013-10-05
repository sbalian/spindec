// Seto Balian 19/05/2013

#include "Named.h"
#include "Spin.h"
#include "Spins.h"

#include <vector>
#include <string>
#include <iostream>

#include <cstdlib>

#include <Eigen/Dense>

Spins::Spins() : Named()
{
//
}

Spins::Spins(const std::string & name) : Named(name)
{
//
}

Spins::Spins(const std::string & name, const Spin & spinToCopy,
             const unsigned int numberOfCopies) : Named(name)
{
  unsigned int i;
  for (i=0;i<numberOfCopies;i++) {
    spinVector_.push_back(spinToCopy);
  }
}

void Spins::add(const Spin & spinToAdd)
{
  spinVector_.push_back(spinToAdd);
  return;
}

bool Spins::empty() const
{
  if (spinVector_.empty()) {
    return 1;
  }
  return 0;
}

unsigned int Spins::numberOfSpins() const
{
  return static_cast<unsigned int>(spinVector_.size());
}

Spin Spins::getSpin(const unsigned int index) const
{
    if (index >= numberOfSpins()) {
      std::cout << error() << "Index to get Spin is out of bounds." <<std::endl;
      exit(1);
    }
    return spinVector_[index];
}

void Spins::print() const
{
  unsigned int i;
  if (empty()) {
    std::cout << error() << "Nothing to print." << std::endl;
    exit(1);
  }
  std::cout << "Spins: " << getName() << std::endl;
  for (i=0;i<numberOfSpins();i++) {
    spinVector_[i].print();
  }
  std::cout << std::endl;
  return;
}

// Method to calculate the dimension of the total Hilbert space using the
// multiplicities of the individual spins
unsigned int Spins::multiplicity() const {
  if (empty()) {
    std::cout << error() << "Need at least one Spin to calculate multiplicity.";
    std::cout << std::endl;
    exit(1);
  }
  unsigned int i;
  unsigned int dim = 1;
  unsigned int n = numberOfSpins();
  for (i=0;i<n;i++) {
    dim = dim*(spinVector_[i].multiplicity());
  }
  return dim;
}

void Spins::setSpin(const unsigned int index, const Spin & spinToSet)
{
  if (index >= numberOfSpins()) {
    std::cout << error() << "Index to set Spin is out of bounds." << std::endl;
    exit(1);
  }
  spinVector_[index] = spinToSet;
  return;
}

void Spins::buildZeemanBasis()
{
  // Construct the basis:
  // |m_0,m_1,m_2,...> where m_j are the magnetic quantum numbers for spin j.
  //
  // Represented as a square matrix:
  // COLS: Spin ID (slot in | >). No. of COLS = number of spins.
  // No. of ROWS = total dimension of the Hilbert space (using multiplicities)

  // Get number of spins and dimension of Hilbert space (using multiplicities)

  if (empty()) {
    std::cout << error() << "Need at least one Spin to build basis.";
    std::cout << std::endl;
    exit(1);
  }

  int n = static_cast<int>(numberOfSpins());
  int M = static_cast<int>(multiplicity());

  // Initialise basis to be built
  Eigen::MatrixXd basisToBuild(M,n);
  basisToBuild.setZero();

  // Preloop variables
  double spinQN = 0.0;
  int M_j = 0;      // Number of magnetic quantum numbers for j-th spin
  int M_0_to_j = 0; 
                // Number of magnetic quantum numbers of spin system up to and 
                // including the j-th spin

  int c_j = 0; // Number of adjacent copies of magnetic quantum numbers for the
           // j-th spin = M_0_to_j / M_j
  int C_j = 0; // Number of copies of set of magnetic quantum numbers for the
           // j-th spin = M / (c_j M_j^2)

  // Loop variables
  int j=0,m=0,p=0,q=0,l=0;

  M_0_to_j = 1;
  // Loop over spins
  // TODO: Explain this here.
  for (j=0;j<n;j++) {
    M_j = getSpin(j).multiplicity();
    M_0_to_j = M_0_to_j*M_j;

    C_j = M_0_to_j / M_j;
    c_j = M / (C_j * M_j);

    p = 0;
    l = 0;
    while (p<C_j) {
      spinQN = -getSpin(j).getSpinQuantumNumber();
      for (m=0;m<M_j;m++) {
        q = 0;
        while (q<c_j) {
          basisToBuild(l,j) = spinQN;
          l = l + 1;
          q = q + 1;
        }
        spinQN = spinQN + 1.0;
      }
      p = p + 1;
    }

  }

  // TODO Explain the minus here ...
  zeemanBasis_ = -basisToBuild;
  return;
}

// TODO Explain this method
void Spins::truncateZeemanBasisByTwoSpins(const unsigned int spinId1,
                                          const unsigned int spinId2,
                                      Eigen::ArrayXXd magneticQuantumNumbers) {

  if (numberOfSpins() < 2) {
    std::cout << error() << "Need at least two spins to truncate basis.";
    std::cout << std::endl;
    exit(1);
  }

  if (magneticQuantumNumbers.cols() != 2) {
    std::cout << error() << "Matrix magneticQuantumNumbers must have";
    std::cout << " two columns to truncate basis." << std::endl;
    exit(1);
  }

  if (dimension() == 0) {
    std::cout << error() << "Did you forget to build the basis before";
    std::cout << " truncating?" << std::endl;
    exit(1);
  }

  std::vector<Eigen::RowVectorXd> new_rows;

  int i,j;
  for (i=0;i<zeemanBasis_.rows();i++) {
    for (j=0;j<magneticQuantumNumbers.rows();j++) {
      if ((zeemanBasis_(i,spinId1) == magneticQuantumNumbers(j,0)) &&
         (zeemanBasis_(i,spinId2) == magneticQuantumNumbers(j,1))) {
        new_rows.push_back(zeemanBasis_.row(i));
      }
    }
  }

  Eigen::MatrixXd new_basis(static_cast<int>(new_rows.size()),
                                                        zeemanBasis_.cols());
  for (i=0;i<new_basis.rows();i++) {
    new_basis.row(i) = new_rows[i];
  }
  zeemanBasis_ = new_basis;
  return;
}

Eigen::MatrixXd Spins::getZeemanBasis() const {
  if ( dimension() == 0) {
    std::cout << error() << "Did you forget to build the basis?" << std::endl;
    exit(1);
  }
  return zeemanBasis_;
}

unsigned int Spins::dimension() const { // Number of basis vectors
  return static_cast<unsigned int>(zeemanBasis_.rows());
}

