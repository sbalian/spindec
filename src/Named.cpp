// See Named.h for description.
// Seto Balian 25/11/2013

#include "Named.h"

Named::Named() {
  set_class_name("AnonymousClass");
  set_object_name("AnonymousObject");
}

void Named::set_class_name(const std::string & class_name) {
  class_name_ = class_name;
  return;
}

void Named::set_object_name(const std::string & object_name) {
  object_name_ = object_name;
  return;
}

std::string Named::get_class_name() const {
  return class_name_;
}

std::string Named::get_object_name() const {
  return object_name_;
}
