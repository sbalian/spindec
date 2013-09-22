// Reads CCE program parameters from an input file

// Created  06/10/2012
// Modified 07/10/2012, 08/10/2012, 11/10/2012, 24/10/2012, 26/10/2012
// Modified 31/10/2012, 01/11/2012, 06/11/2012, 12/11/2012, 14/11/2012
// Modified 15/11/2012, 16/11/2012, 19/11/2012
// Modified 03/12/2012
// Modified 11/12/2012
// Modified 18/01/2013 added abs_echo
// Modified 26/02/2013 added seed_value
// Modified 18/03/2013 added include_shf_to_bath and include_dipolar_to_bath
// Modified 08/05/2013
// Seto Balian
// V1

// NOTE: Handle default values ...

#include "stdincludes.hpp"
#include "cceread.hpp"

using namespace std;

cceread::cceread() {}



cceread::cceread(const string & infilename_in, const string & readprofilename_in, const bool silent_in) {
  infilename = infilename_in;
  readprofilename = readprofilename_in;
  set_profile();
  silent = silent_in;
  read();
}

cceread::cceread(const string & infilename_in, const string & readprofilename_in) {
  infilename = infilename_in;
  readprofilename = readprofilename_in;
  set_profile();
  silent = 1;
  read();
}

void cceread::set_profile() {

  int profile_index = readprofilename_to_index(readprofilename);
  doubleTriplet temp_doubleTriplet;
  frac          temp_frac;

  switch (profile_index)
  {
    case 0:

    // Doubles

    readprof_d["B"] = 0.0;
    readprof_type["B"] = "double";

    readprof_d["gamma_e"]  = 0.0;
    readprof_type["gamma_e"] = "double";

    readprof_d["gamma_n"]  = 0.0;
    readprof_type["gamma_n"] = "double";

    readprof_d["eIE"] = 0.0;
    readprof_type["eIE"] = "double";

    readprof_d["A"] = 0.0;
    readprof_type["A"] = "double";

    readprof_d["gamma_b"] = 0.0;
    readprof_type["gamma_b"] = "double";

    readprof_d["i_time"] = 0.0;
    readprof_type["i_time"] = "double";

    readprof_d["f_time"] = 0.0;
    readprof_type["f_time"] = "double";

    readprof_d["a0"] = 0.0;
    readprof_type["a0"] = "double";

    readprof_d["fcc_a"] = 0.0;
    readprof_type["fcc_a"] = "double";

    readprof_d["fcc_b"] = 0.0;
    readprof_type["fcc_b"] = "double";

    readprof_d["eta"] = 0.0;
    readprof_type["eta"] = "double";

    readprof_d["shf_cor"] = 0.0;
    readprof_type["shf_cor"] = "double";

    readprof_d["sep_cutoff"] = 0.0;
    readprof_type["sep_cutoff"] = "double";

    readprof_d["bath_abundance"] = 0.0;
    readprof_type["bath_abundance"] = "double";

    readprof_d["c0_bath"] = 1.0;
    readprof_type["c0_bath"] = "double";

    readprof_d["D"] = 0.0;
    readprof_type["D"] = "double";

    readprof_d["gamma_eff"] = 0.0;
    readprof_type["gamma_eff"] = "double";

    readprof_d["lattice_cubic_side_length"] = 0.0;
    readprof_type["lattice_cubic_side_length"] = "double";

    readprof_d["bath_abundance_frac"] = 0.0;
    readprof_type["bath_abundance_frac"] = "double";

    // doubleTriplets

    temp_doubleTriplet.d_1 = 0.0;
    temp_doubleTriplet.d_2 = 0.0;
    temp_doubleTriplet.d_3 = 0.0;
    readprof_t["B_dir"] = temp_doubleTriplet;
    readprof_type["B_dir"] = "doubleTriplet";

    // integers

    readprof_i["CCE_order"] = 0;
    readprof_type["CCE_order"] = "int";

    readprof_i["level_0"] = 0;
    readprof_type["level_0"] = "int";

    readprof_i["level_1"] = 0;
    readprof_type["level_1"] = "int";

    readprof_i["nplacements"] = 0;
    readprof_type["nplacements"] = "int";

    readprof_i["n_time"] = 0;
    readprof_type["n_time"] = "int";

    readprof_i["lattice_size"] = 0;
    readprof_type["lattice_size"] = "int";

    readprof_i["bath_abundance_ppm"] = 0;
    readprof_type["bath_abundance_ppm"] = "int";

    readprof_i["seed_value"] = 0;
    readprof_type["seed_value"] = "int";

    // fracs

    temp_frac.num = 0;
    temp_frac.den = 0;
    readprof_f["I"] = temp_frac;
    readprof_type["I"] = "frac";

    // bools

    readprof_b["include_1c"]= 0;
    readprof_type["include_1c"] = "bool";

    readprof_b["full_basis"]= 0;
    readprof_type["full_basis"] = "bool";

    readprof_b["log_time"]= 0;
    readprof_type["log_time"] = "bool";

    readprof_b["seed_rand"]= 0;
    readprof_type["seed_rand"] = "bool";

    readprof_b["Ising_only"]= 0;
    readprof_type["Ising_only"] = "bool";

    readprof_b["no_pipulse"]= 0;
    readprof_type["no_pipulse"] = "bool";

    readprof_b["eff_gyro_ratio"]= 0;
    readprof_type["eff_gyro_ratio"] = "bool";

    readprof_b["rand_c0_bath"]= 0;
    readprof_type["rand_c0_bath"] = "bool";

    readprof_b["sparse_bath"]= 0;
    readprof_type["sparse_bath"] = "bool";

    readprof_b["multiply_echos"]= 0;
    readprof_type["multiply_echos"] = "bool";

    readprof_b["abs_echo"]= 0;
    readprof_type["abs_echo"] = "bool";

    readprof_b["include_shf_to_bath"]= 0;
    readprof_type["include_shf_to_bath"] = "bool";

    readprof_b["include_dipolar_to_bath"]= 0;
    readprof_type["include_dipolar_to_bath"] = "bool";

    readprof_b["old_lattice_generator"]= 0;
    readprof_type["old_lattice_generator"] = "bool";

    readprof_b["flush_random_number_generator"]= 0;
    readprof_type["flush_random_number_generator"] = "bool";

//    readprof_b["halve_time"]= 0;
//    readprof_type["halve_time"] = "bool";

//    readprof_b["average_over_bath_states"]= 0;
//    readprof_type["average_over_bath_states"] = "bool";

    // strings

    readprof_s["output_mode"] = "";
    readprof_type["output_mode"] = "string";

    readprof_s["diagtype"] = "";
    readprof_type["diagtype"] = "string";

    readprof_s["report_echo"] = "";
    readprof_type["report_echo"] = "string";

    return;

    default:
      cout << "ERROR: Read profile not found. Quitting ..." << endl;
      exit(1);
      return;
  }



  return;

}

