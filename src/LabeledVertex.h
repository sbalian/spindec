#ifndef LABELEDVERTEX_H_
#define LABELEDVERTEX_H_

// LabeledVertex
//
// Labeled graph vertex.
//
// Seto Balian, Dec 11, 2013

class LabeledVertex
{
private:
  unsigned int label_;
  VertexContent content_;

public:
  LabeledVertex();
  LabeledVertex(const unsigned int label, const VertexContent & content);

  unsigned int get_label() const;

};

#endif // LABELEDVERTEX_H_
