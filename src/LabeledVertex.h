#ifndef LABELEDVERTEX_H_
#define LABELEDVERTEX_H_

// LabeledVertex
//
// Labeled graph vertex.
//
// Seto Balian, Dec 10, 2013

class LabeledVertex
{
private:
  unsigned int label_;

public:
  LabeledVertex();
  LabeledVertex(const unsigned int label);

  unsigned int get_label() const;

};

#endif // LABELEDVERTEX_H_
