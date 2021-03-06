/**
 * @file Tree.h
 * @author  Daniel Terranova <daniel.terranova@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The Tree class represents a general tree structure.
 */

#ifndef TREE_H
#define TREE_H

#include <list>
#include <string>

class Tree
{
    /** @struct Node
     *  @brief This structure represents a node which is the elements of a tree.
     *  Each node have a list of child nodes and only one parent.
     *
     *   @var Node::value The actual element being stored in this node.
     *   @var Node::children A list of pointers to this node's child nodes.
     *   @var Node::parent A pointers to this node's parent.
     */
    struct Node
    {
        /** @brief Is the value of this node,
         * the actual element being stored in this node
         */
        std::string value;
        /** @brief The children nodes of this node **/
        std::list<Node*> children;
        /** @brief The parent node of this node **/
        Node* parent;

        /**
         * Constructor of a node.
         *
         * @param x [in] The node value or default
         * @param p [in] The parent of the node. If null then the node will have no parent, and
         * will point to itself
         *
         */
        Node(std::string = std::string(), Node* = 0);
    };
    /** @brief List of pointers to all the Node objects in pre order */
    std::list<Node*> nodes;
public:
    class Iterator;
    class NodeIterator;
    Tree();

    /**
    * @brief Copy constructor. Copy the entire tree from the given argument <code>tree</code> into this tree
    * @param tree The tree to copy
    */
    Tree(const Tree& tree);

    /**
     * @brief Constructor of a tree with one element
     *
     * @param x The node value
     */
    Tree(const std::string& x);

    /**
      * @brief Constructor. Add the list of <code>Tree</code> as the children of <code>x</code>
      * into this tree
      *
      * @param x The value to set the root node
      * @param list A List of children to be added to the node of the value <code>x</code>
      */
    Tree(const std::string&, const std::list<Tree*>& list);
    Tree(const std::string&, const std::initializer_list<std::string>& list);

    ~Tree();
    Tree& operator=(const Tree&);
    bool operator==(const Tree&) const;
    bool operator!=(const Tree&) const;
    void clear();
    bool empty() const;
    size_t size() const noexcept;
    int leaves() const;
    int height() const;
    int level(Iterator it) const;
    int width(int);
    size_t width();
    void print();
    std::string& root() const;
    /**
     *  @brief Returns a read iterator that points to the first element in the
     *  Tree.  Iteration is done in pre-order node element order.
     *
     *  @return a iterator to this Tree
     */
    Iterator begin();

    /**
     *  Returns a read iterator that points one past the last
     *  element in the Tree. Iteration is done in pre-order element order.
     *  @return a iterator to this Tree
     */
    Iterator end();
    static bool isRoot(Iterator it);
    /**!
      * Returns true if the iterator points to
      * node that have no children.
      */
    static bool isLeaf(Iterator it);
    static bool isOldestChild(Iterator it);
    static bool isYoungestChild(Iterator it);
    static Iterator youngestChild(Iterator it);
    static Iterator parent (Iterator it);
    static int numChildren(Iterator it);

    // Pre-Order traversal
    class Iterator
    {
        Tree* tree;
        std::list<Node*>::iterator lit;
    public:
        Iterator();
        Iterator(const Iterator&);
        Iterator(Tree*, Node* = 0);
        Iterator(Tree*, std::list<Node*>::iterator it);
        void operator=(const Iterator& it);
        bool operator==(const Iterator& it) const;
        bool operator!=(const Iterator& it);
        Iterator& operator++();  /** prefix operator **/
        Iterator  operator++(int); /** postfix increment **/
        std::string& operator*() const {
            return (*lit)->value;
        }
        bool operator!();
        friend class Tree;
    };
protected:
    int internal_height(Node* p) const;
    int internal_leaves(Node* p) const;
    int internal_level(Node* p, Iterator it) const;
    /**
      * @brief Recursive function to clone a subtree.
      *
      * @param src_node [in] The root node to copy
      * @param nodes [in] the nodes of this tree
      * @param parent [in] the parent of p
      */
    Node* tree_clone(const Node* src_node, std::list<Node*>& nodes, Node* parent);
    std::list<Node*> level(int n);
    std::list<Node*>::iterator litn(Node*);
    std::list<Node*>::iterator litp(Node*);
    std::list<Node*>::iterator nextSibling(std::list<Node*>::iterator);
    void print(int);
};


#endif
