#ifndef HW1__ARCGRAPH_H_
#define HW1__ARCGRAPH_H_

#include "IGraph.h"

class ArcGraph : public IGraph{
 public:
  ArcGraph(int vertexCount);
  ArcGraph(const IGraph &graph);

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;
  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  struct Pair{
    int from;
    int to;
    Pair(int _from, int _to) : from(_from), to(_to) {}
    Pair() = default;
  };

  vector<Pair> pairs;
  int vertexCount;
};

#endif //HW1__ARCGRAPH_H_
