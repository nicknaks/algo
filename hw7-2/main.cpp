// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
// Отсортировать массив методом поразрядной сортировки LSD по байтам.

#include <iostream>

int getDigit(long long value, int digit);
void countingSort(long long *array, int arraySize, size_t nByte);
void LSDSort(long long *array, int size);


int main() {
  int size = 0;
  std::cin >> size;

  auto *array = new long long[size];
  for(int i = 0; i < size; i++) {
    std::cin >> array[i];
  }

  LSDSort(array, size);
  for(int i = 0; i < size; i++) {
    std::cout << array[i] << " ";
  }

  delete[] array;

  return 0;
}

int getDigit(long long int value, size_t digit) {
  return value >> (8 * digit) & 255;
}

void countingSort(long long int *array, int arraySize, size_t nByte) {
  size_t count[256];

  for(size_t & i : count) {
    i = 0;
  }

  for(int i = 0; i < arraySize; i++) {
    count[getDigit(array[i], nByte)]++;
  }

  for(int i = 1; i < 256; i++) {
    count[i] += count[i - 1]; // Концы групп.
  }

  auto *result = new long long[arraySize];

  for(int i = arraySize - 1; i >= 0; --i) {
    result[--count[getDigit(array[i], nByte)]] = array[i];
  }

  memcpy(array, result, arraySize * sizeof(long long));
  delete[] result;
}

void LSDSort(long long int *array, int size) {
  for(size_t i = 0; i < sizeof(long long); i++) {
    countingSort(array, size, i);
  }
}