#include <iostream>
#include <sstream>

#include "Heap.cpp"

void InsertTrainTimesInHeap(const TrainTimes& trainTimes, Heap<int>& trains){
  if (trains.MaxSize() != 0 && trainTimes.arriveTime > trains.PeekHead()) {
    trains.InsertAndExtractHead(trainTimes.departureTime);
    return;
  }

  trains.Insert(trainTimes.departureTime);
}


int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  size_t n = 0;
  std::cin >> n;

  TrainTimes inputTimes;

  Heap<int> Trains;

  for (int i = 0; i < n; ++i) {
    std::cin >> inputTimes.arriveTime >> inputTimes.departureTime;
    InsertTrainTimesInHeap(inputTimes, Trains);
  }

  std::cout << Trains.MaxSize();

  return 0;
}