#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <queue>
#include "Tree.h"

/*!
 * Constructor of a node.
 *
 * @param x [in] The value of x
 * @param p [in] The parent of the node. If null then the node will have no parent
 *
 * @return
 */
Tree::Node::Node(std::string x, Node* p): value(x), parent(p) {
  if (!parent)
    parent = this;
}

// -- Tree definitions (implementations)
Tree::Tree() {
}

Tree::Tree(const std::string& x) {
  nodes.push_back(new Node(x));
}

/*!
 * Copy constructor. Cpy the entire tree into this tree
 * @param tree [in] The tree to copy
 */
Tree::Tree(const Tree& tree)
{
  if (tree.nodes.empty())
    return;
  tree_clone(tree.nodes.front(), nodes, 0);
}

/*!
 * Constructor. Add the list as the children of x
 * @param x [in] The value to set the node
 * @param list [in] List of children to be added to x
 */
Tree::Tree(const std::string& x, const std::list<Tree*>& list)
{
  /// Create the root node
  Node *root = new Node(x);
  nodes.push_back(root);

  for (const auto tree: list) {
      if (!(tree->nodes).empty()) {
          Tree* tp = new Tree(*tree);
          Node* p = tp->nodes.front(); /// should point to root
          root->children.push_back(p);
          p->parent = root;
          std::list<Node*>::iterator lit1 = tp->nodes.begin();
          std::list<Node*>::iterator lit2 = tp->nodes.end();
          std::list<Node*>::iterator lit3 = nodes.end();
          nodes.insert(lit3, lit1, lit2);   //append *tp's nodes
        }
    }
}

Tree::Tree (const std::string& x, const std::initializer_list<std::string>& list)
{
  /// Create the root node
  Node *root = new Node(x);
  nodes.push_back(root);

  for (const auto node: list) {
      Node *child = new Node(node, root);
      root->children.push_back(child);
      nodes.push_back (child);   //append *tp's nodes
    }

}


/// p copy to (dest), nodes - copy from (src)
/// At the first call parent = 0, p represent the root node of the tree
/// that is copied, nodes is passed for each recursion so we could
/// add each sub node creaated from p. P comes from the tree we wish to
/// cpy and nodes is intended to be filled ( from p ).
Tree::Node* Tree::tree_clone(Node* p, std::list<Node*>& nodes, Node* parent)
{
  Node* cp = new Node(p->value, parent);
  nodes.push_back(cp);

  std::list<Node*>& l = p->children;
  std::list<Node*>& cl = cp->children;

  /// Iterate over all children of the node that needs to cpy and clone each
  /// subtree and make cp the new parent
  for (auto child: l)
    cl.push_back( tree_clone(child, nodes, cp));

  return cp;
}

// Destructor    
Tree::~Tree()
{
  for (auto node: nodes)
    delete node;
}

Tree& Tree::operator=(const Tree& t)
{
  clear();
  Tree* p = new Tree(t); // use cpy constructor
  nodes = p->nodes;
  return *this;
}

bool Tree::operator==(const Tree& t) const {
  if (nodes.size() != t.nodes.size())
    return false;

  std::list<Node*>::const_iterator tlit = t.nodes.begin();
  for (std::list<Node*>::const_iterator lit = nodes.begin(); lit!= nodes.end(); lit++, tlit++ ) {
      if ( (*lit)->value != (*tlit)->value )
        return false;
    }
  return true;
}

bool Tree::operator!=(const Tree& t) const {
  return !(*this == t);
}

void Tree::clear() {
  for (auto node : nodes) {
      delete node;
    }
  nodes.clear();
}

bool Tree::empty() const {
  return nodes.empty();
}

size_t Tree::size() const noexcept {
  return (unsigned int) nodes.size();
}

int Tree::leaves() const {
  return internal_leaves(nodes.front());
}

