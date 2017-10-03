/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#ifndef LIST_H
#define LIST_H

#include <list>

using namespace std;
class List : public DataStructure { //override Datastructure class
  private:
    // lists
    list<string> textList;
    list<string> dictList;
  public:
    // add file to data structure (with flag)
    bool add(string fileName, bool text) {
      string line;
      ifstream file(fileName); //open file
      if (file.is_open()) { //check if open
        while (getline(file, line)) { //file line loop
          if (text) //flag check
            textList.push_front(line); //store into text list
          else
            dictList.push_front(line); //store into dictionary list
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
      for (auto i : textList) { //text list loop
        tokenizer tok{i, SEP}; //tokenize line
        for (tokenizer::iterator t = tok.begin(); t != tok.end(); ++t) { //word loop
          for (auto j : dictList) { //dictionary list loop
            if (j == *t) { //already in map, increment
              if (map.find(*t) != map.end()) {
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
          }
        }
      }
      return map; //return counted words
    }

    // print structure (with flag)
    void print(bool text) {
      if (text) //flag check
        for (auto v : textList)
          cout << v << endl;
      else
        for (auto v : dictList)
          cout << v << endl;
    }
};

#endif
