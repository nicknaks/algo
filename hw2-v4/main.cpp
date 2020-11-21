//Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
// Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
// ближайшего по значению к B[i].

#include <iostream>

int binarySearch(const int* array, int first, int last, int key, int arraySize);
void findBorder (const int* array, int size, int element, int& first, int& last);
int* initArray(int& size);

int findNearestIndex(const int* array, int key, int arraySize);

int main() {
  int* A = nullptr;
  int* B = nullptr;
  int sizeA = 0;
  int sizeB = 0;

  A = initArray(sizeA);
  B = initArray(sizeB);

  for (int i = 0; i < sizeB; ++i) {
    int first = 0, last = 0;
//    findBorder(A, sizeA, B[i], first, last);
//    int result = binarySearch(A, first, last, B[i], sizeA);
    int result = findNearestIndex(A, B[i], sizeA);
    std::cout << result << " ";
  }

  delete [] B;
  delete [] A;
  return 0;
}


int* initArray(int &size) {
  std::cin >> size;
  int* array = new int[size];
  for (int i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  return array;
}

void findBorder(const int *array, int size, int element, int& first, int& last) {
  if (size == 0) {
    return;
  }

  first = 0;
  last = 1;

  while(last < size) {
    if (element <= array[last]) {
      return;
    }

    first = last;
    last *= 2;
  }

  last = size - 1;
}

int binarySearch(const int *array, int first, int last, int key, int arraySize) {
  while (last - first > 1) {
    int middle = (first + last) / 2;
    int guess = array[middle];

    if (key > guess) {
      first = middle;
    } else {
      last = middle;
    }
  }

  if (key - array[first] > array[last] - key) {
    return last;
  }

  return first;
}
int findNearestIndex(const int *array, int key, int arraySize) {
  int first = 0;
  int last = 1;

  if (key <= array[first]) {
    return first;
  }

  if (key >= array[arraySize - 1]) {
    return arraySize - 1;
  }

  findBorder(array, arraySize, key, first, last);
  return binarySearch(array, first, last, key, arraySize);
}
