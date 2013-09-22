#ifndef CCEREAD_H
#define CCEREAD_H

// Reads CCE program parameters from an input file

// Created  06/10/2012
// Modified 07/10/2012, 31/10/2012
// Seto Balian
// V1

#include "stdincludes.hpp"

using namespace std;

class cceread
{
private:

string infilename;
string readprofilename;

map_string_double   readprof_d;
map_string_int      readprof_i;
map_string_bool     readprof_b;
map_string_string   readprof_s;
map_string_string   readprof_type;

map_string_frac          readprof_f;
map_string_doubleTriplet readprof_t;

bool silent;

public:

  cceread();
  cceread(const string & infilename_in, const string & readprofilename_in, const bool silent_in);
  cceread(const string & infilename_in, const string & readprofilename_in);


  void set_profile();
  void read();

  double get_double(const string & parametername) const;
  int get_int(const string & parametername) const;
  bool get_bool(const string & parametername) const;
  string get_string(const string & parametername) const;
  string get_type(const string & parametername) const;

  frac get_frac(const string & parametername) const;
  doubleTriplet get_doubleTriplet(const string & parametername) const;

  int readprofilename_to_index(const string & readprofilename_in) const;

  double string_to_double( const string& s ) const;
  int    string_to_int( const string& s ) const;
  bool   string_to_bool( const string& s ) const;
  frac string_to_frac( const string& s ) const;
  doubleTriplet string_to_doubleTriplet( const string& s ) const;

  void set_double(const string & parametername, const double value) ;
  void set_int(const string & parametername, const int value) ;
  void set_bool(const string & parametername, const bool value) ;
  void set_string(const string & parametername, const string & value) ;
  void set_frac(const string & parametername, const frac & value) ;
  void set_doubleTriplet(const string & parametername, const doubleTriplet & value) ;


};

#endif // CCEREAD_H

