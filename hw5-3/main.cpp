#include <iostream>
#include <algorithm>

struct Point {
  int x;
  int type; // '+1' - start point. '-1' - end point
};

bool operator < (const Point &l, const Point &r) {
  return l.x < r.x;
}

bool operator == (const Point &l, const Point &r) {
  return l.x == r.x;
}

template<typename T>
bool isLessDefault(const T &l, const T &r) {
  return l < r;
}

int CalculateLen(const Point *array, int size) {
  int event = 0;
  bool zeroFound = false;
  int len = 0;

  for (int i = 0; i < size; ++i) {
    event += array[i].type;
    if (event == 0) {
      len += array[i].x;
      zeroFound = true;
      continue;
    }

    if (zeroFound) {
      len -= array[i].x;
      zeroFound = false;
    }
  }

  return len - array[0].x;
}

template <typename T>
void Merge(const T *firstArray, int firstSize, const T *secondArray, int secondSize,
           T *mainArray, bool (*isLess)(const T &, const T &)) {
  int i = 0, j = 0, k = 0;
  while (i < firstSize && j < secondSize) {
    if (firstArray[i] == secondArray[j] || isLess(firstArray[i], secondArray[j])) {
      mainArray[k] = firstArray[i];
      i++;
    } else {
      mainArray[k] = secondArray[j];
      j++;
    }
    k++;
  }

  for (; i < firstSize; ++i, ++k) {
    mainArray[k] = firstArray[i];
  }

  for (; j < secondSize; ++j, ++k) {
    mainArray[k] = secondArray[j];
  }
}

template <typename T>
void MergeSort(T *array, int arraySize, bool (*isLess)(const T &, const T &) = isLessDefault) {
  if (arraySize <= 1) {
    return;
  }

  int firstSize = arraySize / 2;
  int secondSize = arraySize - firstSize;
  MergeSort(array, firstSize);
  MergeSort(array + firstSize, secondSize);
  auto c = new T[arraySize];
  Merge(array, firstSize, array + firstSize, secondSize, c, isLess);
  memcpy(array, c, sizeof(T) * arraySize);
  delete[] c;
}

int main() {
  int n = 0;
  std::cin >> n;

  n *= 2;
  auto points = new Point[n]();

  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i + 1].x;
    points[i].type = 1;
    points[i + 1].type = -1;
    i++;
  }

  MergeSort(points, n);

  std::cout << CalculateLen(points, n);

  delete[] points;
  return 0;
}