#ifndef CRYSTALSTRUCTURE_H_
#define CRYSTALSTRUCTURE_H_

// Seto Balian, Jul 22, 2015

#include "SpinDec/typedefs.h"

#include "SpinDec/LatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

#include <vector>

namespace SpinDec
{

/**
 * \brief \f$i{\bf a}_1+j{\bf a}_2+k{\bf a}_3+\sum_n{\bf b}_n\f$.
 * 
 * The above = crystal structure, where \f$ {\bf a}_1,{\bf a}_2,{\bf a}_3 \f$
 * are linearly independent lattice vectors, the \f${\bf b}_n\f$ are \f$n\f$
 * basis vectors and \f$ i,j,k\f$ are integers.
 * 
 * The length units are \f$\mbox{\AA}\f$. Using Cartesian coordinates.
 * 
 */
class CrystalStructure
{
private:
  
  void read_site_vectors(const string & file_name);
  
protected:
  
  
  /**
   * \brief Fills site vectors.
   * 
   * Here, the integer arguments are the \f$i,j,k\f$.
   * The double arguments define the spatial ranges for all the \f$ x,y,z \f$
   * components for shaping the final crystal structure.
   * 
   */
   void fill_site_vectors(const LatticeVectors& lattice_vectors,
      const CrystalBasis& basis,
      const int min_i, const int max_i,
      const int min_j, const int max_j,
      const int min_k, const int max_k,
      const double min_x, const double max_x,
      const double min_y, const double max_y,
      const double min_z, const double max_z);
  
  std::vector<ThreeVector> site_vectors_;

  void add_site_vector(const ThreeVector & site_vector);
  void scale_site_vectors(const double scale_factor);

  /// Get the basis vectors in Cartesian coordinates.
  std::vector<ThreeVector> cartesian_basis_vectors(
      const LatticeVectors& lattice_vectors, const CrystalBasis& basis) const;

public:
  CrystalStructure();
  
  /// Calls fill_site_vectors.
  CrystalStructure(const LatticeVectors& lattice_vectors,
      const CrystalBasis& basis,
      const int min_i, const int max_i,
      const int min_j, const int max_j,
      const int min_k, const int max_k,
      const double min_x, const double max_x,
      const double min_y, const double max_y,
      const double min_z, const double max_z);
  
  /// Reads from file. Three columns: \f$ x,y,z \f$.
  explicit CrystalStructure(const string & file_name);
  explicit CrystalStructure(const vector<ThreeVector> & site_vectors);
  
  /**
  * The fractional abundance (converted to parts per million) is the
  * fraction of site vectors to remain. This method uses a uniform distribution.
  */
  void sparsify(const double fractional_abundance, const UInt seed);
  
  const std::vector<ThreeVector>& get_site_vectors() const;
  const ThreeVector& get_site_vector(const UInt index) const;

  UInt num_site_vectors() const;
  double max_site_vector_length() const;

  /**
   *  \brief \f$ {\rm max}[ {\rm max}( |x_1|, |y_1|, |z_1| ) ,\dots,
   *                 {\rm max} ( |x_n|, |y_n|, |z_n| )], \f$ for \f$n\f$ site
   *                 vectors.
   */
  double max_abs_component() const;
  
  double average_site_vector_separation() const;
  
  void write_site_vectors(const string & file_name) const;
    
  /// Print with cout \f$(x, y, z)\f$.
  friend std::ostream& operator<<(std::ostream& os,
      CrystalStructure const & crystal_structure);

};

} // namespace SpinDec

#endif // CRYSTALSTRUCTURE_H_
