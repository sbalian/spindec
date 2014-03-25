//#ifndef VERTEX_H_
//#define VERTEX_H_
//
//// Vertex
////
//// Vertex of a graph. Contains a label and contents.
////
//// Seto Balian, Mar 25, 2014
//
//#include "SpinDec/typedefs.h"
//#include "SpinDec/GraphContents.h"
//
//namespace SpinDec
//{
//
//class Vertex
//{
//protected:
//  UInt label_;
//  auto_ptr<GraphContents> contents_;
//
//public:
//  Vertex();
//  Vertex(const UInt label, const auto_ptr<GraphContents>& contents);
//  
//  UInt get_label() const;
//  auto_ptr<GraphContents> get_contents() const;
//  
//  virtual auto_ptr<Vertex> clone() const = 0;
//  
//  virtual ~Vertex();
//  
//};
//
//} // namespace SpinDec
//
//#endif // VERTEX_H_
