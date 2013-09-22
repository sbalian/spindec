#ifndef LATTICE_H
#define LATTICE_H

// For generating lattice vectors in Cartesian coordinates (x,y,z).
//
// Created  19/09/2012 diamondcubic -> lattice
// Modified 20/09/2012, 14/11/2012, 19/11/2012
// Modified 11/12/2012 - commented out some generate + get random lattice vecs method
// Modified 25/02/2013
// Modified 08/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "named.hpp"
#include "threevector.hpp"

using namespace std;

class lattice : public named
{

private:
  double lattice_constant;     // lattice constant (for the conventional cell)
  vector<threevector> lattice_vectors;

public:

  lattice();
  lattice(const string & name_in, const double lattice_constant_in);
    
  double get_lattice_constant() const;
  void set_lattice_constant(const double lattice_constant_in);

  vector<threevector> get_lattice_vectors () const;
  threevector get_lattice_vector (const int i) const;

  // int generate_random_diamond_cubic(const double cubic_size, const double frac);
  void old_generate_diamond_cubic(const int size);
  int generate_random_diamond_cubic(const int size, const int bath_abundance_ppm);

  vector<threevector> get_lattice_vectors (const double max_radius) const;

  int get_lattice_vectors_size() const;
  vector<threevector> get_random_lattice_vectors(const double frac) const;

  static double get_max_mod(const vector<threevector> & vvin);
  double get_max_lattice_vector_mod() const;

  static double get_max_abs_comp(const vector<threevector> & vvin);
  double get_max_lattice_vector_abs_comp() const;

  void set_lattice_vectors (const vector<threevector> & lattice_vectors_in);
  void add_lattice_vector(const threevector & lattice_vector);
  void clear_lattice_vectors ();
  void scale_lattice_vectors(const double scalefactor);
  
  void write_lattice_vectors(const string & filename) const;
  void read_lattice_vectors(const string & filename);
  
  void seed_random_number_generator() const;

  double get_average_lattice_vector_separation() const;
  
};

#endif // LATTICE_H

