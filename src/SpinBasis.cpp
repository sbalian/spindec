// See SpinBasis.h for description.
// Seto Balian, Apr 2, 2014

#include "SpinDec/SpinBasis.h"
#include "SpinDec/Errors.h"

#include <iomanip>

namespace SpinDec
{

Eigen::ArrayXXd SpinBasis::build(
    const SpinParametersVector & spin_parameters_vector)
{
  
  int n = static_cast<int>(spin_parameters_vector.size()); // number of spins
  int M = static_cast<int>(spin_parameters_vector.multiplicity());
                                                    // total multiplicity
    
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
    M_j = spin_parameters_vector[j].get_multiplicity();
    if (M_j == 0.0) {continue;} // ! TODO STUPID - FIXME PLEASE!
                               // This happens if a spin quantum number is zero.
                              // The default constructor for SpinParameters
                              // sets the quantum number to zero.
                              // Make sure all default constructors lead to well
                              // defined behavior!!!

    M_0_to_j = M_0_to_j*M_j;
    
    C_j = M_0_to_j / M_j;
    c_j = M / (C_j * M_j);

    p = 0;
    l = 0;
    while (p<C_j) {
      spin_QN = -spin_parameters_vector[j].get_quantum_number();
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

Eigen::ArrayXXd SpinBasis::build(const SpinParameters & spin_parameters)
{
  SpinParametersVector temp;
  temp.push_back(spin_parameters);
  return build(temp);
}

SpinBasis::SpinBasis() :
    basis_as_array_(Eigen::ArrayXXd::Zero(0,0)) // TODO Is this OK?
{/**/}

SpinBasis::SpinBasis(const SpinParametersVector& spin_parameters_vector) :
    basis_as_array_(build(spin_parameters_vector))
{/**/}

SpinBasis::SpinBasis(const SpinParameters& spin_parameters) :
    basis_as_array_(build(spin_parameters))
{/**/}

SpinBasis::SpinBasis(const Eigen::ArrayXXd & basis_as_array) :
        basis_as_array_(basis_as_array)
{/**/}

const Eigen::ArrayXXd& SpinBasis::get_basis_as_array() const
{
  return basis_as_array_;
}

UInt SpinBasis::num_basis_states() const
{
  return static_cast<int>(basis_as_array_.rows());
}

UInt SpinBasis::num_spins() const
{
  return static_cast<int>(basis_as_array_.cols());
}

double SpinBasis::get_element(const UInt index,
        const UInt slot) const
{
  return basis_as_array_(index,slot);
}

SpinBasis SpinBasis::operator+(const SpinBasis & to_append) const
{
  if (num_basis_states() != to_append.num_basis_states()) {
    Errors::quit("Number of basis states mismatch when joining bases.");
  }
  Eigen::ArrayXXd appended(num_basis_states(),
      num_spins() +to_append.num_spins());
  appended << basis_as_array_, to_append.basis_as_array_;
  return SpinBasis(appended);
}

SpinBasis SpinBasis::operator^(const SpinBasis & to_combine) const
{
  
  // consistently with BoostEigen methods for linear algebra
  
  // C = A.combine(B)
  
  UInt num_basis_states_A = num_basis_states();
  UInt num_basis_states_B = to_combine.num_basis_states();
  UInt num_basis_states_C = num_basis_states_A*num_basis_states_B;
  UInt new_num_spins = num_spins() + to_combine.num_spins();

  // prepare expanded basis A with zero elements
  Eigen::ArrayXXd expanded_basis_A(num_basis_states_C,num_spins());
  expanded_basis_A.setZero();
  
  // loop over elements of expanded basis A and fill A elements
  // repeated in rows num_basis_states_B times
  for (UInt i=0;i<num_spins();i++) { // loop over A columns
    UInt l = 0; // new row index
    for (UInt j=0;j<num_basis_states_A;j++) { // loop over A rows
      UInt k=0;
      while (k<num_basis_states_B) { // loop num_basis_states_B times
        expanded_basis_A(l,i) = get_basis_as_array()(j,i);
        l += 1;
        k += 1;
      }
      
    }
  }
  
  
  // new columns from B
  Eigen::ArrayXXd new_columns_B(num_basis_states_C,to_combine.num_spins());
  new_columns_B.setZero();
  
  
  // fill new columns: new rows repeated num_basis_states_B times
  UInt l = 0; // new row index
  for (UInt i = 0;i<num_basis_states_A;i++) {
    UInt k = 0;
    while (k<num_basis_states_B) {
        new_columns_B.row(l) = to_combine.get_basis_as_array().row(k);
        k+=1;
        l+=1;
      }
  }
    
  // return SpinBasis with new basis
  Eigen::ArrayXXd basis_out(num_basis_states_C,new_num_spins);
  basis_out << expanded_basis_A, new_columns_B; // join  
  return SpinBasis(basis_out);
}

bool SpinBasis::operator==(const SpinBasis to_compare) const
{
  if (to_compare.num_spins() != num_spins())
  {
    return false;
  }
  if (to_compare.num_basis_states() != num_basis_states())
  {
    return false;
  }
  for (UInt i = 0; i<num_spins(); i++) {
    for (UInt j=0; j<num_basis_states();j++) {
      if (get_element(j,i) != to_compare.get_element(j,i)) {
        return false;
      }
    }
  }
  return true;
}

std::ostream& operator<<(std::ostream& os, SpinBasis const & basis)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << basis.get_basis_as_array() << std::endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}

} // namespace SpinDec

// GRAVEYARD
// OLD + Don't use this even if you update it ...

//void SpinBasis::truncate(const std::vector<UInt> & spin_indices,
//                    const Eigen::ArrayXXd & to_keep)
//{  
//  // checks
//  
//  const UInt to_keep_cols = static_cast<UInt>(to_keep.cols());
//
//  if (static_cast<UInt>(to_keep_cols) != spin_indices.size()) {
//    Errors::quit(
//              "Number of spins != number of columns in \"to keep\" array");
//  }
//  
//  const UInt original_num_basis_states = num_basis_states();
//  
//  // truncate
//
//  std::vector<Eigen::ArrayXd> new_rows;
//  
//  const UInt to_keep_rows = static_cast<UInt>(to_keep.rows());
//    
//  for (UInt i = 0; i<to_keep_rows ; i++) { // loop over rows to keep
//    
//    // loop over rows in original basis to decide to keep or not
//    for (UInt j=0; j<original_num_basis_states;j++) {
//      
//      // construct test vector from original basis with the correct spin
//    // magnetic quantum numbers (ie for those spins specified by spin_indices)
//      Eigen::ArrayXd test_vector(to_keep_cols);
//      for (UInt k=0;k<to_keep_cols;k++) {
//        test_vector(k) = basis_as_array_(j,spin_indices[k]);
//      }
//      
//      // see if test vector matches the row to keep and add to new rows if yes
//      // TODO see if you can do something like this:
//      // test_vector == to_keep.row(i)
//      // above line does not compile
//      bool pass = 1;
//      for (UInt l = 0;l<to_keep_cols;l++) {
//        if (test_vector(l) != to_keep(i,l)) {
//          pass = 0; // if any of the elements don't match, reject
//          break;
//        }
//      }
//      if (pass) {
//        new_rows.push_back(basis_as_array_.row(j)); 
//      }
//      
//    }
// 
//  }
//  
//  // construct the new basis
//  
//  Eigen::ArrayXXd new_basis(static_cast<int>(new_rows.size()),
//                            basis_as_array_.cols());
//  
//  for (UInt i=0; i<new_rows.size();i++) {
//    new_basis.row(i) = new_rows[i];
//  }
//  
//  basis_as_array_ = new_basis;
//  return;
//
//}
// // OLD TEST CODE FOR THIS METHOD ...
//ZeemanBasis test_basis;
//test_basis.build(graph);
//
//std::cout << "basis" << std::endl;
//std::cout << test_basis.get_basis_as_array() << std::endl;
//
//Eigen::ArrayXXd to_keep(3,2);
//
//to_keep << 0.5 , 4.5,
//          -0.5, 2.5,
//           0.5, -1.5;
//
//std::vector<UInt> indices;
//
//indices.push_back(0);
//indices.push_back(1);
//
//test_basis.truncate(indices,to_keep);
//
//std::cout << "truncated" << std::endl;
//std::cout << test_basis.get_basis_as_array() << std::endl;

