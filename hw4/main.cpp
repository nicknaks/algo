#include <array>
#include <queue>
#include <unordered_map>
#include <assert.h>
#include <string>
#include <iostream>
#include <set>
#include <utility>
#include <stdio.h>
#include <cstring>
#include <algorithm>

using std::array;
using std::queue;
using std::unordered_map;
using std::swap;
using std::string;
using std::cout;
using std::ostream;

const int SideSize = 4;
const int FieldSize = SideSize * SideSize;
const array<int, FieldSize> FinishField({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0});

class GameState {
 public:
  GameState(const array<int, FieldSize> &_field);

  bool CanMoveLeft() const;
  bool CanMoveUp() const;
  bool CanMoveRight() const;
  bool CanMoveDown() const;

  GameState MoveLeft() const;
  GameState MoveUp() const;
  GameState MoveRight() const;
  GameState MoveDown() const;

  int countH() {
    int h = 0;
    for (int i = 0; i < field.size(); i++) {
      int elem = field[i];
      if (elem == 0) {
        h += abs(3 - i / 4) + abs(3 - i % 4);
      } else {
        h += abs((elem - 1) / 4 - i / 4) + abs((elem - 1) % 4 - i % 4);
      }
    }
    return h;
  }

  bool IsFinish() const;

  bool operator==(const GameState &state) const { return field == state.field; }
  bool operator!=(const GameState &state) const { return !(*this == state); }
 private:
  array<int, FieldSize> field;
  int zeroPos;

  friend ostream &operator<<(ostream &out, const GameState &state);
  friend struct StateHasher;
};

ostream &operator<<(ostream &out, const GameState &state) {
  for (int y = 0; y < SideSize; ++y) {
    for (int x = 0; x < SideSize; ++x) {
      out << static_cast<int>(state.field[y * SideSize + x]) << " ";
    }
    out << std::endl;
  }
  return out;
}

GameState::GameState(const array<int, FieldSize> &_field) : field(_field), zeroPos(-1) {
  for (unsigned int i = 0; i < field.size(); ++i)
    if (field[i] == 0) {
      zeroPos = i;
      break;
    }
  assert(zeroPos != -1);
}

bool GameState::CanMoveLeft() const {
  return zeroPos % SideSize != 0;
}

bool GameState::CanMoveUp() const {
  return zeroPos >= SideSize;
}

bool GameState::CanMoveRight() const {
  return zeroPos % SideSize < SideSize - 1;
}

bool GameState::CanMoveDown() const {
  return zeroPos < FieldSize - SideSize;
}

GameState GameState::MoveLeft() const {
  assert(CanMoveLeft());
  GameState newState(*this);
  swap(newState.field[newState.zeroPos], newState.field[newState.zeroPos - 1]);
  --newState.zeroPos;
  return newState;
}

GameState GameState::MoveUp() const {
  assert(CanMoveUp());
  GameState newState(*this);
  swap(newState.field[newState.zeroPos], newState.field[newState.zeroPos - SideSize]);
  newState.zeroPos -= SideSize;
  return newState;
}

GameState GameState::MoveRight() const {
  assert(CanMoveRight());
  GameState newState(*this);
  swap(newState.field[newState.zeroPos], newState.field[newState.zeroPos + 1]);
  ++newState.zeroPos;
  return newState;
}

GameState GameState::MoveDown() const {
  assert(CanMoveDown());
  GameState newState(*this);
  swap(newState.field[newState.zeroPos], newState.field[newState.zeroPos + SideSize]);
  newState.zeroPos += SideSize;
  return newState;
}

bool GameState::IsFinish() const {
  return field == FinishField;
}

struct StateHasher {
  size_t operator()(const GameState &state) const {
    size_t hash = 0;
    memcpy(&hash, &state.field[0], sizeof(hash));
    return hash;
  }
};

using std::set;
using std::pair;
using std::vector;

int h() {
  return 0;
}

bool operator < (const pair<int, GameState>& rhs, const pair<int, GameState>& lhs) {
  return lhs.first > rhs.first;
}

string Get8thSolution(const GameState &state) {
  set<pair<int, GameState>> bfsQueue;
  bfsQueue.emplace(std::make_pair(1, state));
  unordered_map<GameState, pair<char, int>, StateHasher> visited;
  visited[state] = std::make_pair('S', 1);
  bool hasSolution = false;

  while (!bfsQueue.empty()) {
    GameState tempState = bfsQueue.begin()->second;
    bfsQueue.erase(bfsQueue.begin());

    if (tempState.IsFinish()) {
      hasSolution = true;
      break;
    }

    if (tempState.CanMoveLeft()) {
      GameState newState = tempState.MoveLeft();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = std::make_pair('L', visited[tempState].second);
        bfsQueue.emplace(std::make_pair(visited[newState].second + newState.countH(), newState));
      }
    }
    if (tempState.CanMoveUp()) {
      GameState newState = tempState.MoveUp();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = std::make_pair('U', visited[tempState].second);
        bfsQueue.emplace(std::make_pair(visited[newState].second + newState.countH(), newState));
      }
    }
    if (tempState.CanMoveRight()) {
      GameState newState = tempState.MoveRight();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = std::make_pair('R', visited[tempState].second);
        bfsQueue.emplace(std::make_pair(visited[newState].second + newState.countH(), newState));
      }
    }
    if (tempState.CanMoveDown()) {
      GameState newState = tempState.MoveDown();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = std::make_pair('D', visited[tempState].second);
        bfsQueue.emplace(std::make_pair(visited[newState].second + newState.countH(), newState));
      }
    }
  }

  if (!hasSolution)
    return "-1";

  string result;
  GameState tempState(FinishField);
  char move = visited[tempState].first;
  while (move != 'S') {
    result += move;
    switch (move) {
      case 'L':tempState = tempState.MoveRight();
        break;
      case 'U':tempState = tempState.MoveDown();
        break;
      case 'R':tempState = tempState.MoveLeft();
        break;
      case 'D':tempState = tempState.MoveUp();
        break;
    }
    move = visited[tempState].first;
  }
  std::reverse(result.begin(), result.end());
  return result;
}

int main() {
//  GameState state({8, 7, 6, 5, 4, 3, 2, 1, 0});
  array<int, FieldSize> tmp{};

  for (int i = 0; i <= 15; ++i) {
    int el = 0;
    std::cin >> el;
    tmp[i] = el;
  }

  GameState state(tmp);

  string solution = Get8thSolution(state);

  if (solution == "-1") {
    cout << -1;
    return 0;
  }


  cout << solution.size() << std::endl;
  for (char direction : solution) {
    switch (direction) {
      case 'L':std::cout << "R ";
        break;
      case 'U':std::cout << "D ";
        break;
      case 'R':std::cout << "L ";
        break;
      case 'D':std::cout << "U ";
        break;
    }
  }

  return 0;
}