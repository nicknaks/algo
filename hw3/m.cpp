#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

template <class _T>
class BinaryTree;

template<class _T>
struct BinaryTreeNode
{
 public:
  typedef _T value_t;
  friend class BinaryTree<value_t>;

  BinaryTreeNode(value_t key):
      key(key)
  {
    left = NULL;
    right = NULL;
  }

  ~BinaryTreeNode()
  {
    if (left)
      delete left;
    if (right)
      delete right;
  }
  value_t key;
 private:
  BinaryTreeNode<value_t> *left;
  BinaryTreeNode<value_t> *right;
};

template <class _T>
class BinaryTree
{
 public:
  typedef _T value_t;

  BinaryTree()
  {
    root = NULL;
  }

  ~BinaryTree()
  {
    delete root;
  }

  void add(value_t key)
  {
    BinaryTreeNode<value_t> *nodeToAppend = new BinaryTreeNode<value_t>(key);
    if (!root)
    {
      root = nodeToAppend;
      return;
    }

    BinaryTreeNode<value_t> *current = root;
    BinaryTreeNode<value_t> *next = root;

    while (next)
    {
      current = next;
      if (key <= current->key)
        next = next->left;
      else next = next->right;
    }
    if (key <= current->key)
      current->left = nodeToAppend;
    else current->right = nodeToAppend;
  }

  int getMaxLayerWidth()
  {
    int maxLayerWidth = 0;
    std::queue<BinaryTreeNode<value_t> *> layer;
    layer.push(root);
    while (!layer.empty())
    {
      int currentLayerWidth = layer.size();
      if (currentLayerWidth > maxLayerWidth)
        maxLayerWidth = currentLayerWidth;
      for (int i = 0; i < currentLayerWidth; ++i)
      {
        BinaryTreeNode<value_t> *temp = layer.front();
        layer.pop();
        if (temp->left)
          layer.push(temp->left);
        if (temp->right)
          layer.push(temp->right);
      }
    }
    return maxLayerWidth;
  }

 private:
  BinaryTreeNode<value_t> *root;
};
//------------------------//------------------------//------------------------

template <class _T, class _P>
class Treap;

template <class _T, class _P>
struct TreapNode
{
 public:
  typedef _T value_t;
  typedef _P priority_t;

  friend class Treap<value_t, priority_t> ;//* Treap<value_t, priority_t>::merge(TreapNode<value_t, priority_t> *left, TreapNode<value_t, priority_t> *right);

  TreapNode(value_t key, priority_t priority):
      key(key),
      priority(priority)
  {
    left = NULL;
    right = NULL;
  }
  ~TreapNode()
  {
    if (left)
      delete left;
    if (right)
      delete right;
  }

  value_t key;
  priority_t priority;
 private:
  TreapNode<value_t, priority_t> *left;
  TreapNode<value_t, priority_t> *right;
};

template <class _T, class _P>
class Treap
{
 public:
  typedef _T value_t;
  typedef _P priority_t;

  Treap()
  {
    root = NULL;
  }

  ~Treap()
  {
    delete root;
  }

  void add(value_t key, priority_t priority)
  {
    TreapNode<value_t, priority_t> *nodeToAppend = new TreapNode<value_t, priority_t>(key, priority);

    if (!root)
    {
      root = nodeToAppend;
      return;
    }

    TreapNode<value_t, priority_t> *current = root;
    TreapNode<value_t, priority_t> *prev = root;

    while (current && current->priority >= priority)
    {
      prev = current;
      if (key <= current->key)
        current = current->left;
      else
        current = current->right;
    }

    split(current, key, nodeToAppend->left, nodeToAppend->right);

    if (current == root)
      root = nodeToAppend;
    else
    {
      if (key <= prev->key)
        prev->left = nodeToAppend;
      else
        prev->right = nodeToAppend;
    }
  }

  int getMaxLayerWidth()
  {
    int maxLayerWidth = 0;
    std::queue<TreapNode<value_t, priority_t> *> layer;
    layer.push(root);
    while (!layer.empty())
    {
      int currentLayerWidth = layer.size();
      if (currentLayerWidth > maxLayerWidth)
        maxLayerWidth = currentLayerWidth;
      for (int i = 0; i < currentLayerWidth; ++i)
      {
        TreapNode<value_t, priority_t> *temp = layer.front();
        layer.pop();
        if (temp->left)
          layer.push(temp->left);
        if (temp->right)
          layer.push(temp->right);
      }
    }
    return maxLayerWidth;
  }

 private:
  TreapNode<value_t, priority_t> *root;

  TreapNode<value_t, priority_t> *merge(TreapNode<value_t, priority_t> *left, TreapNode<value_t, priority_t> *right)
  {
    if (left == NULL || right == NULL)
      return (left == NULL) ? right : left;
    if (left->priority > right->priority)
    {
      left->right = merge(left->right, right);
      return left;
    }
    else
    {
      right->left = merge(left, right->left);
      return right;
    }
  }

  void split(TreapNode<value_t, priority_t> *current, value_t key, TreapNode<value_t, priority_t> *&left, TreapNode<value_t, priority_t> *&right)
  {
    if (current == NULL)
    {
      left = NULL;
      right = NULL;
    }
    else if (current->key <= key)
    {
      split(current->right, key, current->right, right);
      left = current;
    }
    else
    {
      split(current->left, key, left, current->left);
      right = current;
    }
  }
};
//------------------------//------------------------//------------------------

template <class _T>
int getMaxLayerWidth(_T *root)
{
  int maxLayerWidth = 0;
  std::queue<_T *> layer;
  layer.push(root);
  while (!layer.empty())
  {
    int currentLayerWidth = layer.size();
    if (currentLayerWidth > maxLayerWidth)
      maxLayerWidth = currentLayerWidth;
    for (int i = 0; i < currentLayerWidth; ++i)
    {
      _T *temp = layer.front();
      layer.pop();
      if (temp->left)
        layer.push(temp->left);
      if (temp->right)
        layer.push(temp->right);
    }
  }
  return maxLayerWidth;
}
//------------------------//------------------------//------------------------

int main()
{
  BinaryTree<int> BTree;
  Treap<int, int> CTree;
  size_t n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i)
  {
    int key, priority;
    std::cin >> key >> priority;
    BTree.add(key);
    CTree.add(key, priority);
  }

  std::cout << std::abs(CTree.getMaxLayerWidth() - BTree.getMaxLayerWidth()) << std::endl;
  return 0;
}