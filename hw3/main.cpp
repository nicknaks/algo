//Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
//Вывести их разницу. Разница может быть отрицательна.
#include <iostream>
#include <stack>
#include <queue>

using std::stack;
using std::queue;

template<typename T>
class Treap {
 public:
  Treap() : root(nullptr) {}
  Treap(const Treap &) = delete;
  Treap &operator=(const Treap &) = delete;

  ~Treap() {
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

  void Add(const T &key, int pk) {
    if (root == nullptr) {
      root = new Node(key, pk);
      return;
    }

    Node *current = root;
    Node *prev = root;

    while (current != nullptr) {
      if (current->priorityKey < pk) {
        break;
      }

      prev = current;

      if (key >= prev->key) {
        current = prev->right;
      } else {
        current = prev->left;
      }
    }

    Node* addNode = new Node(key, pk);

    split(current, key, addNode->left, addNode->right);

    if (current == root) {
      root = addNode;
      return;
    }

    if (key >= prev->key) {
      prev->right = addNode;
      return;
    }

    prev->left = addNode;
  }

  int MaxWidth() {
    if (root == nullptr) {
      return 0;
    }

    int maxWide = 0, currentWide = 0;

    queue<Node *> elements;
    elements.push(root);

    while (!elements.empty()) {
      currentWide = elements.size();
      
      if (currentWide > maxWide) {
        maxWide = currentWide;
      }

      for (int i = 0; i < currentWide; ++i) {
        Node *node = elements.front();
        elements.pop();

        if (node->left != nullptr) {
          elements.push(node->left);
        }

        if (node->right != nullptr) {
          elements.push(node->right);
        }
      }
    }

    return maxWide;
  }

 private:
  struct Node {
    T key;
    int priorityKey;
    Node *right;
    Node *left;
    Node(const T &_key, int _pk) : left(nullptr), right(nullptr), key(_key), priorityKey(_pk) {}
  };

  void split(Node *current, const T &key, Node *&leftTree, Node *&rightTree) {
    if (current == nullptr) {
      leftTree = nullptr;
      rightTree = nullptr;
    } else if (current->key <= key) {
      split(current->right, key, current->right, rightTree);
      leftTree = current;
    } else {
      split(current->left, key, leftTree, current->left);
      rightTree = current;
    }
  }

  Node *root;
};

template <typename T>
class BinTree {
 public:
  BinTree(): root(nullptr) {}
  BinTree(const BinTree&) = delete;
  BinTree& operator = (const BinTree&) = delete;

  ~BinTree() {
    if (root == nullptr) {
      return;
    }

    queue<Node*> elements;
    elements.push(root);

    while (!elements.empty()) {
      Node* node = elements.front();
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

  void Add(const T& key) {
    if (root == nullptr) {
      root = new Node(key);
      return;
    }

    Node* current = root;
    Node* prev = root;

    while(current != nullptr){
      prev = current;
      if (key >= prev->key) {
        current = prev->right;
      } else {
        current = prev->left;
      }
    }

    current = new Node(key);
    if (key >= prev->key) {
      prev->right = current;
      return;
    }

    prev->left = current;
  }

  int MaxWidth() {
    if (root == nullptr) {
      return 0;
    }

    int maxWide = 0, currentWide = 0;

    queue<Node *> elements;
    elements.push(root);

    while (!elements.empty()) {
      currentWide = elements.size();

      if (currentWide > maxWide) {
        maxWide = currentWide;
      }

      for (int i = 0; i < currentWide; ++i) {
        Node *node = elements.front();
        elements.pop();

        if (node->left != nullptr) {
          elements.push(node->left);
        }

        if (node->right != nullptr) {
          elements.push(node->right);
        }
      }
    }

    return maxWide;
  }
 private:
  struct Node{
    T key;
    Node* right;
    Node* left;
    explicit Node(const T& _key) : left(nullptr), right(nullptr), key(_key) {}
  };

  Node* root;
};

int main() {
  int n;
  std::cin >> n;

  Treap<int> treap;
  BinTree<int> binTree;

  for (int i = 0; i < n; ++i) {
    int key, pk;
    std::cin >> key >> pk;
    treap.Add(key, pk);
    binTree.Add(key);
  }

  std::cout << treap.MaxWidth() - binTree.MaxWidth();

  return 0;
}