void cceread::read() {


  
  // Start input file stream
  ifstream infile(infilename.c_str());

  if (infile.good()) {
    if (silent==0) {
      cout << "Reading input parameters from " << infilename << " ... ";
    }
  } else {
      cout << "ERROR: Cannot find input file named " << infilename << ". Quitting ..." << endl;
      exit(1);
      return;
  }

  string line;
  stringstream ss;
  string varname, vartype, varvalue;
  
  int i;

  bool good_line = 0;
  int equal_pos = 0;

  while(!infile.eof()) {

    // Get the line
    getline (infile,line);

    good_line = 0;
    equal_pos = 0;

    // Handle comments: lines beginning with '//'
    if ((line[0] == '/') && (line [1] == '/')) {continue;}

    // Determine if line has =, and determine the ='s position
    for (i=0;i<int(line.length());i++) {
      if (line[i] == '=') {
        equal_pos = i;
        good_line = 1;
        // if nothing after =, don't accept the line
        if (i == int(line.length() - 1)) {
          good_line = 0;
        }
      }
    }

    // clear the string stream
    ss.str(string());

    // Proceed if good line
    if (good_line) {

      // Get the parameter name
      for (i=0;i<equal_pos;i++) {
        if (line[i] == ' ') {continue;}
        ss << line[i];
      }
      varname = ss.str();
      ss.str(string());

      // Get the parameter type
      vartype = get_type( varname );

      // Get the parameter value
      for (i=equal_pos+1;i<int(line.length());i++) {
        ss << line[i];
      }
      varvalue = ss.str();
      ss.str(string());

      if (vartype == "double") {
        set_double( varname , string_to_double( varvalue )  );
      }

      if (vartype == "int") {
        set_int( varname , string_to_int( varvalue )  );
      }

      if (vartype == "bool") {
        set_bool( varname , string_to_bool( varvalue )  );
      }

      if (vartype == "frac") {
        set_frac( varname , string_to_frac( varvalue )  );
      }

      if (vartype == "doubleTriplet") {
        set_doubleTriplet( varname , string_to_doubleTriplet( varvalue )  );
      }

      if (vartype == "string") {
        set_string( varname , varvalue );
      }

// cout << varname << endl;

    }
    

  }

  if (silent==0) {
    cout << "done." << endl;
  }

  infile.close();

  return;

}

double cceread::get_double(const string & parametername) const {
  double value = readprof_d.find(parametername)->second;
  if (silent==0) {
    cout << parametername << "=\t" << value << endl;
  }
  return value;
}

int cceread::get_int(const string & parametername) const {
  int value = readprof_i.find(parametername)->second;
  if (silent==0) {
    cout << parametername << "=\t" << value << endl;
  }
  return value;
}

bool cceread::get_bool(const string & parametername) const {
  bool value = readprof_b.find(parametername)->second;
  if (silent==0) {
    cout << parametername << "=\t" << value << endl;
  }
  return value;
}

string cceread::get_string(const string & parametername) const {
  string value = readprof_s.find(parametername)->second;
  if (silent==0) {
    cout << parametername << "=\t" << value << endl;
  }
  return value;
}

