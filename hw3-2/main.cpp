#include <iostream>

#include "Deque.h"

int main() {
  Deque d;
  d.PushBack(10);
  d.PushBack(9);
  d.PushBack(1);
  d.PushBack(2);
  d.PushBack(23);
  std::cout << d.PopBack() << " " <<d.PopBack() << " " <<d.PopBack() <<  " " <<d.PopBack() <<  " " <<d.PopBack();
  std::cout << std::endl;

  d.PushBack(111);
  std::cout << d.PopBack();
  std::cout << d.PopBack();

  return EXIT_SUCCESS;
}