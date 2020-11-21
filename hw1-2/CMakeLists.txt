cmake_minimum_required(VERSION 3.17)
project(hw1_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw1_2 main.cpp)

#int main() {
#size_t n = 0;
#std::cin >> n;
#
#Point point1, point2, startPoint;
#std::cin >> startPoint.x >> startPoint.y;
#
#point1 = startPoint;
#
#double square = 0;
#
#for (int i = 0; i + 1 < n; ++i) {
#std::cin >> point2.x >> point2.y;
#square += (point2.x - point1.x) * (point1.y + point2.y);
#point1 = point2;
#}
#
#square += (startPoint.x - point1.x) * (point1.y + startPoint.y);
#
#std::cout << abs(square) / 2;
#
#return EXIT_SUCCESS;
#}
