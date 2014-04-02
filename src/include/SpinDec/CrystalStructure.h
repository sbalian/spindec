#ifndef CRYSTALSTRUCTURE_H_
#define CRYSTALSTRUCTURE_H_

// SpinDec::CrystalStructure
//
// Crystal structure: lattice + basis in Cartesian (x,y,z) coordinates.
// Units of length: Angstroms.
//
// Seto Balian, Apr 2, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/CrystalLattice.h"
#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

class CrystalStructure
{
protected:

  std::vector<ThreeVector> site_vectors_; // lattice + basis
  
  // add each lattice vector with all the basis vectors to get the site vectors
  void add_site_vectors(
      const CrystalLattice& lattice, const CrystalBasis& basis);
  
  void add_site_vector(const ThreeVector & site_vector);

  void scale_site_vectors(const double scale_factor);
  
  void read_site_vectors(const string & file_name);
                                                    // clears existing
                                                    // site_vectors_
  void clear_site_vectors();

public:
  CrystalStructure();
  CrystalStructure(const CrystalLattice& lattice, const CrystalBasis& basis);

  const std::vector<ThreeVector>& get_site_vectors() const;
  const ThreeVector& get_site_vector(const UInt index) const;

  UInt num_site_vectors() const;
  double max_site_vector_length() const;

  // max  ( max ( |x_1|, |y_1|, |z_1| ), ... , max ( |x_n|, |y_n|, |z_n| ), )
  // for n site vectors
  double max_abs_component() const;
  
  double average_site_vector_separation() const;
  
  void write_site_vectors(const string & file_name) const;

};

} // namespace SpinDec

#endif // CRYSTALSTRUCTURE_H_
