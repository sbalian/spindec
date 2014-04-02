// See CrystalStructure.h for description.
// Seto Balian, Apr 2, 2014

#include "SpinDec/CrystalStructure.h"
#include "SpinDec/FileProperties.h"
#include "SpinDec/Errors.h"
#include "SpinDec/BoostEigen.h"

#include <fstream>
#include <iomanip>

#include <algorithm>

namespace SpinDec
{

void CrystalStructure::add_site_vectors(
    const CrystalLattice& lattice, const CrystalBasis& basis)
{
  ThreeVector site_vector;
  for (UInt i=0;i < lattice.num_lattice_vectors();i++) {
    for (UInt j=0;j<basis.num_basis_vectors();j++) {
      site_vector = lattice.get_lattice_vector(i) + basis.get_basis_vector(j);
      site_vectors_.push_back(site_vector);
    }
  }
  return;
}

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
  
  // clear site, lattice and basis vectors
  clear_site_vectors();
  
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

void CrystalStructure::clear_site_vectors()
{
  site_vectors_.clear();
  return;
}

CrystalStructure::CrystalStructure()
{
}

CrystalStructure::CrystalStructure(
    const CrystalLattice& lattice, const CrystalBasis& basis)
{
  add_site_vectors(lattice,basis);
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

