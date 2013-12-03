// See SingleSpinBasis.h for description.
// Seto Balian, Dec 3, 2013

#include "SingleSpinBasis.h"
#include "BoostEigen.h"

void SingleSpinBasis::build(const Spin & spin)
{
  SpinBasis::build(SpinVector(spin));
}

SingleSpinBasis::SingleSpinBasis() : SpinBasis() {/**/}

SingleSpinBasis::SingleSpinBasis(const Spin & spin)
{
  build(spin);
}

SingleSpinBasis::SingleSpinBasis(const Eigen::ArrayXd & basis) :
  SpinBasis(basis)
{/**/} // TODO is this OK? ArrayXd vs ArrayXXd

unsigned int SingleSpinBasis::num_spins() const
{
  return 1;
}

double SingleSpinBasis::get_element(const unsigned int row) const
{
  return SpinBasis::get_element(row,0);
}

SpinBasis SingleSpinBasis::join(const SingleSpinBasis & to_join) const
{
  Eigen::ArrayXXd lhs = get_basis();
  Eigen::ArrayXXd rhs = to_join.get_basis();
  BoostEigen::horizontalAppend(lhs,rhs);
  return SpinBasis(lhs);
}


SpinBasis SingleSpinBasis::combine(const SpinBasis & basis) const
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
  // return SpinBasis with new basis
  return SpinBasis(new_basis);
}
