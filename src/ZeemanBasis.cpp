// See ZeemanBasis.h for description.
// Seto Balian 01/11/2013

#include <Eigen/Dense>
#include <vector>

#include "ZeemanBasis.h"
#include "Spins.h"
#include "Spin.h"
#include "Errors.h"

ZeemanBasis::ZeemanBasis() {
  //
}

ZeemanBasis::ZeemanBasis(const Spins & spins,
                                        const Eigen::ArrayXXd & basis) {
  set_spins(spins);
  set_basis(basis); 
}

Spins ZeemanBasis::get_spins()    const {
  return spins_;
}

Eigen::ArrayXXd ZeemanBasis::get_basis() const {
  return basis_;
}

void ZeemanBasis::set_spins(const Spins & spins) {
  spins_ = spins;
  return;
}

void ZeemanBasis::set_basis(const Eigen::ArrayXXd & basis) {
  basis_ = basis;
}

void ZeemanBasis::build() {
  
  int n = static_cast<int>(spins_.num_spins()); // number of spins
  int M = static_cast<int>(spins_.multiplicity()); // total multiplicity

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
    M_j = spins_.get_spin(j).multiplicity();
    M_0_to_j = M_0_to_j*M_j;

    C_j = M_0_to_j / M_j;
    c_j = M / (C_j * M_j);

    p = 0;
    l = 0;
    while (p<C_j) {
      spin_QN = -spins_.get_spin(j).get_quantum_number();
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

void ZeemanBasis::truncate(const std::vector<unsigned int> & spin_indices,
                    const Eigen::ArrayXXd & to_keep) {

  if (static_cast<unsigned int>(to_keep.cols()) != spin_indices.size()) {
    Errors::quit("Number of spins != number of columns in \"to keep\" array");
  }

  if (dimension() == 0) {
    Errors::quit("Did you forget to build the basis before truncating?");
  }


  std::vector<Eigen::ArrayXd> new_rows;
    
  for (unsigned int i = 0; i<dimension() ; i++) { // loop over original rows to
                                                  // decide to keep an original
                                                  // row or not
    
    bool keep_row = 0; // do not keep
    
    // loop over rows to keep
    for (unsigned int j=0; j<static_cast<unsigned int>(to_keep.rows());j++) {
      
      // see if the original row matches any one of the rows to keep
      for (unsigned int k=0; k<spin_indices.size(); k++ ) {
        
        // see if ALL elements in a row to keep match with the corresponding
        // ones in the original row
        
        keep_row = 1; // keep the row, unless ...
        if ( basis_(i,spin_indices[k]) != to_keep(j,k) ) { // ... any of the
                                                           // elements don't
                                                           // match
          keep_row = 0;
          break;
        }
        
      }
      
      if (keep_row == 1) {break;} // found a row, don't bother looking
                
    }
 
    if (keep_row == 1) { // keep the original row
      new_rows.push_back(basis_.row(i));
    }
    
  }
  
  Eigen::ArrayXXd new_basis(static_cast<int>(new_rows.size()),
                            basis_.cols());
  
  for (unsigned int i=0; i<new_rows.size();i++) {
    new_basis.row(i) = new_rows[i];
  }
  
  set_basis(new_basis);
  
  return;

}


unsigned int ZeemanBasis::dimension() const {
  return static_cast<unsigned int>(basis_.rows());
}
