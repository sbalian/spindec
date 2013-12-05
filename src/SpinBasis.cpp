// See SpinBasis.h for description.
// Seto Balian, Dec 5, 2013

#include "SpinBasis.h"

Eigen::ArrayXXd SpinBasis::build(const SpinVector & spin_vector) const
{
  int n = static_cast<int>(spin_vector.size()); // number of spins
  int M = static_cast<int>(spin_vector.get_multiplicity());// total multiplicity

  // Initialise basis to be built
  Eigen::ArrayXXd basis(M,n);
  basis.setZero();
  
  // For example, for 2 electrons, the algorithm below will build
                          //           0.5  0.5
                          //           0.5 -0.5
                          //          -0.5  0.5
                          //          -0.5 -0.5
  // where the magnetic quantum numbers (+/- 0.5 here) are evaluated
  // from the multiplicites of spins represented by column 1 and 2
  // (both spin-1/2 in this case)

  // declare algorithm parameters
  double spin_QN = 0.0; // basis element
  int M_j = 0;      // Number of magnetic quantum numbers for j-th spin
  int M_0_to_j = 0; 
                // Number of magnetic quantum numbers of spin system up to and 
                // including the j-th spin

  int c_j = 0; // Number of adjacent copies of magnetic quantum numbers for the
           // j-th spin = M_0_to_j / M_j
  int C_j = 0; // Number of copies of set of magnetic quantum numbers for the
           // j-th spin = M / (c_j M_j^2)

  // loop variables
  int j=0,m=0,p=0,q=0,l=0;

  M_0_to_j = 1;
  // Loop over spins
  for (j=0;j<n;j++) {
    M_j = spin_vector.get_spin(j).get_multiplicity();
    M_0_to_j = M_0_to_j*M_j;

    C_j = M_0_to_j / M_j;
    c_j = M / (C_j * M_j);

    p = 0;
    l = 0;
    while (p<C_j) {
      spin_QN = -spin_vector.get_spin(j).get_quantum_number();
      for (m=0;m<M_j;m++) {
        q = 0;
        while (q<c_j) {
          basis(l,j) = -spin_QN;
          l += 1;
          q += 1;
        }
        spin_QN += 1.0;
      }
      p += 1;
    }
  }

  return basis;

}

SpinBasis::SpinBasis() {/**/}

SpinBasis::SpinBasis(const SpinVector & spin_vector)
{
  basis_ = build(spin_vector);
}

SpinBasis::SpinBasis(const Eigen::ArrayXXd & basis)
{
  basis_ = basis;
}

Eigen::ArrayXXd SpinBasis::get_basis() const
{
  return basis_;
}

unsigned int SpinBasis::dimension() const
{
  return static_cast<int>(basis_.rows());
}

unsigned int SpinBasis::num_spins() const
{
  return static_cast<int>(basis_.cols());
}

double SpinBasis::get_element(const unsigned int index,
        const unsigned int slot) const
{
  return basis_(index,slot);
}

SpinBasis SpinBasis::operator+(const SpinBasis & to_join) const
{
  Eigen::ArrayXXd joined(dimension(),num_spins() + to_join.num_spins());
  joined << basis_, to_join.basis_;
  return joined;
}

SpinBasis SpinBasis::operator^(const SpinBasis & to_combine) const
{
  
  // consistently with BoostEigen methods for linear algebra
  
  // C = A.combine(B)
  
  unsigned int dimension_A = dimension();
  unsigned int dimension_B = to_combine.dimension();
  unsigned int dimension_C = dimension_A*dimension_B;
  unsigned int new_num_spins = num_spins() + to_combine.num_spins();

  // prepare expanded basis A with zero elements
  Eigen::ArrayXXd expanded_basis_A(dimension_C,num_spins());
  expanded_basis_A.setZero();
  
  // loop over elements of expanded basis A and fill A elements
  // repeated in rows dimension_B times
  for (unsigned int i=0;i<num_spins();i++) { // loop over A columns
    unsigned int l = 0; // new row index
    for (unsigned int j=0;j<dimension_A;j++) { // loop over A rows
      unsigned int k=0;
      while (k<dimension_B) { // loop dimension_B times
        expanded_basis_A(l,i) = get_basis()(j,i);
        l += 1;
        k += 1;
      }
      
    }
  }
  
  
  // new columns from B
  Eigen::ArrayXXd new_columns_B(dimension_C,to_combine.num_spins());
  new_columns_B.setZero();
  
  
  // fill new columns: new rows repeated dimension_B times
  unsigned int l = 0; // new row index
  for (unsigned int i = 0;i<dimension_A;i++) {
    unsigned int k = 0;
    while (k<dimension_B) {
        new_columns_B.row(l) = to_combine.get_basis().row(k);
        k+=1;
        l+=1;
      }
  }
    
  // return SpinBasis with new basis
  Eigen::ArrayXXd basis_out(dimension_C,new_num_spins);
  basis_out << expanded_basis_A, new_columns_B; // join  
  return SpinBasis(basis_out);
}

SpinBasis::~SpinBasis() {/**/}

// Don't use this ...
//void SpinBasis::truncate(const std::vector<unsigned int> & spin_indices,
//                    const Eigen::ArrayXXd & to_keep)
//{  
//  // checks
//  
//  const unsigned int to_keep_cols = static_cast<unsigned int>(to_keep.cols());
//
//  if (static_cast<unsigned int>(to_keep_cols) != spin_indices.size()) {
//    Errors::quit(
//              "Number of spins != number of columns in \"to keep\" array");
//  }
//  
//  const unsigned int original_dimension = dimension();
//  
//  // truncate
//
//  std::vector<Eigen::ArrayXd> new_rows;
//  
//  const unsigned int to_keep_rows = static_cast<unsigned int>(to_keep.rows());
//    
//  for (unsigned int i = 0; i<to_keep_rows ; i++) { // loop over rows to keep
//    
//    // loop over rows in original basis to decide to keep or not
//    for (unsigned int j=0; j<original_dimension;j++) {
//      
//      // construct test vector from original basis with the correct spin
//      // magnetic quantum numbers (ie for those spins specified by spin_indices)
//      Eigen::ArrayXd test_vector(to_keep_cols);
//      for (unsigned int k=0;k<to_keep_cols;k++) {
//        test_vector(k) = basis_(j,spin_indices[k]);
//      }
//      
//      // see if test vector matches the row to keep and add to new rows if yes
//      // TODO see if you can do something like this:
//      // test_vector == to_keep.row(i)
//      // above line does not compile
//      bool pass = 1;
//      for (unsigned int l = 0;l<to_keep_cols;l++) {
//        if (test_vector(l) != to_keep(i,l)) {
//          pass = 0; // if any of the elements don't match, reject
//          break;
//        }
//      }
//      if (pass) {
//        new_rows.push_back(basis_.row(j)); 
//      }
//      
//    }
// 
//  }
//  
//  // construct the new basis
//  
//  Eigen::ArrayXXd new_basis(static_cast<int>(new_rows.size()),
//                            basis_.cols());
//  
//  for (unsigned int i=0; i<new_rows.size();i++) {
//    new_basis.row(i) = new_rows[i];
//  }
//  
//  basis_ = new_basis;
//  return;
//
//}
