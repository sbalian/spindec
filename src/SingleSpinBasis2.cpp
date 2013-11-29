// See SingleSpinBasis.h for description.
// Seto Balian, November 28, 2013

#include "SingleSpinBasis.h"
#include "BoostEigen.h"

#include <vector>


SingleSpinBasis::SingleSpinBasis()
{
  SingleSpinBasis::clear();
}

void SpinBasis::clear()
{
  // @todo what is the difference between this and
  // Eigen::ArrayXd::Zero(1,1) ... when I return ArrayXXd what will it return?
  SpinBasis::set_basis(Eigen::ArrayXd::Zero(1,1));
}

void SingleSpinBasis::add_magnetic_quantum_number(
                                  const double magnetic_quantum_number)
{
  //@todo now get_basis() returns ArrayXXd  and this is set to ArrayXd, what
  // is happening with Eigen?
  Eigen::ArrayXd basis = SpinBasis::get_basis();
  BoostEigen::addElement(basis,magnetic_quantum_number);
  SpinBasis::set_basis(basis);
  return;
}

void SingleSpinBasis::build(const Spin* spin)
{
  std::vector<const Spin*> spins;
  spins.push_back(spin);
  SpinBasis::build(spins);
  return;
}

void SingleSpinBasis::combine_to(SpinBasis & basis) const
{
  
  unsigned int old_dimension = basis.dimension();
  unsigned int to_combine_dimension = dimension();
  unsigned int new_dimension = old_dimension*to_combine_dimension;
  unsigned int new_num_spins = basis.num_spins()+1;

  // prepare new basis
  Eigen::ArrayXXd new_basis(new_dimension,new_num_spins);
  new_basis.setZero();
  
  // loop over elements of new basis and fill old elements repeated in rows
  // to_combine_dimension times
  // (last column left empty for new spin)
  for (unsigned int i=0;i<basis.num_spins();i++) { // loop over old columns
    unsigned int l = 0; // new row index
    for (unsigned int j=0;j<old_dimension;j++) { // loop over old rows
      
      unsigned int k=0;
      while (k<to_combine_dimension) { // loop to_combine_dimension times
        new_basis(l,i) = basis.get_basis()(j,i);
        l += 1;
        k += 1;
      }
      
    }
  }
  
  // last column of new basis: new column
  Eigen::ArrayXd new_column(new_dimension);
  new_column.setZero();
  
  // fill new column: new elements repeated old_dimension times
  unsigned int l = 0; // new row index
  for (unsigned int i = 0;i<old_dimension;i++) {
    unsigned int k = 0;
    while (k<to_combine_dimension) {
        new_column(l) = get_basis()(k);
        k+=1;
        l+=1;
      }
  }
  
  // set new column
  new_basis.col(basis.num_spins()) = new_column; 
  // set new basis
  basis.set_basis(new_basis);
  return;
}
