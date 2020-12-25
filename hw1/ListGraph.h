#ifndef HW1__LISTGRAPH_H_
#define HW1__LISTGRAPH_H_

#include "IGraph.h"

class ListGraph : public IGraph {
 public:
  ListGraph(int vertexCount);
  ListGraph(const IGraph &graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;
  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  vector<vector<int>> adjacencyLists;
};

#endif //HW1__LISTGRAPH_H_
