#ifndef FILEPROPERTIES_H_
#define FILEPROPERTIES_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// Static methods for ASCII file properties.
class FileProperties
{
public:
  
  static bool exists(const string file_name);
  
  /// NOTE: empty lines not counted.
  static UInt num_lines(const string file_name);
  
};

} // namespace SpinDec

#endif // FILEPROPERTIES_H_
