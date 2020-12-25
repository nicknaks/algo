#include "SetGraph.h"
SetGraph::SetGraph(int vertexCount) : adjacencyLists(vertexCount) {}

void SetGraph::AddEdge(int from, int to) {
  assert(from >= 0 && from < adjacencyLists.size());
  assert(to >= 0 && to < adjacencyLists.size());

  adjacencyLists[from].insert(to);
}

int SetGraph::VerticesCount() const {
  return adjacencyLists.size();
}

vector<int> SetGraph::GetNextVertices(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  return vector(adjacencyLists[vertex].begin(), adjacencyLists[vertex].end());
}

vector<int> SetGraph::GetPrevVertices(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());

  vector<int> prevVertices;

  for (int from = 0; from < adjacencyLists.size(); ++from) {
    if (adjacencyLists[from].count(vertex) != 0) {
      prevVertices.push_back(from);
    }
  }

  return prevVertices;
}

SetGraph::SetGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()){
  for (int from = 0; from < graph.VerticesCount(); ++from) {
    vector<int> nextVertices = graph.GetNextVertices(from);
    for (int & to : nextVertices) {
      adjacencyLists[from].insert(to);
    }
  }
}


