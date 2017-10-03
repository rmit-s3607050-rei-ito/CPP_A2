/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
  Note: Influenced by 'tree.h' example
*/

#include "bst.h"

using namespace std;

string BST::Node::getData(void) {
  return data; //get word
}

void BST::Node::add(string item) {
  if (item < data) { //traverse left
    if (left)
      return left->add(item); //move to left
    else
      left = make_unique<BST::Node>(item); //add new item to left
  }
  else if (item > data) { //traverse right
    if (right)
      return right->add(item); //move to right
    else
      right = make_unique<BST::Node>(item); //add new item to right
  }
  else //already in tree, add to instance count
    count++;
}

void BST::Node::print(void) {
  if (left) //trverse left (!null)
    left->print();
  cout << data << endl; //print word
  if (right) //traverse right (!null)
    right->print();
}

BST::Node *BST::getRoot(void) {
  return root.get();
}

void BST::add(string item) {
  if (root) //start add at root
    return root->add(item);

  root = make_unique<BST::Node>(item); //root empty, add new item as root
}

void BST::print(void) {
  root->print(); //start print at root
}
