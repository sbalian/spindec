//// See Vertex.h for description.
//// Seto Balian, Mar 25, 2014
//
//#include "include/SpinDec/Vertex.h"
//
//namespace SpinDec
//{
//
//Vertex::Vertex() : label_(0)
//{
//}
//
//Vertex::Vertex(const UInt label,
//    const auto_ptr<GraphContents>& contents) :
//        label_(0)
//{
//  contents_ = contents->clone();
//}
//
//UInt Vertex::get_label() const
//{
//  return label_;
//}
//
//auto_ptr<GraphContents> Vertex::get_contents() const
//{
//  return contents_->clone();
//}
//
//Vertex::~Vertex()
//{
//  
//}
//  
//
//} // namespace SpinDec
//
