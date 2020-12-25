#ifndef HW1__MATRIXGRAPH_H_
#define HW1__MATRIXGRAPH_H_

#include "IGraph.h"

class MatrixGraph : public IGraph {
 public:
  explicit MatrixGraph(int vertexCount);
  MatrixGraph(const IGraph &graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;
  vector<int> GetNextVertices(int vertex) const override;
  vector<int> GetPrevVertices(int vertex) const override;

 private:
  vector<vector<int>> matrix;
};

#endif //HW1__MATRIXGRAPH_H_
