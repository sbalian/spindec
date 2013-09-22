#ifndef FT_H
#define FT_H

// f(t), where t is a n x 1 array and f is a n x m array of complex doubles (m and n >= 1)
//
// Created  19/09/2012
// Modified 20/09/2012, 22/09/2012, 27/09/2012, 28/09/2012, 03/10/2012, 19/11/2012
// Modified 02/12/2012 - complex f
// Modified 11/12/2012
// Seto Balian
// V1

// NOTE: Needs commenting

#include "stdincludes.hpp"

using namespace std;
using namespace Eigen;

class ft
{
private:
  
  ArrayXd   t;
  ArrayXXcd f;
  
public:
  ft();
  ft(const double initial_t, const double final_t, const int number_of_t_steps, const bool log_t);
  ft(const double initial_t, const double final_t, const int number_of_t_steps, const bool log_t, const int n);
  ft(const ArrayXd & t_in, const int n);
  ft(const ArrayXd & t_in, const ArrayXXcd & f_in);

  ft(const vector<double> & time_in);

  ArrayXd  get_t () const;
  double   get_t (const int i) const;
  void set_t (const ArrayXd & t_in);
  void set_t (const int i, const double value);
  void inv_log10_t();
  void log10_t();
  int t_size() const;

  ArrayXXcd get_f () const;
  ArrayXcd  get_f (const int i) const;
  cmplxd  get_f (const int i, const int j) const;
  void set_f (const int i, const int j, const cmplxd & value);
  void set_f (const ArrayXXcd & f_in);
  void set_f (const int i, const ArrayXcd & f_in);
  void add_f (const ArrayXcd & f_in);
  void set_f_ones();
  void set_f_zeros();
  int f_size() const;
  
  ft product_f()        const; // complex
  ft mean_f()           const; // complex
  ft stdev_f()          const; // complex
  ft stdev_mean_f()     const; // complex

  void print(const int precision, const string & output_mode) const;
  void print(const int precision, const string & outfilename, const string & output_mode) const;
  
//  // First column: t
//  // Subsequent columns: f(t)
  static ft read(const string & input_file_name);

};

#endif // FT_H