int Tree::internal_leaves(Node* p) const {
  if (!p)
    return 0;

  std::list<Node*> plist = p->children;

  if (plist.empty())
    return 1; //*p is a leaf

  int n0 = 0;
  for (auto node : plist) {
      n0 += internal_leaves(node);
    }
  return n0;
}

int Tree::height() const {
  return internal_height(nodes.front());
}

int Tree::internal_height(Node* p) const {
  std::list<Node*> plist = p->children;

  if (plist.empty())
    return 0;

  int h0 = 0;

  for (auto node : plist) {
      int h1 = internal_height(node);
      if (h1 > h0)
        h0 = h1;
    }
  return h0+1;
}

int Tree::level(Iterator it) const {
  return internal_level(nodes.front(), it);
}

int Tree::internal_level(Node* p, Iterator it) const {
  if (!p)
    return -1; // the empty tree has height -1
  if (p->value == *it)
    return 0;

  for (auto node: p->children) {
      int lc = internal_level (node, it);
      if (lc > -1)
        return lc+1;
    }
  return -1;
}

void Tree::print()  {
  int h = height();
  for ( int level=0; level<=h; level++)
    print(level);
  std::cout << "\n";
}

void Tree::print(int n)  {
  std::list<Node*> level_nodes = level(n);
  for (auto node: level_nodes)
    std::cout << (node)->value << " ";
}

// protected members
std::list<Tree::Node*> Tree::level(int n) {
  std::list<Node*> listn;

  if (empty())
    return listn;

  std::queue<std::list<Node*>*> q;
  Node* root = *(nodes.begin());

  if (n == 0)
    return std::list<Tree::Node*>(1,root);

  q.push(&(root->children));
  while (!q.empty()) {
      std::list<Node*>* p = q.front();
      std::list<Node*>& list = *p;

      for (auto lit : list) {
          Iterator it (this, lit);
          if (level(it) == n)
            listn.push_back(lit);
          q.push(&lit->children);
        }
      q.pop();
    }
  return listn;
}


int Tree::width(int)
{
  return 0;
}

size_t Tree::width()
{
  size_t w = 1;
  if (nodes.empty())
    return 0;
  for (int k = 0; k<= height(); k++) {
      size_t w1 = level(k).size();
      if (w1 > w) w = w1;
    }
  return w;
}

std::string& Tree::root() const {
  // TODO: Implement
  return nodes.front()->value;
}

Tree::Iterator::Iterator() {
}

Tree::Iterator::Iterator(const Iterator& it) :
    tree(it.tree), lit(it.lit) {
}

Tree::Iterator::Iterator(Tree* tree, Node* p) : tree(tree) {
  std::list<Node*> nodes = tree->nodes;
  lit = find(nodes.begin(), nodes.end(), p);
}

Tree::Iterator::Iterator(Tree* tree, std::list<Node*>::iterator it) :
    tree(tree), lit(it) {
}

void Tree::Iterator::operator=(const Tree::Iterator &it) {
  tree = it.tree;
  lit = it.lit;
}

bool Tree::Iterator::operator==(const Tree::Iterator &it) const {
  return tree == it.tree && lit == it.lit;
}

bool Tree::Iterator::operator!=(const Tree::Iterator &it) {
  return tree != it.tree || lit != it.lit;
}

// prefix
Tree::Iterator& Tree::Iterator::operator++()
{
  ++lit;
  return *this;
}

Tree::Iterator Tree::Iterator::operator++(int)
{
  Tree::Iterator it(*this);
  ++(*this);
  return it;
}

bool Tree::Iterator::operator!()
{
  return lit == tree->nodes.end();
}

Tree::Iterator Tree::begin() {
  return Tree::Iterator(this, nodes.begin());
}

Tree::Iterator Tree::end() {
  return Iterator(this, nodes.end());
}

bool Tree::isRoot(Tree::Iterator it)
{
  return it.lit == (it.tree->nodes).begin();
}
bool Tree::isLeaf (Tree::Iterator it)
{
  return (*it.lit)->children.empty ();
}
