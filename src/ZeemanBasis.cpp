// See ZeemanBasis.h for description.
// Seto Balian 24/10/2013

// TODO Explain any conventions here ...

#include <Eigen/Dense>
#include <vector>

#include "ZeemanBasis.h"
#include "Spins.h"
#include "Spin.h"
#include "Errors.h"

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

// TODO Explain this method
void ZeemanBasis::build() {

  int n = static_cast<int>(spins_.num_spins());
  int M = static_cast<int>(spins_.multiplicity());

  // Initialise basis to be built
  Eigen::ArrayXXd basis(M,n);
  basis.setZero();

  // Preloop variables
  double spin_QN = 0.0;
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
  // TODO: Explain here
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

  return;

}

// TODO Explain this method
////void ZeemanBasis::truncate(const std::vector<unsigned int> & spin_indices,
////                    const Eigen::ArrayXXd & to_keep) {

////  if (to_keep.cols() != spin_indices.size()) {
////    quit("Number of spins != number of columns in 'to keep' array");
////  }

////  if (dimension() == 0) {
////    quit("Did you forget to build the basis before truncating?");
////  }


////  std::vector<Eigen::ArrayXd> new_rows;

////  bool keep_row = 0;

////  for (unsigned int i =0; i<spin_indices.size(); i ++ ) {

////    for (unsigned int j = 0; j<dimension() ; j++) {

////      keep_row = 1;
////      if (basis_(j,spin_indices[i]) != to_keep(j,i) ) {
////        keep_row = 0;
////      }

////    }

////    

////  }

////  return;

////}


// TODO Explain this method
////////void Spins::truncateZeemanBasisByTwoSpins(const unsigned int spinId1,
////////                                          const unsigned int spinId2,
////////                                      Eigen::ArrayXXd magneticQuantumNumbers) {





////////  std::vector<Eigen::RowVectorXd> new_rows;

////////  int i,j;
////////  for (i=0;i<zeemanBasis_.rows();i++) {
////////    for (j=0;j<magneticQuantumNumbers.rows();j++) {
////////      if ((zeemanBasis_(i,spinId1) == magneticQuantumNumbers(j,0)) &&
////////         (zeemanBasis_(i,spinId2) == magneticQuantumNumbers(j,1))) {
////////        new_rows.push_back(zeemanBasis_.row(i));
////////      }
////////    }
////////  }

////////  Eigen::MatrixXd new_basis(static_cast<int>(new_rows.size()),
////////                                                        zeemanBasis_.cols());
////////  for (i=0;i<new_basis.rows();i++) {
////////    new_basis.row(i) = new_rows[i];
////////  }
////////  zeemanBasis_ = new_basis;
////////  return;
////////}

unsigned int ZeemanBasis::dimension() const {
  return static_cast<unsigned int>(basis_.rows());
}





