#ifndef HW1__SETGRAPH_H_
#define HW1__SETGRAPH_H_

#include <set>
#include "IGraph.h"

using std::set;

class SetGraph : public IGraph{
 public:
  explicit SetGraph(int vertexCount);
  explicit SetGraph(const IGraph &graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;
  vector<int> GetNextVertices(int vertex) const override;
  vector<int> GetPrevVertices(int vertex) const override;

 private:
  vector<set<int>> adjacencyLists;
};

#endif //HW1__SETGRAPH_H_
