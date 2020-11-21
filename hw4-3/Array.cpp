#ifndef HW4_3__ARRAY_CPP_
#define HW4_3__ARRAY_CPP_

#include <cstdlib>
#include <cstring>

struct TrainTimes {
  int arriveTime = 0;
  int departureTime = 0;
};


template <typename T>
class Array {
 public:
  Array() : ptr(nullptr), size(0), capacity(0) {
    ptr = new T[2]();
    capacity = 4;
  }

  Array(const Array& rhs) : capacity(rhs.capacity), size(rhs.size){
    ptr = new T[capacity]();
    memcpy(ptr, rhs.ptr, size * sizeof(T));
 }

  Array& operator = (const Array& rhs) {
    size = rhs.size;
    capacity = rhs.capacity;
    delete [] ptr;
    ptr = new T[capacity]();
    memcpy(ptr, rhs.ptr, size * sizeof(T));
    return *this;
  }

  ~Array() {
    delete [] ptr;
  }

  void PushBack(const T& element) {
    if (size == capacity) {
      resize();
    }

    ptr[size++] = element;
  }

  int PopBack() {
    if (size != 0) {
      size--;
    }
    return ptr[size];
  }

  void Swap(int rhs, int lhs) {
    if (rhs == lhs) {
      return;
    }
    T tmp = ptr[rhs];
    ptr[rhs] = ptr[lhs];
    ptr[lhs] = tmp;
  }

  size_t Size() const { return size; }
  bool IsEmpty() const { return size == 0; }
  T& operator[] (const int& index) { return ptr[index]; }

 private:
  T* ptr;
  size_t size;
  size_t capacity;

  void resize() {
    int* tmpPtr = new T[capacity * 2]();
    memcpy(tmpPtr, &ptr[0], size * sizeof(int));
    delete [] ptr;
    ptr = tmpPtr;
    capacity *= 2;
  }
};

#endif //HW4_3__ARRAY_CPP_
