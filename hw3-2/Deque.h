#ifndef HW3_2__DEQUE_H_
#define HW3_2__DEQUE_H_

#include <iostream>

class Deque {
 public:
  Deque();
  ~Deque();

  // добавление элемента
  int PushBack(const int& value);
  int PushFront(const int& value);

  // удаление элемента
  int PopBack();
  //int& PopFront();

  bool IsEmpty() const { return size == 0;}
 private:
  int* ptr; // указатель на начало массива
  int head; // индекс головы
  int tail; // индекс хвоста
  size_t size;
  size_t capacity;

  int Resize();
};


#endif //HW3_2__DEQUE_H_
