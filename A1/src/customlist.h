/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#ifndef CL_H
#define CL_H

#include "linkedlist.h"

using namespace std;
class CustomList : public DataStructure { //override Datastructure class
  private:
    // linked lists
    LinkedList textList;
    LinkedList dictList;
  public:
    // add file to data structure (with flag)
    bool add(string fileName, bool text) {
      string line;
      ifstream file(fileName); //open file
      if (file.is_open()) { //check if open
        while (getline(file, line)) { //file line loop
          if (text) //flag check
            textList.add(line); //store into text list
          else
            dictList.add(line); //store into dictionary list
          if (debug) //print process
            cout << "adding to list: " << line << endl;
        }
        file.close(); //close file
        return true; //success exit
      }
      else
        return false; //fail exit
    }

    // structure search & store into map
    map<string, int> search() {
      map<string, int> map; //word counter
      // get list heads
      LinkedList::Node *textNode = textList.getHead();
      LinkedList::Node *dictNode = dictList.getHead();
      while (textNode != nullptr) { //text list loop
        string textLine = textNode->getData(); //store node data
        tokenizer tok{textLine, SEP}; //tokenize line
        for (tokenizer::iterator t = tok.begin(); t != tok.end(); ++t) { //word loop
          while (dictNode != nullptr) { //dictionary list loop
            string dictLine = dictNode->getData(); //store node data
            if (dictNode->getData() == *t) { //word comparison
              if (map.find(*t) != map.end()) { //already in map, increment
                map[*t]++;
                if (debug) //print process
                  cout << "counting: " << *t << " [" << map[*t] << "]" << endl;
              }
              else { //put in new element
                map.insert(pair<string,int>(*t, 1));
                if (debug) //print process
                  cout << "adding: " << *t << endl;
              }
            }
            else { //put in empty element
              map.insert(pair<string,int>(*t, 0));
              if (debug) //print process
                cout << "adding: " << *t << endl;
            }
            dictNode = dictNode->getNext(); //move to next node
          }
          dictNode = dictList.getHead(); //go back to start
        }
        textNode = textNode->getNext(); //move to next node
      }
      return map; //return counted words
    }

    // print structure (with flag)
    void print(bool text) {
      if (text) //flag check
        textList.print();
      else
        dictList.print();
    }
};

#endif
