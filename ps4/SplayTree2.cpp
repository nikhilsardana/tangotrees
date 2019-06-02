#include "SplayTree.h"
#include "global.h"

using namespace std;

int numops;
SplayTree::SplayTree(size_t nElems) {
  root = treeFor(0, nElems);
  numops  = 0;
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
 * Determines whether the specified key is present in the splay tree.
 */

bool SplayTree::contains(size_t i) {
  /* TODO: Implement the full (not simplified) version of top-down splaying
   * described in Sleator and Tarjan's paper.
   */
	Node* l = nullptr;
	Node* r = nullptr;
	Node* t = root;
	Node n;
	n.left = nullptr;
	n.right = nullptr;
	l = &n;
	r = &n;
	bool found = false;
	while(1) {
		if(t == nullptr) {
			return false;
		}
		if(i == t->key) {
			found = true;
			break;
		} else if(i < t->key) {
			if(t->left == nullptr) {
				break;
			}
			if(i == (t->left)->key) {
				//link right
				r->left = t;
				r = t;
				t = t->left;
				numops += 1;
			} else if(i < (t->left)->key) {
				//rotate right
				Node* temp2 = t;
				t = t->left;
				temp2->left = t->right;
				t->right = temp2;
				//link right
				r->left = t;
				r = t;
				t = t->left;
				numops += 2;
			} else if(i > (t->left)->key) {
				//link right
				r->left = t;
				r = t;
				t = t->left;
				//link left
				l->right = t;
				l = t;
				t = t->right;
				numops += 1;
			}
		} else if (i > t->key) {
			if(t->right == nullptr) {
				break;
			}
			if ( i == (t->right)->key) {
				//link left
				l->right = t;
				l = t;
				t = t->right;
				numops += 1;
			} else if (i > (t->right)->key) {
				//rotate left
				Node* temp2 = t;
				t = temp2->right;
				temp2->right = t->left;
				t->left = temp2;
				//link left
				l->right = t;
				l = t;
				t = t->right;
				numops += 2;
			} else if (i < (t->right)->key) {
				//link left
				l->right = t;
				l = t;
				t = t->right;
				//link right
				r->left = t;
				r = t;
				t = t->left;
				numops += 1;
			}
		}
	}
	r->left = t->right;
	l->right = t->left;
	t->left = n.right;
	t->right = n.left;
	root = t;	
	numops += 1;
	if(found) {
		return true;
	}
  	return false;
}
