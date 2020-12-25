// 4.1 Солдаты
#include <iostream>
#include <queue>

using std::queue;

template<typename T>
class AVLTree {
 public:
  explicit AVLTree(bool (*isLess)(const T &, const T &) = isLessDefault) : root(nullptr), cmp(isLess) {}
  AVLTree(const AVLTree &) = delete;
  AVLTree &operator=(const AVLTree &) = delete;
  ~AVLTree() {
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

 public:
  int Add(const T &key) {
    int position = 0;
    add(root, key, position);
    return height(root) - position - 1;
  }
  void Delete(int position) {
    position = height(root) - position - 1;
    root = remove(root, position);
  }

 private:
  struct Node {
    T key;
    int height;
    Node *right;
    Node *left;
    explicit Node(const T &_key) : key(_key), right(nullptr), left(nullptr), height(1) {}
  };

  static bool isLessDefault(const T &l, const T &r) {
    return l > r;
  }

  bool (*cmp)(const T &, const T &);
  Node *root;

  int height(Node *node) const {
    if (node == nullptr) {
      return 0;
    }

    return node->height;
  }
  int bFactor(Node *node) const {
    return height(node->right) - height(node->left);
  }
  void fixHeight(Node *node) {
    node->height = height(node->right) + height(node->left) + 1;
  }

  Node *rotateRight(Node *node) {
    Node *nodeLeft = node->left;
    node->left = nodeLeft->right;
    nodeLeft->right = node;
    fixHeight(node);
    fixHeight(nodeLeft);
    return nodeLeft;
  }
  Node *rotateLeft(Node *node) {
    Node *nodeRight = node->right;
    node->right = nodeRight->left;
    nodeRight->left = node;
    fixHeight(node);
    fixHeight(nodeRight);
    return nodeRight;
  }

  Node *balance(Node *node) {
    fixHeight(node);

    if (bFactor(node) == 2) {
      if (bFactor(node->right) < 0) {
        node->right = rotateRight(node->right);
      }

      return rotateLeft(node);
    }

    if (bFactor(node) == -2) {
      if (bFactor(node->left) > 0) {
        node->left = rotateLeft(node->left);
      }

      return rotateRight(node);
    }

    return node;
  }

  void add(Node *&node, const T &key, int &position) {
    if (node == nullptr) {
      node = new Node(key);
      return;
    }

    if (key == node->key || cmp(key, node->key)) {
      position += height(node) - height(node->right);
      add(node->right, key, position);
    } else {
      add(node->left, key, position);
    }
    node = balance(node);
  }

  Node *findMin(Node *node) {
    if (node->left == nullptr) {
      return node;
    }

    return findMin(node->left);
  }

  Node *removeMin(Node *node) {
    if (node->left == nullptr) {
      return node->right;
    }

    node->left = removeMin(node->left);
    return balance(node);
  }

  Node *remove(Node *node, int &position) {
    if (node == nullptr) {
      return nullptr;
    }

    if (!cmp(position, height(node->left)) && position != height(node->left)) {
      node->left = remove(node->left, position);
    } else if (cmp(position, height(node->left) && position != height(node->left))) {
      position -= (height(node->left) + 1);
      node->right = remove(node->right, position);
    } else {
      Node *minParent = node;
      Node *min = node->right;

      while (min->left != nullptr) {
        minParent = min;
        min = min->left;
      }

      node->key = min->key;
      if (minParent->left == min) {
        minParent->left = min->right;
      } else {
        minParent->right = min->right;
      }

      delete min;
      return balance(node);
    }
    return balance(node);
  }
};

enum Command {
  ADDNODE = 1,
  DELNODE = 2
};

int main() {

  AVLTree<int> tree;

  int n = 0;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    int command = 0, value = 0;

    std::cin >> command >> value;

    if (command == ADDNODE) {
      std::cout << tree.Add(value) << std::endl;
    } else if (command == DELNODE) {
      tree.Delete(value);
    }
  }

  return 0;
}
