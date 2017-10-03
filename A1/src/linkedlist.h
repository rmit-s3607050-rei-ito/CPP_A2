/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
  Note: Influenced by 'intlist.h' example
*/

#ifndef LL_H
#define LL_H

#include <memory>

#include "util.h"

class LinkedList {
  public:
    // list node class (public for use in 'customlist.h')
    class Node {
      private:
        std::string data; //word store
        std::unique_ptr<Node> next;
      public:
        Node(std::string newData) : data(newData), next(nullptr) {}
        void setNext(std::unique_ptr<Node> &&newNext); //next setter
        Node *getNext(void); //next getter
        std::string getData(void); //data getter
        std::unique_ptr<Node> &getNextPtr(void); //nect ptr getter
        friend class LinkedList;
    };
    LinkedList(void) : head(nullptr), size(0) {}
    Node *getHead(void); //head getter
    void add(std::string); //add new
    void print(void); //print list
  private:
    std::unique_ptr<Node> head; //start node
    int size; //list size
};

#endif
