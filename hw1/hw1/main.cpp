#include <iostream>
#include <queue>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

using std::queue;

template<typename F>
void BFS(const IGraph &graph, int vertex, const F& visit) {
  vector<bool> visited(graph.VerticesCount(), false);
  queue<int> bfsQueue;
  bfsQueue.push(vertex);
  visited[vertex] = true;

  while (!bfsQueue.empty()) {
    int current = bfsQueue.front();
    bfsQueue.pop();
    visit(current);
    vector<int> adjacentVeticies = graph.GetNextVertices(current);
    for (int i = 0; i < adjacentVeticies.size(); ++i)
      if (!visited[adjacentVeticies[i]]) {
        bfsQueue.push(adjacentVeticies[i]);
        visited[adjacentVeticies[i]] = true;
      }
  }
}

int main() {
  ListGraph graph(5);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 3);
  graph.AddEdge(0, 4);
  graph.AddEdge(1, 4);
  graph.AddEdge(4, 2);

  int count1 = 0;

  BFS(graph, 0, [&count1](int vertex) { count1++;});

  int count2 = 0;

  MatrixGraph matrix_graph(graph);
  BFS(matrix_graph, 0, [&count2](int vertex) { count2++;});

  int count3 = 0;

  SetGraph set_graph(graph);
  BFS(set_graph, 0, [&count3](int vertex) { count3++;});

  int count4 = 0;

  ArcGraph arc_graph(graph);
  BFS(arc_graph, 0, [&count4](int vertex) { count4++;});

  std::cout << count1 << " " << count2 << " " << count3 << " " << count4;
  return 0;
}
