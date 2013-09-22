// f(t), where t is a n x 1 array and f is a n x m array (m and n >= 1)
//
// Created  19/09/2012
// Modified 20/09/2012, 22/09/2012, 27/09/2012, 28/09/2012, 30/09/2012, 03/10/2012, 19/11/2012
// Modified 02/12/2012 - complex f
// Modified 11/12/2012, 12/12/2012
// Modified 17/01/2013
// Seto Balian
// V1

// NOTE: Needs commenting

#include "stdincludes.hpp"
#include "ft.hpp"

using namespace std;
using namespace Eigen;

ft::ft(){}

ft::ft(const double initial_t, const double final_t, const int number_of_t_steps, const bool log_t) {
  ft(initial_t,final_t,number_of_t_steps,0);
  if (log_t) {
    inv_log10_t();
  }
  set_f_ones();
}

ft::ft(const double initial_t, const double final_t, const int number_of_t_steps, const bool log_t, const int n) {

  ArrayXd   t_in(number_of_t_steps+1);
  ArrayXXcd f_in(number_of_t_steps+1,n);

  double dt = (final_t - initial_t) / double(number_of_t_steps);
  double tt = initial_t;

  int i,j;
  for (i=0;i<number_of_t_steps+1;i++) {
    t_in(i) = tt;
    for (j=0;j<n;j++) {
      f_in(i,j) = cmplxd(1.0,0.0);
    }
    tt = tt + dt;
  }

  t = t_in;
  f = f_in;

  if (log_t) {
    inv_log10_t();
  }

  set_f_ones();

}

ft::ft(const ArrayXd & t_in, const int n) {
  t = t_in;
  ArrayXXcd f_in(t_in.rows(),n);
  f_in.setZero();
  f = f_in;
  set_f_ones();
}

ft::ft(const ArrayXd & t_in, const ArrayXXcd & f_in) {
  t = t_in;
  f = f_in;
}

ft::ft(const vector<double> & time_in) {
  int n = int ( time_in.size() );
  int i;
  ArrayXd t_in(n);

  for (i=0;i<n;i++) {
    t_in(i) = time_in[i];
  }
  
  t = t_in;

  ArrayXXcd f_in(t_in.rows(),1);
  f_in.setZero();
  f = f_in;

}

ArrayXd  ft::get_t () const {
  return t;
}

double  ft::get_t (const int i) const {
  return t(i);
}

void ft::set_t (const ArrayXd  & t_in) {
  t = t_in;
  return;
}

void ft::set_t (const int i, const double value) {
  t(i) = value;
  return;
}

void ft::inv_log10_t() {
  int i;
  for (i=0;i<t_size();i++) {
    t(i) = pow(10.0,t(i));
  }
  return;
}

void ft::log10_t() {
  int i;
  for (i=0;i<t_size();i++) {
    t(i) = log10(t(i));
  }
  return;
}

int ft::t_size() const {
  return t.rows();
}

ArrayXXcd ft::get_f () const {
  return f;
}

ArrayXcd  ft::get_f (const int i) const {
  return get_f().col(i);
}

cmplxd  ft::get_f (const int i, const int j) const {
  return get_f()(i,j);
}

void ft::set_f (const int i, const int j, const cmplxd & value) {
  f(i,j) = value;
  return;
}

void ft::set_f (const ArrayXXcd & f_in) {
  f = f_in;
  return;
}

void ft::set_f (const int i, const ArrayXcd & f_in) {
  f.col(i) = f_in;
  return;
}

void ft::add_f (const ArrayXcd & f_in) {
  ArrayXXcd new_f(f.rows(),f.cols() + 1);
  int i;
  for (i=0;i<f.cols();i++) {
    new_f.col(i) = f.col(i);
  }
  new_f.col(f.cols()) = f_in;
  f = new_f;
  return;
}

void ft::set_f_ones() {
  f.setOnes();
  return;
}

void ft::set_f_zeros() {
  f.setZero();
  return;
}

int ft::f_size() const {
  return f.cols();
}


ft ft::product_f()        const { // complex
  return ft ( get_t() , get_f().rowwise().prod() );
}

ft ft::mean_f()           const { // complex
  return ft ( get_t() , (get_f().rowwise().sum())/double(f_size()) );
}

ft ft::stdev_f()          const { // complex

  ArrayXXcd f_array = get_f();
  int f_rows = f_array.rows();
  int f_cols = f_array.cols();
  ArrayXXd real_f_array(f_rows,f_cols);
  ArrayXXd imag_f_array(f_rows,f_cols);
  int i, j;
  for (i=0;i<f_rows;i++) {
    for (j=0;j<f_cols;j++) {
      real_f_array(i,j) = real(f_array(i,j));
      imag_f_array(i,j) = imag(f_array(i,j));
    }
  }

  ArrayXXcd mean_f_array = mean_f().get_f();
  ArrayXXd mean_real_f_array(f_rows,1);
  ArrayXXd mean_imag_f_array(f_rows,1);
  for (i=0;i<f_rows;i++) {
    mean_real_f_array(i,0) = real(mean_f_array(i,0));
    mean_imag_f_array(i,0) = imag(mean_f_array(i,0));
  }

  for (i=0;i<f_cols;i++) {
    real_f_array.col(i) = real_f_array.col(i) - mean_real_f_array.col(0);
  }

  for (i=0;i<f_cols;i++) {
    imag_f_array.col(i) = imag_f_array.col(i) - mean_imag_f_array.col(0);
  }

  for (i=0;i<f_rows;i++) {
    for (j=0;j<f_cols;j++) {
      real_f_array(i,j) = real_f_array(i,j)*real_f_array(i,j);
    }
  }

  for (i=0;i<f_rows;i++) {
    for (j=0;j<f_cols;j++) {
      imag_f_array(i,j) = imag_f_array(i,j)*imag_f_array(i,j);
    }
  }

  ArrayXd real_f_out = sqrt(real_f_array.rowwise().sum())/(double(f_cols) - 1.0);
  ArrayXd imag_f_out = sqrt(imag_f_array.rowwise().sum())/(double(f_cols) - 1.0);

  ArrayXXcd f_out(f_rows,1);
  for (i=0;i<f_rows;i++) {
    f_out(i,0) = cmplxd(real_f_out(i),imag_f_out(i));
  }
 
  return ft(  get_t(), f_out  );

}

