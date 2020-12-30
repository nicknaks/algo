#include <vector>
#include <iostream>
#include <queue>
#include <cassert>
#include <set>
#include <utility>
#include <limits.h>

using std::vector;
using std::queue;

class ListGraph {
 public:
  ListGraph(int vertexCount);
  ~ListGraph() = default;

  void AddEdge(int from, int to, int i);

  int VerticesCount() const;
  vector<std::pair<int, int>> GetNextVertices(int vertex) const;
  vector<std::pair<int, int>> GetPrevVertices(int vertex) const;

 private:
  vector<vector<std::pair<int, int>>> adjacencyLists;
};

ListGraph::ListGraph(int vertexCount) : adjacencyLists(vertexCount) {}

void ListGraph::AddEdge(int from, int to, int i) {
  assert(from >= 0 && from < adjacencyLists.size());
  assert(to >= 0 && to < adjacencyLists.size());

  adjacencyLists[from].push_back(std::make_pair(to, i));
}

int ListGraph::VerticesCount() const {
  return adjacencyLists.size();
}

vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  return adjacencyLists[vertex];
}

vector<std::pair<int, int>> ListGraph::GetPrevVertices(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  vector<std::pair<int, int>> result;
  for (int from = 0; from < adjacencyLists.size(); ++from)
    for (int i = 0; i < adjacencyLists[from].size(); ++i)
      if (adjacencyLists[from][i].first == vertex)
        result.emplace_back(from, adjacencyLists[from][i].second);
  return result;
}

bool operator < (const std::pair<int, int>& rhs, const std::pair<int, int>& lhs) {
  return lhs.first < rhs.first;
}

int Dijkstra(const ListGraph &graph, int fromVertex, int toVertex) {
  vector<bool> pi(graph.VerticesCount(), false);
  vector<int> d(graph.VerticesCount(), INT_MAX);
  d[fromVertex] = 0;

  std::set<std::pair<int, int>> bfsQueue;
  bfsQueue.emplace(std::make_pair(0, fromVertex));

  while (!bfsQueue.empty()) {
    int current = bfsQueue.begin()->second;
    bfsQueue.erase(bfsQueue.begin());

    auto adjacentVerticies = graph.GetNextVertices(current);
    pi[current] = true;
    for (const auto &nextVertex : adjacentVerticies) {
      if (d[nextVertex.first] > d[current] + nextVertex.second) {

        if (d[nextVertex.first] != INT_MAX)
          bfsQueue.erase(std::make_pair(d[nextVertex.first], nextVertex.first));

        d[nextVertex.first] = d[current] + nextVertex.second;
        bfsQueue.emplace(std::pair<int, int>(d[nextVertex.first], nextVertex.first));
      }
    }
  }
  return d[toVertex];
}

int main() {
  int countEdge = 0;
  int countVertex = 0;
  std::cin >> countVertex;
  std::cin >> countEdge;

  ListGraph graph(countVertex);

  for (int i = 0; i < countEdge; ++i) {
    int from = 0, to = 0, time = 0;
    std::cin >> from >> to >> time;
    graph.AddEdge(from, to, time);
    graph.AddEdge(to, from, time);
  }

  int vertex1 = 0, vertex2 = 0;
  std::cin >> vertex1 >> vertex2;

  std::cout << Dijkstra(graph, vertex1, vertex2);
}
