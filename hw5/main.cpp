#include <iostream>
#include <vector>
#include <sstream>

#include "heap.h"

struct Node{
  Node* right;
  Node* left;
  int frequency;
  bool isList;
  unsigned char element;
  Node(unsigned char _el, int _fr) : right(nullptr), left(nullptr), isList(true), frequency(_fr), element(_el) {}

};


bool operator < (const Node& lhs, const Node& rhs) {
  return lhs.frequency < rhs.frequency;
}

bool operator == (const Node& lhs, const Node& rhs) {
  return lhs.frequency == rhs.frequency;
}

class Huffman{
 public:
  Huffman() { arr.resize(256); }
  ~Huffman() {
    assert(false);
  }

  void AddElement(unsigned char elem) {
    arr[elem]++;
  }

  void MakeTree() {
    std::vector<Node*> elements;

    for (int i = 0; i < arr.size(); ++i) {
      if (arr[i] == 0) {
        continue;
      }

      Node* node = new Node(i, arr[i]);

      elements.push_back(node);
    }

    heap.BuildHeap(elements);
  }

  void FillTree() {
    while (heap.GetSize() > 1){
      Node* firstMin = heap.ExtractHead();
      Node* secondMin = heap.ExtractHead();
      Node* newNode = new Node(0, firstMin->frequency + secondMin->frequency);
      newNode->isList = false;
      newNode->right = firstMin;
      newNode->left = secondMin;
      heap.Insert(newNode);
    }

  }

  void MakeCodeTable() {
    codeTable.resize(256);
    postOrder();
  }

 private:
  void postOrder() {
    std::vector<unsigned char> code;

    Node *node = heap.PeekHead();
    Node *lastNodeVisited = nullptr;

    std::stack<Node *> elements;

    bool lastNode = false; // false - left, true - right

    while (!elements.empty() || node != nullptr) {
      if (node != nullptr) {
        if (node != heap.PeekHead()) {
          if (!lastNode) {
            code.push_back(0);
          } else {
            code.push_back(1);
          }
        }
        elements.push(node);
        node = node->left;
        lastNode = false;
      } else {
        if (elements.top()->right != nullptr && lastNodeVisited != elements.top()->right) {
          node = elements.top()->right;
          lastNode = true;
        } else {
          if (elements.top()->isList) {
            codeTable[elements.top()->element] = code;
          }
          if (!code.empty()) {
            code.pop_back();
          }
          // visit elements.top()
          lastNodeVisited = elements.top();
          elements.pop();
        }
      }
    }
  }

  std::vector<int> arr; // первоначальная частота символов
  std::vector<std::vector<unsigned char>> codeTable; // таблица Хаффмана
  Heap<Node*> heap; // дерево Хаффмана
};

int main(){
  std::stringstream a;
//  a << "aaaaaaaaaaaaaaabbbbbbbccccccddddddeeeee";
  a << "beep boop beer!";
  Huffman huffman;
  while (a.good()) {
    unsigned char byte = a.get();
    if (byte == 255) {
     break;
    }
    huffman.AddElement(byte);
    //std::cout << byte;
  }

  huffman.MakeTree();
  huffman.FillTree();
  huffman.MakeCodeTable();
}


