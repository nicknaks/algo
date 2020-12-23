// 2_1. Выведите элементы в порядке in-order (слева направо).

#include <iostream>
#include <stack>
#include <queue>

using std::stack;
using std::queue;

template<class T>
bool isLessDefault(const T &l, const T &r) {
  return l >= r;
}

template<typename T>
class BinTree {
 public:
  BinTree(bool (*isLess)(const T &, const T &) = isLessDefault) : root(nullptr), isLess(isLess) {}
  BinTree(const BinTree &) = delete;
  BinTree &operator=(const BinTree &) = delete;
  ~BinTree();

  void Add(const T &key);
  void InOrder(void visit(const T &));
 private:
  struct Node {
    T key;
    Node *right;
    Node *left;
    explicit Node(const T &_key) : left(nullptr), right(nullptr), key(_key) {}
  };

  bool (*isLess)(const T &, const T &);

  Node *root;
};

template<typename T>
BinTree<T>::~BinTree() {
  if (root == nullptr) {
    return;
  }

  queue<Node *> elements;
  elements.push(root);
  while (!elements.empty()) {
    Node *node = elements.front();
    elements.pop();
    if (node->right != nullptr) {
      elements.push(node->right);
    }
    if (node->left != nullptr) {
      elements.push(node->left);
    }
    delete node;
  }
}

template<typename T>
void BinTree<T>::Add(const T &key) {
  if (root == nullptr) {
    root = new Node(key);
    return;
  }

  Node *current = root;
  Node *prev = root;

  while (current != nullptr) {
    prev = current;
    if (isLess(key, prev->key))  {
      current = prev->right;
    } else {
      current = prev->left;
    }
  }

  current = new Node(key);
  if (isLess(key, prev->key)) {
    prev->right = current;
    return;
  }

  prev->left = current;
}

template<typename T>
void BinTree<T>::InOrder(void visit(const T &)) {
  stack<Node *> elements;
  Node *node = root;

  while (!elements.empty() || node != nullptr) {
    if (node == nullptr) {
      node = elements.top();
      elements.pop();
      visit(node->key);
      node = node->right;
    } else {
      elements.push(node);
      node = node->left;
    }
  }
}

int main() {
  int n;
  std::cin >> n;

  BinTree<int> bin_tree;

  for (int i = 0; i < n; ++i) {
    int value;
    std::cin >> value;
    bin_tree.Add(value);
  }

  bin_tree.InOrder([](const int &key) {
    std::cout << key << " ";
  });

  return 0;
}
