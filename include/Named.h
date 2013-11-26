#ifndef NAMED_H
#define	NAMED_H

// Named
//
// For everything that has a name.
// Stores class and object (particular instance of class) names.
//
// Seto Balian, November 26, 2013

#include <string>

class Named
{

private:
  std::string class_name_;
  std::string object_name_;

public:
  
  Named();
  void set_class_name(const std::string & class_name);
  void set_object_name(const std::string & object_name);

  std::string get_class_name() const;
  std::string get_object_name() const;


};

#endif	 // NAMED_H
