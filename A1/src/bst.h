/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
  Note: Influenced by 'tree.h' example
*/

#ifndef BST_H
#define BST_H

#include <memory>

#include "util.h"

class BST {
  public:
    // tree node class (public for use in 'customtree.h')
    class Node {
      private:
        std::string data; //word store
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int count; //instance count
      public:
        Node(std::string newData) : data(newData), left(nullptr),
          right(nullptr), count(1) {}
        std::string getData(void); //data getter
        void add(std::string); //add new (Node)
        void print(void); //print tree
        friend class BST;
    };
    BST(void) : root(nullptr) {}
    Node *getRoot(void); //root getter
    void add(std::string); //add new (BST)
    void print(void); //print tree
  private:
    std::unique_ptr<Node> root; //base node
};

#endif
