#ifndef SPINS_H
#define SPINS_H

// Spins <- Named
//
// For multiple Spin objects. Contains high-field (Zeeman) basis.
//
// Seto Balian 19/05/2013

#include "Named.h"
#include "Spin.h"

#include <vector>
#include <string>

#include <Eigen/Dense>

class Spins : public Named
{

private:
  std::vector<Spin> spinVector_;
  Eigen::MatrixXd zeemanBasis_; // Product states of high-field eigenstates
                                // (labeled with the magnetic quantum numbers)

public:

  Spins();
  Spins(const std::string & name);

  Spins(const std::string & name, const Spin & spinToCopy,
        const unsigned int numberOfCopies);

  void add(const Spin & spinToAdd);

  bool empty() const;

  unsigned int numberOfSpins() const;

  Spin getSpin(const unsigned int index) const;

  void print() const;

  unsigned int multiplicity() const;

  void setSpin(const unsigned int index, const Spin & spinToSet);

  void buildZeemanBasis();

  void truncateZeemanBasisByTwoSpins(const unsigned int spinId1,
                                     const unsigned int spinId2,
                                     Eigen::ArrayXXd magneticQuantumNumbers);

  Eigen::MatrixXd getZeemanBasis() const;

  unsigned int dimension() const; // Number of basis vectors
  
};

#endif // SPINS_H

