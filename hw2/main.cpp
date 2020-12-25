#include <vector>
#include <iostream>
#include <queue>
#include <cassert>

using std::vector;
using std::queue;

struct IGraph {
  virtual ~IGraph() {}

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const  = 0;

  virtual vector<int> GetNextVertices(int vertex) const = 0;
  virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

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

int BFS(const IGraph &graph, int fromVertex, int toVertex) {
  vector<int> lengthCount(graph.VerticesCount(), 0);
  vector<int> minLength(graph.VerticesCount(), 0);
  queue<int> bfcQueue;
  bfcQueue.push(fromVertex);

  minLength[fromVertex] = 1;
  lengthCount[fromVertex] = 1;

  while (!bfcQueue.empty()) {
    int current = bfcQueue.front();
    bfcQueue.pop();
    vector<int> adjacentVerticies = graph.GetNextVertices(current);
    for (const int &nextVertex : adjacentVerticies) {
      if ((minLength[nextVertex] == 0 || minLength[nextVertex] > minLength[current])) {
        if (lengthCount[nextVertex] == 0) {
          bfcQueue.push(nextVertex);
        }
        minLength[nextVertex] = minLength[current] + 1;
        lengthCount[nextVertex] += lengthCount[current];
      }
    }
  }

  if (toVertex == fromVertex) {
    return lengthCount[fromVertex] - 1;
  }
  return lengthCount[toVertex];
}


int main() {
  int countEdge = 0;
  int countVertex = 0;
  std::cin >> countVertex;
  std::cin >> countEdge;

  ListGraph graph(countVertex);

  for (int i = 0; i < countEdge; ++i) {
    int from = 0, to = 0;
    std::cin >> from >> to;
    graph.AddEdge(from, to);
    graph.AddEdge(to, from);
  }

  int vertex1 = 0, vertex2 = 0;
  std::cin >> vertex1 >> vertex2;

  std::cout << BFS(graph, vertex1, vertex2);
}

