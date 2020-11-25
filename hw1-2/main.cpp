//1_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество
// вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода против часовой стрелки.
//n < 1000, координаты < 10000.
//Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой
// стороной многоугольника.
//Требования: Координата должна быть реализована в виде структуры.

#include <iostream>
#include <cassert>
#include <cmath>

struct Point {
  int x = 0;
  int y = 0;
};

double calculateSquare(Point* array, int pointQuantity);

int main() {
  int n = 0;

  std::cin >> n;
  assert(n >= 3);

  auto array = new Point[n];


  for (int i = 0; i < n; ++i) {
    std::cin >> array[i].x >> array[i].y;
  }

  std::cout << calculateSquare(array, n);

  delete [] array;
  return EXIT_SUCCESS;
}

double calculateSquare(Point* array, int pointQuantity) {
  double square = 0;

  for (int i = 0; i < pointQuantity - 1; ++i) {
    square += (array[i + 1].x - array[i].x) * (array[i].y + array[i + 1].y);
  }

  square += (array[0].x - array[pointQuantity - 1].x) * (array[0].y + array[pointQuantity - 1].y);

  return abs(square) / 2.0;
}
