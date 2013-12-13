#ifndef LABELEDVERTEX_H_
#define LABELEDVERTEX_H_

// LabeledVertex
//
// Labeled graph vertex.
//
// Seto Balian, Dec 13, 2013

#include "VertexContents.h"

class LabeledVertex
{
private:
  unsigned int label_;
  VertexContents contents_;

public:
  LabeledVertex();
  LabeledVertex(const unsigned int label, const VertexContents & contents);

  unsigned int get_label() const;
  VertexContents get_contents() const;

};

#endif // LABELEDVERTEX_H_
