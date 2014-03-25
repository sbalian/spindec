//// See Edge.h for description.
//// Seto Balian, Mar 25, 2014
//
//#include "include/SpinDec/Edge.h"
//
//namespace SpinDec
//{
//
//Edge::Edge()
//{
//}
//
//Edge::Edge(const Edge& other)
//{
//  vertices_.first = other.get_vertex1();
//  vertices_.second = other.get_vertex2();
//  contents_ = other.get_contents();
//}
//
//Edge::Edge(const auto_ptr<Vertex>& vertex1,
//           const auto_ptr<Vertex>& vertex2,
//           const auto_ptr<GraphContents>& contents)
//{
//  vertices_.first = vertex1->clone();
//  vertices_.second = vertex2->clone();
//  contents_ = contents->clone();
//}
//
//auto_ptr<Vertex> Edge::get_vertex1() const
//{
//  return vertices_.first->clone();
//}
//
//auto_ptr<Vertex> Edge::get_vertex2() const
//{
//  return vertices_.second->clone();
//}
//
//auto_ptr<GraphContents> Edge::get_contents() const
//{
//  return contents_->clone();
//}
//
//Edge& Edge::operator =(const Edge& other)
//{
//  vertices_.first = other.get_vertex1();
//  vertices_.second = other.get_vertex2();
//  contents_ = other.get_contents();
//  return *this;
//}
//
//Edge::~Edge() {}
//
//} // namespace SpinDec
//
