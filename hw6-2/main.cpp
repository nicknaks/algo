//Реализуйте стратегию выбора опорного элемента “медиана трёх”.
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>
#include <algorithm>

template<typename T>
bool isLessDefault( const T& l, const T& r )
{
  return l > r;
}

template<typename T>
void Median(T* array, int left, int right) {
  int middle = (left + right) / 2;

  if (array[left] > array[middle]) {
    if (array[left] < array[right]) {
      std::swap(array[right], array[left]);
      std::swap(array[middle], array[left]);
    } else if (array[right] < array[middle]) {
        std::swap(array[middle], array[right]);
        std::swap(array[middle], array[left]);
    } else {
      std::swap(array[middle], array[left]);
    }
  } else {
    if (array[right] > array[middle]) {
      std::swap (array[middle], array[right]);
    } else if (array[right] < array[left]) {
        std::swap (array[right], array[left]);
    }
  }

}

template<typename T>
int Partition(T* array, int left, int right, bool (*isLess)(const T &, const T &)) {
  if (left - right == 0) {
    return 0;
  }

  Median(array, left, right);

  const int &pivot = array[right];
  // j <= i
  int i = right - 1;
  int j = i;

  // collect < pivot
  while (j >= left) {
    if (array[j] == pivot || isLess(array[j], pivot)) {
      std::swap(array[i--], array[j]);
    }
    j--;
  }

  std::swap(array[++i], array[right]);
  return i;
}

template<typename T>
int FindKStat(T* array, int size, int k, bool (*isLess)(const T &, const T &) = isLessDefault) {
  int left = 0;
  int right = size - 1;

  while (right > left) {
    int part = Partition(array, left, right, isLess);

    if (k == part) {
      return array[k];
    }

    if (k < part) {
      right = part - 1;
    } else {
      left = part + 1;
    }
  }

  return array[k];
}

int main() {
  int n = 0;
  std::cin >> n;

  int k = 0;
  std::cin >> k;

  auto array = new int[n];

  for (int i = 0; i < n ; ++i) {
    std::cin >> array[i];
  }

  std::cout << FindKStat(array, n, k);

  delete [] array;
}
