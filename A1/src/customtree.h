/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#ifndef CT_H
#define CT_H

#include "bst.h"

using namespace std;
class CustomTree : public DataStructure { //override Datastructure class
  private:
    // binary search trees
    BST textTree;
    BST dictTree;
  public:
    // add file to data structure (with flag)
    bool add(string fileName, bool text) {
      string line;
      ifstream file(fileName); //open file
      if (file.is_open()) { //check if open
        while (getline(file, line)) { //loop through file
          if (text) //flag check
            textTree.add(line); //store into text tree
          else
            dictTree.add(line); //store into dictionary tree
          if (debug) //print process
            cout << "adding to list: " << line << endl;
        }
        file.close(); //close file
        return true; //success exit
      }
      else
        return false; //fail exit
    }

    // structure search & store into map (incomplete)
    map<string, int> search() {
      map<string, int> map;

      return map;
    }

    // print structure (with flag)
    void print(bool text) {
      if (text) //flag check
        textTree.print();
      else
        dictTree.print();
    return;
    }
};

#endif
