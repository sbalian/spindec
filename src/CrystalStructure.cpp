// See CrystalStructure.h for description.
// Seto Balian, Oct 22, 2014

#include "SpinDec/CrystalStructure.h"
#include "SpinDec/FileProperties.h"
#include "SpinDec/Errors.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/RandomNumberGenerator.h"

#include <fstream>
#include <iomanip>
#include <iostream>

#include <algorithm>

namespace SpinDec
{

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
    
  // read the file as saved by the write method (3 columns: x,y,z)
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


void CrystalStructure::fill_site_vectors(const LatticeVectors& lattice_vectors,
    const CrystalBasis& basis,
    const int min_i, const int max_i,
    const int min_j, const int max_j,
    const int min_k, const int max_k,
    const double min_x, const double max_x,
    const double min_y, const double max_y,
    const double min_z, const double max_z,
    const double fractional_abundance)
{
  
  // get the basis vectors in Cartesian coordinates because they are expressed
  // in the (a1,a2,a3) lattice vector basis
  std::vector<ThreeVector> basis_vectors = cartesian_basis_vectors(
      lattice_vectors,basis);

  ThreeVector site_vector;
  ThreeVector a_i, a_j, a_k;

  // check fractional abundance
  if (fractional_abundance <= 0.0) {
    Errors::quit("Fractional abundance must be positive and non-zero.");
  }
  
  // convert fractional abundance to parts per million
  const unsigned int abundance_ppm =
      static_cast<unsigned int>(fractional_abundance*1000000);
  
  // warn if no site vectors
  if (abundance_ppm == 0) {
    Errors::warning("Abundance is 0. No lattice sites will be included.");
  }

  // loop over integers i, j, k for the input ranges, adding site vectors
  // if all conditions are met
  for (int i=min_i;i<=max_i;i++) {
    // scale lattice vectors as described in CrystalStructure.h
    a_i = static_cast<double>(i)*lattice_vectors.get_a1();
    for (int j=min_j;j<=max_j;j++) {
      a_j = static_cast<double>(j)*lattice_vectors.get_a2();
      for (int k=min_k;k<=max_k;k++) {
        a_k = static_cast<double>(k)*lattice_vectors.get_a3();
        
        // for each lattice vector add all sites specified by the basis vectors
        // (described in CrystalStructure.h)
        for (UInt l =0;l<basis_vectors.size();l++) {
          
          site_vector = a_i + a_j + a_k + basis_vectors[l];
          
          // add if random number drawn from a uniform distribution is 
          // < abundance (for random numbers between 1 and 1 million)
          if ( static_cast<unsigned int>(
              RandomNumberGenerator::uniform_c_rand(1,1000000))
                                      <= abundance_ppm) {
            // move on
          } else {
              continue; // don't add site vector
          }
          
          // now check if site vector fits in the (fine double) range defined
          // by the input (and hence shape the final crystal structure)
          bool to_add
                  = ((site_vector(0) >= min_x) && (site_vector(0) <= max_x));
          to_add *= ((site_vector(1) >= min_y) && (site_vector(1) <= max_y));
          to_add *= ((site_vector(2) >= min_z) && (site_vector(2) <= max_z));
          
          // all ok? then add the site vector
          if (to_add == true) {
            add_site_vector(site_vector);
          }
          
        }
        
      }
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


CrystalStructure::CrystalStructure()
{
}

CrystalStructure::CrystalStructure(
    const LatticeVectors& lattice_vectors, const CrystalBasis& basis,
    const int min_i, const int max_i,
          const int min_j, const int max_j,
          const int min_k, const int max_k,
          const double min_x, const double max_x,
          const double min_y, const double max_y,
          const double min_z, const double max_z,
          const double fractional_abundance)
{
  
  fill_site_vectors(lattice_vectors, basis,
             min_i, max_i,
             min_j,  max_j,
             min_k,  max_k,
             min_x,  max_x,
             min_y,  max_y,
             min_z,  max_z,
             fractional_abundance);
  
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

std::ostream& operator<<(std::ostream& os,
    CrystalStructure const & crystal_structure)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << std::scientific << std::left << std::setprecision(6);
  
  for (UInt i = 0;i < crystal_structure.num_site_vectors(); i++) {
    os << std::setw(12) << crystal_structure.get_site_vector(i)(0);
    os << std::setw(12) << crystal_structure.get_site_vector(i)(1);
    os << std::setw(12) << crystal_structure.get_site_vector(i)(2);
    os << std::endl;
  }
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}

} // namespace SpinDec