ft ft::stdev_mean_f()     const { // complex
  return ft(get_t(), stdev_f().get_f()/sqrt(double(f_size())));
}

void ft::print(const int precision, const string & output_mode) const {

if ((output_mode == "real") || (output_mode == "imag") ||
    (output_mode == "cmplx") || (output_mode == "abs") )
{} else {
  cout << "ERROR: output_mode must be \"real\",\"imag\",\"abs\" or \"cmplx\".";
  cout << " Quitting ..." << endl;
  exit(1);
  return;
}

  cout << left;
  cout << scientific;
  int i, j;
  for (i=0;i<t_size();i++) {
    cout << setw(precision+24) << setprecision(precision) << get_t(i);
    for (j=0;j<f_size();j++) {
      if (output_mode == "real") {
        cout << setw(precision+24) << setprecision(precision) << real(get_f()(i,j));
      }
      if (output_mode == "imag") {
        cout << setw(precision+24) << setprecision(precision) << imag(get_f()(i,j));
      }
      if (output_mode == "abs") {
        cout << setw(precision+24) << setprecision(precision) << abs(get_f()(i,j));
      }
      if (output_mode == "cmplx") {
        cout << setw(precision+24) << setprecision(precision) << get_f()(i,j);
      }
    }
    cout << endl;
  }
  return;

}

void ft::print(const int precision, const string & outfilename, const string & output_mode) const {

if ((output_mode == "real") || (output_mode == "imag") ||
    (output_mode == "cmplx") || (output_mode == "abs") )
{} else {
  cout << "ERROR: output_mode must be \"real\",\"imag\",\"abs\" or \"cmplx\".";
  cout << " Quitting ..." << endl;
  exit(1);
  return;
}

  ofstream outfile(outfilename.c_str());

  outfile << left;
  outfile << scientific;
  int i, j;
  for (i=0;i<t_size();i++) {
    outfile << setw(precision+24) << setprecision(precision) << get_t(i);
    for (j=0;j<f_size();j++) {
      if (output_mode == "real") {
        outfile << setw(precision+24) << setprecision(precision) << real(get_f()(i,j));
      }
      if (output_mode == "imag") {
        outfile << setw(precision+24) << setprecision(precision) << imag(get_f()(i,j));
      }
      if (output_mode == "abs") {
        outfile << setw(precision+24) << setprecision(precision) << abs(get_f()(i,j));
      }
      if (output_mode == "cmplx") {
        outfile << setw(precision+24) << setprecision(precision) << get_f()(i,j);
      }
    }
    outfile << endl;
  }

  outfile.close();
  return;

}

// First column: t
// Subsequent columns: f(t)
ft ft::read(const string & input_file_name) {

  // start input file stream
  ifstream infile(input_file_name.c_str());

  // get number of lines in input file
  int nlines = 0;
  string temps;
  while (getline(infile, temps)) {
          if (temps == "") {
            break;
          } else {
              nlines++;
            }
  }
  infile.clear();
  infile.seekg(0);

//  cout << "nlines is " << nlines << endl;

  // Determine if complex numbers
  unsigned int p = 0;
  bool isComplex = 0;
  while (!infile.eof()) {
    infile >> temps;
    for (p=0;p<temps.length();p++) {
      if (temps[p] == '(') {
        isComplex = 1;
        break;
      }
    }
  }
  infile.clear();
  infile.seekg(0);

//  cout << "is complex is " << isComplex << endl;
  
  // get number of entries in input file
  double tempd = 0.0;
  cmplxd tempcmplxd;
  int nentries = -1;
  while (!infile.eof()) {
    nentries = nentries + 1;
    if (isComplex == 0) {
      infile >> tempd;
    } else {
        infile >> tempcmplxd;
      }
  }
  infile.clear();
  infile.seekg(0);

//  cout << "nentries is " << nentries << endl;

  
  // get number of columns in input file
  int ncols = nentries/nlines;
  
  // declare loop variables
  int i, j;
  ArrayXd tt(nlines);
  
  // get first column (t vector)
  for (i=0;i<nlines;i++) {
    infile >> tempd;
    tt(i) = tempd;
    for (j=0;j<ncols-1;j++) {
      if (isComplex == 0) {
        infile >> tempd;
      } else {
          infile >> tempcmplxd;
      }
    }
  }
  infile.clear();
  infile.seekg(0);

//  cout << tt << endl;

  ArrayXXcd ff(nlines,ncols-1);

  
  // read f(t) from file
  for (i=0;i<nlines;i++) {
    infile >> tempd;
    for (j=0;j<ncols-1;j++) {
      if (isComplex == 0) {
        infile >> tempd;
        ff(i,j) = cmplxd(tempd,0.0);
      } else {
          infile >> tempcmplxd;
          ff(i,j) = tempcmplxd;
        }
    }
    
  }
  
  // end input file stream
  infile.close();

  return ft( tt,ff );

}


