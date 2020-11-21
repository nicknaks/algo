#ifndef HW4_3__HEAP_CPP_
#define HW4_3__HEAP_CPP_

#include "Array.cpp"

template<typename T>
class Heap {
 public:
  // конструкторы деструкторы
  explicit Heap(bool (*isLess)(const T &, const T &) = isLessDefault) : arr(Array<T>()), maxSize(0), cmp(isLess) {}

  explicit Heap(const Array<T> &_arr, bool (*isLess)(const T &, const T &) = isLessDefault)
      : arr(_arr), maxSize(0), cmp(isLess) {
    buildHeap();
  }

  ~Heap() = default;

  // добавление в кучу с удалением первого элемента
  void InsertAndExtractHead(const T &element) {
    arr.PushBack(element);
    ExtractHead();
  }

  // добавление в кучу без удаления первого элемента
  void Insert(const T &element) {
    arr.PushBack(element);
    siftUp(static_cast<int>(arr.Size()) - 1);
    maxSize++;
  }

  // извлечение минимума
  int ExtractHead() {
    assert(!arr.IsEmpty());

    int result = arr[0];
    arr[0] = arr.PopBack();

    if (!arr.IsEmpty()) {
      siftDown(0);
    }
    return result;
  }

  // просмотр минимума без удаления
  int PeekHead() { return arr[0]; }

  size_t MaxSize() const { return maxSize; }

 private:
  Array<T> arr; // динамический массив для хранения кучи
  size_t maxSize;
  bool (*cmp)(const T &, const T &);

  static bool isLessDefault(const T &l, const T &r) {
    return l < r;
  }

  void buildHeap() {
    for (int i = arr.Size() / 2 - 1; i >= 0; --i) {
      siftDown(i);
    }
  }

  void siftUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (arr[index] == arr[parent] || !cmp(arr[index], arr[parent])) {
        return;
      }
      arr.Swap(index, parent);
      index = parent;
    }
  }

  void siftDown(int index) {
    int smallest = -3;

    while (smallest != index) {
      smallest = index;

      int left = 2 * index + 1;
      int right = 2 * index + 2;

      if (left < arr.Size() && cmp(arr[left], arr[index]))
        smallest = left;
      if (right < arr.Size() && cmp(arr[right], arr[smallest]))
        smallest = right;

      arr.Swap(index, smallest);
    }
  }
};

#endif //HW4_3__HEAP_CPP_