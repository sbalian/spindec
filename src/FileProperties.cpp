// See FileProperties.h for description.
// Seto Balian, Apr 2, 2014

#include "SpinDec/FileProperties.h"
#include "SpinDec/Errors.h"

#include <fstream>

namespace SpinDec
{

bool FileProperties::exists(const string file_name)
{
  // start stream
  std::ifstream input_file(file_name.c_str());
  // check if file is open
  if (input_file.is_open()) {
    input_file.close();
    return true;
  }
  return false;
}

UInt FileProperties::num_lines(const string file_name)
{
  
  // check if file exists
  if (!exists(file_name)) {
    string message = "File ";
    message += file_name;
    message += "does not exist.";
    Errors::quit(message);
  }
  
  // start stream
  std::ifstream input_file(file_name.c_str());
  UInt num_lines = 0;
  string temp_string;
  while (std::getline(input_file, temp_string)) {
    if (temp_string == "") {
      continue;
    }
    num_lines++;
  }
  input_file.close();
  return num_lines;
  
}

} // namespace SpinDec

