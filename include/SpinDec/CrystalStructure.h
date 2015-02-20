#ifndef CRYSTALSTRUCTURE_H_
#define CRYSTALSTRUCTURE_H_

// SpinDec::CrystalStructure
//
// Crystal structure =
// i a_1  + j a_2 + k a_3 + sum_n{b_n}
// where a1, a2 and a3 are (linearly independent) lattice vectors, the b_n
// are n basis vectors and i,j,k integers.
//
// The length units are Angstroms. Using Cartesian coordinates.
//
// Seto Balian, Feb 20, 2015

#include "SpinDec/typedefs.h"

#include "SpinDec/LatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

#include <vector>

namespace SpinDec
{

class CrystalStructure
{
private:
  void read_site_vectors(const string & file_name);
  
protected:
  
  // Here, the integer arguments are the i,j,k defined above.
  // The double arguments define the spatial ranges for all the x,y, and z
  // components for shaping the final crystal structure.
  // The fractional abundance (converted to parts per million) is the
  // fraction of site vectors added using a uniform distribution (using
  // cstdlib rand(); see RandomNumberGenerator.h).
  // If the fractional abundance is 1.0, then all site vectors are included.
  void fill_site_vectors(const LatticeVectors& lattice_vectors,
      const CrystalBasis& basis,
      const int min_i, const int max_i,
      const int min_j, const int max_j,
      const int min_k, const int max_k,
      const double min_x, const double max_x,
      const double min_y, const double max_y,
      const double min_z, const double max_z,
      const double fractional_abundance);
  
  std::vector<ThreeVector> site_vectors_;

  void add_site_vector(const ThreeVector & site_vector);
  void scale_site_vectors(const double scale_factor);

  // get the basis vectors in Cartesian coordinates
  std::vector<ThreeVector> cartesian_basis_vectors(
      const LatticeVectors& lattice_vectors, const CrystalBasis& basis) const;

public:
  CrystalStructure();
  
  // calls fill_site_vectors
  CrystalStructure(const LatticeVectors& lattice_vectors,
      const CrystalBasis& basis,
      const int min_i, const int max_i,
      const int min_j, const int max_j,
      const int min_k, const int max_k,
      const double min_x, const double max_x,
      const double min_y, const double max_y,
      const double min_z, const double max_z,
      const double fractional_abundance);
  
  explicit CrystalStructure(const string & file_name); // reads from file
                                                       // 3 columns: x, y, z
  
  explicit CrystalStructure(const vector<ThreeVector> & site_vectors);
  
  const std::vector<ThreeVector>& get_site_vectors() const;
  const ThreeVector& get_site_vector(const UInt index) const;

  UInt num_site_vectors() const;
  double max_site_vector_length() const;

  // max  ( max ( |x_1|, |y_1|, |z_1| ), ... , max ( |x_n|, |y_n|, |z_n| ), )
  // for n site vectors
  double max_abs_component() const;
  
  double average_site_vector_separation() const;
  
  void write_site_vectors(const string & file_name) const;
  
  // Print with cout (x, y, z)
  friend std::ostream& operator<<(std::ostream& os,
      CrystalStructure const & crystal_structure);

};

} // namespace SpinDec

#endif // CRYSTALSTRUCTURE_H_
