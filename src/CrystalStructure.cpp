// See CrystalStructure.h for description.
// Seto Balian, Apr 3, 2014

#include "SpinDec/CrystalStructure.h"
#include "SpinDec/FileProperties.h"
#include "SpinDec/Errors.h"
#include "SpinDec/BoostEigen.h"

#include <fstream>
#include <iomanip>

#include <algorithm>

namespace SpinDec
{

void CrystalStructure::add_site_vector(const ThreeVector & site_vector)
{
  site_vectors_.push_back(site_vector);
  return;
}

void CrystalStructure::scale_site_vectors(const double scale_factor)
{
  for (UInt i=0;i<num_site_vectors();i++) {
    site_vectors_[i]*= scale_factor;
  }
  return;
}

std::vector<ThreeVector> CrystalStructure::cartesian_basis_vectors(
    const LatticeVectors& lattice_vectors, const CrystalBasis& basis) const
{
  std::vector<ThreeVector> cartesian_vectors;
  
  for (UInt i =0; i< basis.num_basis_vectors();i++) {
    ThreeVector cartesian_vector =
        basis.get_basis_vector(i)(0)*lattice_vectors.get_a1() +
        basis.get_basis_vector(i)(1)*lattice_vectors.get_a2() +
        basis.get_basis_vector(i)(2)*lattice_vectors.get_a3();
    cartesian_vectors.push_back(cartesian_vector);
  }
  return cartesian_vectors;
}

void CrystalStructure::read_site_vectors(const string& file_name)
{
  // check if file exists
  if (!FileProperties::exists(file_name)) {
    string message = "Crystal structure input file ";
    message += file_name;
    message += "does not exist.";
    Errors::quit(message);
  }

  // get number of lines
  UInt num_lines = FileProperties::num_lines(file_name);
  
  // start stream
  std::ifstream input_file(file_name.c_str());
    
  // read the file as saved by the write method
  ThreeVector site_vector;
  
  double component = 0.0;
  for (UInt i=0;i<num_lines;i++) {
    input_file >> component;
    site_vector(0) = component;
    
    input_file >> component;
    site_vector(1) = component;
    
    input_file >> component;
    site_vector(2) = component;
    
    add_site_vector(site_vector);
    
  }

  input_file.close();
  return;
  
}

CrystalStructure::CrystalStructure()
{
}

CrystalStructure::CrystalStructure(
    const LatticeVectors& lattice_vectors, const CrystalBasis& basis,
    const int min_i, const int max_i,
          const int min_j, const int max_j,
          const int min_k, const int max_k)
{
    
  std::vector<ThreeVector> basis_vectors = cartesian_basis_vectors(
      lattice_vectors,basis);
  
  ThreeVector site_vector;
  ThreeVector a_i, a_j, a_k;
  
  for (int i=min_i;i<=max_i;i++) {
    a_i = static_cast<double>(i)*lattice_vectors.get_a1();
    for (int j=min_j;j<=max_j;j++) {
      a_j = static_cast<double>(j)*lattice_vectors.get_a2();
      for (int k=min_k;k<=max_k;k++) {
        a_k = static_cast<double>(k)*lattice_vectors.get_a3();
        
        for (UInt l =0;l<basis_vectors.size();l++) {
          site_vector = a_i + a_j + a_k + basis_vectors[l];
          add_site_vector(site_vector);
        }
        
      }
    }
  }
  
}

CrystalStructure::CrystalStructure(const string & file_name)
{
  read_site_vectors(file_name);
}


const std::vector<ThreeVector>& CrystalStructure::get_site_vectors() const
{
  return site_vectors_;
}

const ThreeVector& CrystalStructure::get_site_vector(
    const UInt index) const
{
  return site_vectors_[index];
}

UInt CrystalStructure::num_site_vectors() const
{
  return site_vectors_.size();
}

double CrystalStructure::max_site_vector_length() const
{
  DoubleArray lengths;
  for (UInt i=0;i < num_site_vectors();i++) {
    lengths.push_back(get_site_vector(i).norm());
  }
  return *max_element(lengths.begin(),lengths.end());
}

double CrystalStructure::max_abs_component() const
{
  
  DoubleArray lengths;
  for (UInt i=0;i < num_site_vectors();i++) {
    lengths.push_back(BoostEigen::maxAbsCoeff(get_site_vector(i)));
  }
  return *max_element(lengths.begin(),lengths.end());

}

double CrystalStructure::average_site_vector_separation() const
{
  
  double avg_diff = 0.0;
  ThreeVector i_vec, j_vec, diff_vec;

  // pair all vectors, find the average distance
  UInt k = 0;
  for (UInt i=0; i<num_site_vectors();i++) {
    i_vec = get_site_vector(i);
    UInt j = 0;
    while (j<i) {
      j_vec = get_site_vector(j);
      diff_vec = i_vec - j_vec;
      avg_diff += diff_vec.norm();
      j += 1;
      k += 1;
    }
    
  }

  return avg_diff/static_cast<double>(k);
  // TODO CHECK: k should be n*n/2 where n=num of site vectors
  
}


void CrystalStructure::write_site_vectors(
    const string& file_name) const
{
  // start stream
  std::ofstream out_file(file_name.c_str());
  
  // format
  out_file << std::left;
  out_file << std::scientific;
  out_file << std::setprecision(5);
  
  for (UInt i=0;i<num_site_vectors();i++) {
    out_file << std::setw(25) << get_site_vector(i)(0);
    out_file << std::setw(25) << get_site_vector(i)(1);
    out_file << std::setw(25) << get_site_vector(i)(2);
    out_file << std::endl;
  }
  out_file.close();
  return;
}


} // namespace SpinDec

