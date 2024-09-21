/**
 * NTHELEMSET
 */
#ifndef JUMPAKU_NTHELEMSET_HPP
#define JUMPAKU_NTHELEMSET_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

// A BST node
struct Node {
  int data;
  int size;
  Node *left, *right;
  Node(int x) {
    data = x;
    size = 1;
    left = right = nullptr;
  }
};

// Function to find k'th smallest element in BST
Node *kthSmallest(Node *root, int &k, int &count) {
  if (root == nullptr)
    return nullptr;

  Node *left = kthSmallest(root->left, k, count);
  if (left != nullptr)
    return left;

  count++;
  if (count == k)
    return root;

  return kthSmallest(root->right, k, count);
}

// Method to initialize count and call kthSmallest
Node *findKthSmallest(Node *root, int k) {
  int count = 0;
  return kthSmallest(root, k, count);
}

// Function to find k'th largest element in BST
Node *kthLargest(Node *root, int &k, int &count) {
  if (root == nullptr)
    return nullptr;

  Node *right = kthLargest(root->right, k, count);
  if (right != nullptr)
    return right;

  count++;
  if (count == k)
    return root;

  return kthLargest(root->left, k, count);
}

// Method to initialize count and call kthLargest
Node *findKthLargest(Node *root, int k) {
  int count = 0;
  return kthLargest(root, k, count);
}

// Recursive function to insert a key into BST
Node *insert(Node *root, int x) {
  if (root == nullptr) {
    return new Node(x);
  }
  if (x < root->data) {
    root->left = insert(root->left, x);
  } else if (x > root->data) {
    root->right = insert(root->right, x);
  }
  root->size++;
  return root;
}
vecl collect(Node *root) {
  vecl res;
  if (root == nullptr) {
    return res;
  }
  res.push_back(root->data);
  auto left = collect(root->left);
  auto right = collect(root->right);
  res.insert(res.end(), left.begin(), left.end());
  res.insert(res.end(), right.begin(), right.end());
  return res;
}

#endif
/* end of NTHELEMSET */