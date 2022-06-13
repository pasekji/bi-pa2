#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

struct Node
{
    public:
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int val)
{
    Node* node = new Node;
    node->data = val;
    node->left = node->right = nullptr;

    return node;
}

Node* fillNode(Node & fill, char key);

Node* buildTree(int n)
{
    int val = n;
    Node* root = newNode(val);
    return nullptr;
}

int main()
{
  int n1 = 0;
  Node* root = buildTree(n1);


}
