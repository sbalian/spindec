#ifndef FILEPROPERTIES_H_
#define FILEPROPERTIES_H_

// SpinDec::FileProperties
//
// Static methods for ASCII file properties.
//
// Seto Balian, Apr 2, 2014

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class FileProperties
{
public:
  
  static bool exists(const string file_name);
  static UInt num_lines(const string file_name); // empty lines not counted ...
  
};

} // namespace SpinDec

#endif // FILEPROPERTIES_H_
