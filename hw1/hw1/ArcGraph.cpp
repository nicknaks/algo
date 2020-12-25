#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertexCount) : vertexCount(vertexCount) { }

void ArcGraph::AddEdge(int from, int to) {
  pairs.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
  return vertexCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> nextVertices;
  for (const auto& pair : pairs) {
    if (pair.from == vertex) {
      nextVertices.push_back(pair.to);
    }
  }
  return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> prevVertices;
  for (const auto& pair : pairs) {
    if (pair.to == vertex) {
      prevVertices.push_back(pair.from);
    }
  }

  return prevVertices;
}

ArcGraph::ArcGraph(const IGraph &graph) : vertexCount(graph.VerticesCount()) {
  for (int from = 0; from < vertexCount; ++from) {
    vector<int> nextVertices = graph.GetNextVertices(from);
    for (const auto& to : nextVertices) {
      pairs.emplace_back(from, to);
    }
  }
}




