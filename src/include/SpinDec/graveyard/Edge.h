//#ifndef EDGE_H_
//#define EDGE_H_
//
//// Edge
////
//// Graph edge. Contains a pair of vertices and contents.
////
//// Seto Balian, Mar 25, 2014
//
//#include "SpinDec/typedefs.h"
//#include "SpinDec/GraphContents.h"
//#include "SpinDec/Vertex.h"
//
//namespace SpinDec
//{
//
//class Edge
//{
//protected:
//  pair< auto_ptr<Vertex>,auto_ptr<Vertex> > vertices_;
//  auto_ptr<GraphContents> contents_;
//  
//public:
//  Edge();
//  Edge(const Edge& other);
//
//  Edge(const auto_ptr<Vertex>& vertex1,
//       const auto_ptr<Vertex>& vertex2,
//       const auto_ptr<GraphContents>& contents);
//  
//  auto_ptr<Vertex> get_vertex1() const;
//  auto_ptr<Vertex> get_vertex2() const;
//  auto_ptr<GraphContents> get_contents() const;
//  
//  Edge& operator=( const Edge& other);
//  
//  virtual auto_ptr<Edge> clone() const = 0;
//  
//  virtual ~Edge();
//  
//};
//
//} // namespace SpinDec
//
//#endif // EDGE_H_
