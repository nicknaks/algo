#ifndef HW1__IGRAPH_H_
#define HW1__IGRAPH_H_

#include <vector>

using std::vector;

struct IGraph {
  virtual ~IGraph() {}

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const  = 0;

  virtual vector<int> GetNextVertices(int vertex) const = 0;
  virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //HW1__IGRAPH_H_