string cceread::get_type(const string & parametername) const {
  return readprof_type.find(parametername)->second;
}

frac cceread::get_frac(const string & parametername) const {
  frac value = readprof_f.find(parametername)->second;
  if (silent==0) {
    cout << parametername << "=\t" << value.num << " / " << value.den << endl;
  }
  return value;
}

doubleTriplet cceread::get_doubleTriplet(const string & parametername) const {
  doubleTriplet value = readprof_t.find(parametername)->second;
  if (silent==0) {
    cout << parametername << "=\t" << value.d_1 << ", " << value.d_2 << ", " << value.d_3 << endl;
  }
  return value;
}

int cceread::readprofilename_to_index (const string & readprofilename_in) const {

  if (readprofilename_in == "donornucbath") {
    return 0;
  }
  
  cout << "ERROR: Read profile not found. Quitting ..." << endl;
  exit(1);
  return 0;

}

// http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c
double cceread::string_to_double( const string& s ) const {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
}

int    cceread::string_to_int( const string& s ) const {
   std::istringstream i(s);
   int x;
   if (!(i >> x))
     return 0;
   return x;
}

bool   cceread::string_to_bool( const string& s ) const {
   std::istringstream i(s);
   bool x;
   if (!(i >> x))
     return 0;
   return x;
}

frac cceread::string_to_frac( const string& s ) const {

  stringstream ss;
  int i;
  int div = 0;

  int numerator, denomenator;

  for (i=0;i<int(s.length());i++) {
    if (s[i] == ' ') {
      continue;
    }
    if (s[i] == '/') {
      div = i;
      break;
    }
    ss << s[i];
  }

  numerator = string_to_int(ss.str());
  ss.str(string());

  for (i=div+1;i<int(s.length());i++) {
    if (s[i] == ' ') {
      continue;
    }
    ss << s[i];
  }

  denomenator = string_to_int(ss.str());

  frac frac_out;
  frac_out.num = numerator;
  frac_out.den = denomenator;
  return frac_out;
}

doubleTriplet cceread::string_to_doubleTriplet( const string& s ) const {

  stringstream ss;
  int i;
  int comma_1 = 0;
  int comma_2 = 0;

  double double1, double2, double3;

  for (i=0;i<int(s.length());i++) {
    if (s[i] == ' ') {
      continue;
    }
    if (s[i] == ',') {
      comma_1 = i;
      break;
    }
    ss << s[i];
  }

  double1 = string_to_double(ss.str());
  ss.str(string());

  for (i=comma_1+1;i<int(s.length());i++) {
    if (s[i] == ' ') {
      continue;
    }
    if (s[i] == ',') {
      comma_2 = i;
      break;
    }
    ss << s[i];
  }

  double2 = string_to_double(ss.str());
  ss.str(string());

  for (i=comma_2+1;i<int(s.length());i++) {
    if (s[i] == ' ') {
      continue;
    }
    ss << s[i];
  }

  double3 = string_to_double(ss.str());

  doubleTriplet doubleTriplet_out;
  doubleTriplet_out.d_1 = double1;
  doubleTriplet_out.d_2 = double2;
  doubleTriplet_out.d_3 = double3;

  return doubleTriplet_out;
}


void cceread::set_double(const string & parametername, const double value) {
  readprof_d.find(parametername)->second = value;
  return;
}

void cceread::set_int(const string & parametername, const int value) {
  readprof_i.find(parametername)->second = value;
  return;
}

void cceread::set_bool(const string & parametername, const bool value) {
  readprof_b.find(parametername)->second = value;
  return;
}

void cceread::set_string(const string & parametername, const string & value) {

  stringstream ss;
  string toset;
  int i;

  for (i=0;i<int(value.length());i++) {
    if (value[i] == ' ') {
      continue;
    }
    ss << value[i];
  }
  toset = ss.str();

  readprof_s.find(parametername)->second = toset;
  return;
}

void cceread::set_frac(const string & parametername, const frac & value) {
  readprof_f.find(parametername)->second = value;
  return;
}

void cceread::set_doubleTriplet(const string & parametername, const doubleTriplet & value) {
  readprof_t.find(parametername)->second = value;
  return;
}

// TEST

//int main () {

//  cceread reader("test.cfg","donornucbath");

//  cout << setprecision(10);
//  cout << "A = " << reader.get_double("A") << endl;
//  cout << "B = " << reader.get_double("B") << endl;
//  cout << "B_dir_x = " << reader.get_doubleTriplet("B_dir").d_1 << endl;
//  cout << "B_dir_y = " << reader.get_doubleTriplet("B_dir").d_2 << endl;
//  cout << "B_dir_z = " << reader.get_doubleTriplet("B_dir").d_3 << endl;
//  cout << "nplacements = " << reader.get_int("nplacements") << endl;
//  cout << "output_mode = " << reader.get_string("output_mode") << endl;
//  cout << "include_1c = " << reader.get_bool("include_1c") << endl;
//  cout << "I = " << reader.get_frac("I").num << " / " << reader.get_frac("I").den << endl;

//  return 0;

//}





