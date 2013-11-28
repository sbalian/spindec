// See SpinBasis.h for description.
// Seto Balian, November 28, 2013

#include "SpinBasis.h"
#include "Errors.h"
#include "BoostEigen.h"

SpinBasis::SpinBasis()
{
  clear();
}

Eigen::ArrayXXd SpinBasis::get_basis() const
{
  return basis_;
}

void SpinBasis::set_basis(const Eigen::ArrayXXd & basis)
{
  basis_ = basis;
  return;
}

unsigned int SpinBasis::dimension() const
{
  return static_cast<unsigned int>(get_basis().rows());
}

unsigned int SpinBasis::num_spins() const
{
  return static_cast<unsigned int>(get_basis().cols());
}

void SpinBasis::clear()
{
  set_basis(Eigen::ArrayXXd::Zero(1,1));
}

SpinBasis SpinBasis::join(const SpinBasis & to_join) const
{
  SpinBasis out;
  Eigen::ArrayXXd lhs = get_basis();
  BoostEigen::horizontalAppend(lhs,to_join.get_basis());
  out.set_basis(lhs);
  return out;
}

void SpinBasis::build(const std::vector<Spin*> & spins)
{    
  int n = static_cast<int>(spins.size()); // number of spins
  int M = 1;  // total multiplicity
  for (unsigned int i=0;i<static_cast<unsigned int>(n);i++) {
    M *= spins[i]->multiplicity();
  }

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
    M_j = spins[j]->multiplicity();
    M_0_to_j = M_0_to_j*M_j;

    C_j = M_0_to_j / M_j;
    c_j = M / (C_j * M_j);

    p = 0;
    l = 0;
    while (p<C_j) {
      spin_QN = -spins[j]->get_quantum_number();
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
  
  set_basis(basis);
  return;

}


void SpinBasis::truncate(const std::vector<unsigned int> & spin_indices,
                    const Eigen::ArrayXXd & to_keep)
{  
  // checks
  
  const unsigned int to_keep_cols = static_cast<unsigned int>(to_keep.cols());

  if (static_cast<unsigned int>(to_keep_cols) != spin_indices.size()) {
    Errors::quit(
              "Number of spins != number of columns in \"to keep\" array");
  }
  
  const unsigned int original_dimension = dimension();
  
  // truncate

  std::vector<Eigen::ArrayXd> new_rows;
  
  const unsigned int to_keep_rows = static_cast<unsigned int>(to_keep.rows());
    
  for (unsigned int i = 0; i<to_keep_rows ; i++) { // loop over rows to keep
    
    // loop over rows in original basis to decide to keep or not
    for (unsigned int j=0; j<original_dimension;j++) {
      
      // construct test vector from original basis with the correct spin
      // magnetic quantum numbers (ie for those spins specified by spin_indices)
      Eigen::ArrayXd test_vector(to_keep_cols);
      for (unsigned int k=0;k<to_keep_cols;k++) {
        test_vector(k) = basis_(j,spin_indices[k]);
      }
      
      // see if test vector matches the row to keep and add to new rows if yes
      // @todo see if you can do something like this:
      // test_vector == to_keep.row(i)
      // above line does not compile
      bool pass = 1;
      for (unsigned int l = 0;l<to_keep_cols;l++) {
        if (test_vector(l) != to_keep(i,l)) {
          pass = 0; // if any of the elements don't match, reject
          break;
        }
      }
      if (pass) {
        new_rows.push_back(basis_.row(j)); 
      }
      
    }
 
  }
  
  // construct the new basis
  
  Eigen::ArrayXXd new_basis(static_cast<int>(new_rows.size()),
                            basis_.cols());
  
  for (unsigned int i=0; i<new_rows.size();i++) {
    new_basis.row(i) = new_rows[i];
  }
  
  basis_ = new_basis;
  return;

}
