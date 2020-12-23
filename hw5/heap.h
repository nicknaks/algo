#include <vector>
#include <iostream>
#include <stack>

template<typename T>
class Heap {
 public:
  // конструкторы деструкторы
  Heap() = default;
  ~Heap() = default;

  // добавление в кучу с удалением первого элемента
  void InsertAndExtractHead(const T &element) {
    arr.push_back(element);
    ExtractHead();
  }

  // добавление в кучу без удаления первого элемента
  void Insert(const T &element) {
    arr.push_back(element);
    siftUp(static_cast<int>(arr.size()) - 1);
  }

  // извлечение минимума
  T ExtractHead() {
    T result = arr[0];
    arr[0] = arr[arr.size() - 1];
    arr.pop_back();

    if (!arr.empty()) {
      siftDown(0);
    }

    return result;
  }

  // просмотр минимума без удаления
  T PeekHead() { return arr[0]; }

  void BuildHeap(const std::vector<T>& v) {
    arr = v;
    for (int i = arr.size() / 2 - 1; i >= 0; --i) {
      siftDown(i);
    }
  }

  size_t GetSize() const { return arr.size(); }
 private:
  void swap(int rhs, int lhs){
    if (rhs == lhs) {
      return;
    }

    T tmp = arr[rhs];
    arr[rhs] = arr[lhs];
    arr[lhs] = tmp;
  }

  std::vector<T> arr;

  void siftUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (arr[index] >= arr[parent]) {
        return;
      }

      swap(index, parent);
      index = parent;
    }
  }

  void siftDown(int index) {
    int smallest = -3;

    while (smallest != index) {
      smallest = index;

      int left = 2 * index + 1;
      int right = 2 * index + 2;

      if (left < arr.size() && arr[left] < arr[index])
        smallest = left;
      if (right < arr.size() && arr[right] < arr[smallest])
        smallest = right;

      swap(index, smallest);
    }
  }
};