#ifndef ZEEMANBASIS_H
#define ZEEMANBASIS_H

// ZeemanBasis
//
// Holds magnetic quantum numbers (Zeeman basis).
// TODO Explain any conventions here ...
//
// Seto Balian 24/10/2013

#include <Eigen/Dense>
#include <vector>

#include "Spins.h"

class ZeemanBasis
{

private:
  Eigen::ArrayXXd basis_; // Zeeman basis. Columns -> Spins. TODO Explain this
  Spins spins_;

public:

  ZeemanBasis();
  ZeemanBasis(const Spins & spins, const Eigen::ArrayXXd & basis);

  Spins get_spins()    const;
  Eigen::ArrayXXd get_basis() const;

  void set_spins(const Spins & spins);
  void set_basis(const Eigen::ArrayXXd & basis);

  void build();

  void truncate(const std::vector<unsigned int> & spin_indices,
                      const Eigen::ArrayXXd & to_keep);

  unsigned int dimension() const;

};

#endif // ZEEMANBASIS_H

