// See SingleSpinBasis.h for description.
// Seto Balian, November 29, 2013

#include "SingleSpinBasis.h"

void SingleSpinBasis::build(const Spin & spin)
{
  const unsigned int multiplicity = spin.get_multiplicity();
  Eigen::ArrayXd basis(multiplicity);
  double element = spin.get_quantum_number();
  for (unsigned int i=0;i<multiplicity;i++) {
    basis(i) = element;
    element += 1.0;
  }
  basis_ = basis;
  return;
}

SingleSpinBasis::SingleSpinBasis()
{
  basis_ = Eigen::ArrayXd::Zero(1);
}

SingleSpinBasis::SingleSpinBasis(const Spin & spin)
{
  build(spin);
}

SingleSpinBasis::SingleSpinBasis(const Eigen::ArrayXd & basis)
{
  basis_ = basis;
}


//void SingleSpinBasis::combine_to(SpinBasis & basis) const
//{
//  
//  unsigned int old_dimension = basis.dimension();
//  unsigned int to_combine_dimension = dimension();
//  unsigned int new_dimension = old_dimension*to_combine_dimension;
//  unsigned int new_num_spins = basis.num_spins()+1;
//
//  // prepare new basis
//  Eigen::ArrayXXd new_basis(new_dimension,new_num_spins);
//  new_basis.setZero();
//  
//  // loop over elements of new basis and fill old elements repeated in rows
//  // to_combine_dimension times
//  // (last column left empty for new spin)
//  for (unsigned int i=0;i<basis.num_spins();i++) { // loop over old columns
//    unsigned int l = 0; // new row index
//    for (unsigned int j=0;j<old_dimension;j++) { // loop over old rows
//      
//      unsigned int k=0;
//      while (k<to_combine_dimension) { // loop to_combine_dimension times
//        new_basis(l,i) = basis.get_basis()(j,i);
//        l += 1;
//        k += 1;
//      }
//      
//    }
//  }
//  
//  // last column of new basis: new column
//  Eigen::ArrayXd new_column(new_dimension);
//  new_column.setZero();
//  
//  // fill new column: new elements repeated old_dimension times
//  unsigned int l = 0; // new row index
//  for (unsigned int i = 0;i<old_dimension;i++) {
//    unsigned int k = 0;
//    while (k<to_combine_dimension) {
//        new_column(l) = get_basis()(k);
//        k+=1;
//        l+=1;
//      }
//  }
//  
//  // set new column
//  new_basis.col(basis.num_spins()) = new_column; 
//  // set new basis
//  basis.set_basis(new_basis);
//  return;
//}
