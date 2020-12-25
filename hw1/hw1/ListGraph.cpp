#include "ListGraph.h"

ListGraph::ListGraph(int vertexCount) : adjacencyLists(vertexCount) {}

ListGraph::ListGraph(const IGraph &graph) {
  adjacencyLists.resize(graph.VerticesCount());
  for (int from = 0; from < adjacencyLists.size(); ++from)
    adjacencyLists[from] = graph.GetNextVertices(from);
}

void ListGraph::AddEdge(int from, int to) {
  assert(from >= 0 && from < adjacencyLists.size());
  assert(to >= 0 && to < adjacencyLists.size());

  adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
  return adjacencyLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  vector<int> result;
  for (int from = 0; from < adjacencyLists.size(); ++from)
    for (int i = 0; i < adjacencyLists[from].size(); ++i)
      if (adjacencyLists[from][i] == vertex)
        result.push_back(from);
  return result;
}