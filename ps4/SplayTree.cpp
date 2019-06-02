#include "SplayTree.h"
using namespace std;

SplayTree::SplayTree(size_t nElems) {
  root = treeFor(0, nElems);
}

/**
 * Constructs a perfectly balanced tree for the values in the range
 * [low, high).
 */
SplayTree::Node*
SplayTree::treeFor(size_t low, size_t high) {
  /* Base Case: The empty range is represented by an empty tree. */
  if (low == high) return nullptr;
  
  /* Otherwise, pull out the middle, then recursively construct trees for the
   * left and right ranges.
   */
  size_t mid = low + (high - low) / 2;
  return new Node {
    mid,
    treeFor(low, mid),
    treeFor(mid + 1, high)
  };
}

/**
 * Frees all memory used by this tree.
 */
SplayTree::~SplayTree() {
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
 * linkLeft
 * --------
 * Adds current node to left tree.
 * Moves right in search.
 */
void SplayTree::linkLeft(Node* &t, Node* &l) const {
  l->right = t;
  l = t;
  t = t->right;
}

/**
 * linkRight
 * --------
 * Adds current node to right tree.
 * Moves left in search.
 */
void SplayTree::linkRight(Node* &t, Node* &r) const {
  r->left = t;
  r = t;
  t = t->left;
}

/**
 * rotateLeft
 * ----------
 * Rotates node t left, around its right edge.
 * Sets t to be its right child.
 */
void SplayTree::rotateLeft(Node* &t) const {
  // assumed: t->right is not null
  Node* temprl = t->right->left;
  Node* tempr = t->right;
  t->right->left = t;
  t->right = temprl;
  t = tempr;
}

/**
 * rotateRight
 * -----------
 * Rotates node t right, around its left edge.
 * Sets t to be its left child.
 */
void SplayTree::rotateRight(Node* &t) const {
  // assumed: t->left is not null
  Node* templr = t->left->right;
  Node* templ = t->left;
  t->left->right = t;
  t->left = templr;
  t = templ;
}

/**
 * assemble
 * --------
 * Assembles left tree, right tree, and subtree from t, into a complete
 * node.
 *
 * super->left must store the root of the right search tree.
 * super->right must store the root of the left search tree.
 */
void SplayTree::assemble(Node* &t, Node* &l, Node* &r, Node* super) const {
  r->left = t->right;
  l->right = t->left;
  t->right = super->left;
  t->left = super->right;
  root = t;
}

/**
 * Determines whether the specified key is present in the splay tree.
 */
bool SplayTree::contains(size_t key) const {
  Node *t, *l, *r; // working tree t, left tree l, right tree r
  Node super {0, nullptr, nullptr}; // node to store roots of left and right tree (null node in T&S)

  // initialize nodes
  t = root; 
  l = r = &super;
  
  // faithful recreation of Tarjan and Sleator's pseudocode,
  // except it handles the absence of a key by breaking at correct moments.
  while (key != t->key) {
    if (key < t->key) {
      if (!t->left) break; // key not present
      if (key == t->left->key) {
        linkRight(t, r);
      } else if (key < t->left->key) {
        rotateRight(t);
        if (!t->left) break; // check again, in case rotation made t->left null
        linkRight(t, r);
      } else /* key > t->left->key) */ {
        linkRight(t, r);
        linkLeft(t, l);
      }
    } else /* key > t-> key */ {
      if (!t->right) break; // key not present
      if (key == t->right->key) {
        linkLeft(t,l);
      } else if (key > t->right->key) {
        rotateLeft(t);
        if (!t->right) break; // check again, in case rotation made t->right null
        linkLeft(t, l);
      } else /* key < t->right->key) */ {
        linkLeft(t, l);
        linkRight(t, r);
      }
    }
  }
  assemble(t, l, r, &super);

  // t is either the right node, or its in-order successor/predecessor
  return (t->key == key);
}
