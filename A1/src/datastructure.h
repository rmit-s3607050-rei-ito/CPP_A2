/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#ifndef DS_H
#define DS_H

#include "util.h"

class DataStructure {
  public:
    bool debug = false; //debug text toggle (all structures)

    // add file to data structure (with flag)
    virtual bool add(std::string fileName, bool text) = 0;
    // structure search & store into map
    virtual std::map<std::string, int> search() = 0;
    // print structure (with flag)
    virtual void print(bool text) = 0;
};

#endif
