#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexCount) : matrix(vertexCount) {
  for (int i = 0; i < vertexCount; ++i) {
    matrix[i].resize(vertexCount);
    for (int j = 0; j < matrix[i].size(); ++j) {
      matrix[i][j] = 0;
    }
  }
}

void MatrixGraph::AddEdge(int from, int to) {
  assert(from >= 0 && from < matrix.size());
  assert(to >= 0 && to < matrix.size());
  matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
  return matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
  assert(vertex >= 0 && vertex < matrix.size());

  vector<int> nextVertices;

  for (int i = 0; i < matrix[vertex].size(); ++i) {
    if (matrix[vertex][i] == 1) {
      nextVertices.push_back(i);
    }
  }

  return nextVertices;
}

vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
  assert(vertex >= 0 && vertex < matrix.size());

  vector<int> prevVertices;

  for (int i = 0; i < matrix.size(); ++i) {
    if (matrix[i][vertex] == 1) {
      prevVertices.push_back(i);
    }
  }

  return prevVertices;
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
  matrix.resize(graph.VerticesCount());

  for (int from = 0; from < matrix.size(); ++from) {
    matrix[from].resize(graph.VerticesCount());
    for (int to = 0; to < matrix.size(); ++to) {
      matrix[from][to] = 0;
    }
    vector<int> nextVertices = graph.GetNextVertices(from);
    for (int to : nextVertices) {
      matrix[from][to] = 1;
    }
  }
}
