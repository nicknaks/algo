#include <iostream>
#include <algorithm>

struct Point {
  int x;
  int type; // '+1' - start point. '-1' - end point
};

bool operator<(const Point &l, const Point &r) {
  return l.x < r.x;
}

template<typename T>
bool isLessDefault(const T &l, const T &r) {
  return l < r;
}

void CalculateLen(const Point &element, int &event, int &count, bool &zeroFound) {
  event += element.type;
  if (event == 0) {
    count += element.x;
    zeroFound = true;
    return;
  }

  if (zeroFound) {
    count -= element.x;
    zeroFound = false;
  }
}

void Merge(const Point *firstArray,
           int firstSize,
           const Point *secondArray,
           int secondSize,
           Point *mainArray,
           int &len,
           bool (*isLess)(const Point &, const Point &)) {
  int event = 0;
  len = 0;
  bool zeroFound = false;

  int i = 0, j = 0, k = 0;
  while (i < firstSize && j < secondSize) {
    if (firstArray[i].x == secondArray[j].x || isLess(firstArray[i], secondArray[j])) {
      mainArray[k] = firstArray[i];
      i++;
    } else {
      mainArray[k] = secondArray[j];
      j++;
    }

    CalculateLen(mainArray[k], event, len, zeroFound);
    k++;
  }

  for (; i < firstSize; ++i, ++k) {
    mainArray[k] = firstArray[i];
    CalculateLen(mainArray[k], event, len, zeroFound);
  }

  for (; j < secondSize; ++j, ++k) {
    mainArray[k] = secondArray[j];
    CalculateLen(mainArray[k], event, len, zeroFound);
  }

  len -= mainArray[0].x;
}

void MergeSort(Point *array, int arraySize, int &len, bool (*isLess)(const Point &, const Point &) = isLessDefault) {
  if (arraySize <= 1) {
    return;
  }

  int firstSize = arraySize / 2;
  int secondSize = arraySize - firstSize;
  MergeSort(array, firstSize, len);
  MergeSort(array + firstSize, secondSize, len);
  auto c = new Point[arraySize];
  Merge(array, firstSize, array + firstSize, secondSize, c, len, isLess);
  memcpy(array, c, sizeof(Point) * arraySize);
  delete[] c;
}

int main() {
  int n = 0;
  std::cin >> n;

  auto points = new Point[n * 2]();

  for (int i = 0; i < n * 2; ++i) {
    std::cin >> points[i].x >> points[i + 1].x;
    points[i].type = 1;
    points[i + 1].type = -1;
    i++;
  }

  int len = 0;
  MergeSort(points, n * 2, len);

  std::cout << len;

  delete[] points;
  return 0;
}