#include "PerfectlyBalancedTree.h"
#include "global.h"
using namespace std;


int numalts;
PerfectlyBalancedTree::PerfectlyBalancedTree(size_t nElems) {
  root = treeFor(0, nElems);
}

/**
 * Constructs a perfectly balanced tree for the values in the range
 * [low, high).
 */
PerfectlyBalancedTree::Node*
PerfectlyBalancedTree::treeFor(size_t low, size_t high) {
  /* Base Case: The empty range is represented by an empty tree. */
  if (low == high) return nullptr;
  
  /* Otherwise, pull out the middle, then recursively construct trees for the
   * left and right ranges.
   */
  size_t mid = low + (high - low) / 2;
  return new Node {
    mid,
    NULL,
    treeFor(low, mid),
    treeFor(mid + 1, high)
  };
}

/**
 * Frees all memory used by this tree.
 */
PerfectlyBalancedTree::~PerfectlyBalancedTree() {
  /* This is the same algorithm we used in PS3. It takes time O(n) and uses
   * only O(1) auxiliary memory.
   */
  while (root != nullptr) {
    /* If the root has no left subtree, just delete the root. */
    if (root->left == nullptr) {
      Node* next = root->right;
      delete root;
      root = next;
    }
    /* Otherwise, the root has a left subtree. Do a right rotation to move
     * that child to the left.
     */
    else {
      Node* child = root->left;
      root->left = child->right;
      child->right = root;
      root = child;
    }
  }
}

/**
 * Determines whether the specified key is present in the perfectly-balanced
 * tree.
 */
bool PerfectlyBalancedTree::contains(size_t key) const {
  Node* curr = root;
  while (true) {
    if (curr == nullptr)  return false;
    if (curr->key == key) return true;
    
    string prev_pref = curr->pref;

    if (key < curr->key) {
      curr->pref = "L";
      if (prev_pref == "R") {
        numalts++;
      }
      curr = curr->left;
    } else {
      curr->pref = "R";
      if (prev_pref == "L") {
        numalts++;
      }
      curr = curr->right;
    }
    
    curr = (key < curr->key? curr->left : curr->right);
  }
}
