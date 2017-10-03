/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
  Note: Influenced by 'intlist.h' example
*/

#include "linkedlist.h"

using namespace std;

void LinkedList::Node::setNext(unique_ptr<LinkedList::Node> &&newNext) {
  next = move(newNext); //move to to new position
}

LinkedList::Node *LinkedList::Node::getNext(void) {
  return next.get(); //get next's node
}

unique_ptr<LinkedList::Node> &LinkedList::Node::getNextPtr(void) {
  return next; //get next's pointer
}

string LinkedList::Node::getData(void) {
  return data; //get word
}

LinkedList::Node *LinkedList::getHead(void) {
  return head.get(); //get list head
}

void LinkedList::add(string data) {
  Node *current;
  Node *prev = nullptr;
  unique_ptr<LinkedList::Node> newNode = make_unique<LinkedList::Node>(data);
  if(head == nullptr) { //empty head
     // put new node as head, increase size & end
    head = make_unique<Node>(data);
    ++size;
    return;
  }
  current = head.get(); //get the pointer held by the unique_ptr
  if(!prev) { //previous node empty (first element)
    // put new node as head, move head to next
    newNode->setNext(move(head));
    head = move(newNode);
  }
  else if(!current) //current node empty
    prev->setNext(move(newNode));
  else { //next node empty
    newNode->setNext(move(prev->getNextPtr()));
    prev->setNext(move(newNode));
  }
  ++size; //increase size
}

void LinkedList::print(void) {
    LinkedList::Node *current;
    for(current = head.get(); current; current = current->getNext()) { //list loop
        cout << current->data << endl; //print word
    }
}
