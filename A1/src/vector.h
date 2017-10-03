/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

using namespace std;
class Vector : public DataStructure { //override DataStructure class
  private:
    // vectors
    vector<string> textVec;
    vector<string> dictVec;
  public:
    // add file to data structure (with flag)
    bool add(string fileName, bool text) {
      string line;
      ifstream file(fileName); //open file
      if (file.is_open()) { //check if open
        while (getline(file, line)) { //file line loop
          if (text) //flag check
            textVec.push_back(line); //store into text vector
          else
            dictVec.push_back(line); //store into dictionary vector
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
      map<string, int> map; //word count
      for (auto i : textVec) { //text vector loop
        tokenizer tok{i, SEP}; //tokenize line
        for (tokenizer::iterator t = tok.begin(); t != tok.end(); ++t) { //word loop
          for (auto j : dictVec) { //dictionary vector loop
            if (j == *t) { //word comparison
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
          }
        }
      }
      return map; //return counted words
    }

    // print structure (with flag)
    void print(bool text) {
      if (text) { //flag check
        for (auto v : textVec) {
          cout << v << endl;
        }
      }
      else {
        for (auto v : dictVec) {
          cout << v << endl;
        }
      }
    }
};

#endif
