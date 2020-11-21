#include "Deque.h"

Deque::Deque() : ptr(nullptr), head(0), tail(0), size(0), capacity(0) {
  ptr = new int(2);
  assert(ptr != nullptr);

  capacity = 2;
}

Deque::~Deque() {
  delete [] ptr;
}

int Deque::PushBack(const int &value) {
  if (size == capacity) {
    Resize();
  }

  if (size != 0) {
    tail++;
  }
  ptr[tail] = value;

  size++;
  return EXIT_SUCCESS;
}

int Deque::PopBack() {
  if (tail == 0) {
    tail = static_cast<int>(size) - 1;
    size--;
    return ptr[tail];
  }

  size--;
  return  ptr[tail--];
}

int Deque::Resize() {
  int* tmpPtr = new int (capacity * 2);

  if (tail >= head) {
    memcpy(tmpPtr, ptr, size * sizeof(int));
  } else {
    memcpy(tmpPtr,&ptr[head], (size - head) * sizeof(int));
    memcpy(&tmpPtr[size - head], &ptr, tail * sizeof(int));
    head = 0;
    tail = static_cast<int>(size) - 1;
  }

  capacity *= 2;
  delete [] ptr;
  ptr = tmpPtr;
  return EXIT_SUCCESS;
}

int Deque::PushFront(const int &value) {
  if (head <= tail) {
    if (size == capacity) {
      Resize(value);
      return EXIT_SUCCESS;
    }
    head = tail + 1;
    ptr[head] = value;
    size++;
    return EXIT_SUCCESS;
    }
  }




//  if (head <= tail) {
//    if (head != 0) {
//      head--;
//      ptr[head] = value;
//      size++;
//      return EXIT_SUCCESS;
//    }
//
//    if (size == capacity) {
//      Resize();
//    }
//
//    head = tail + 1;
//    ptr[head] = value;
//    size++;
//    return EXIT_SUCCESS;
//  }
//
//  if (size == capacity) {
//    Resize();
//    head = tail + 1;
//    ptr[head] = value;
//    size++;
//    return EXIT_SUCCESS;
//  }
//
//  if () {
//
//  }

  return 0;
}
