/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/tokenizer.hpp>

const int N_ARG = 9; //max arguments

// tokenizer & tokens to be used in multiple places
typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
const boost::char_separator<char> SEP
  {" 1234567890!@#$%^&*()_+=[{}]\\|;:'\"<>,./?"}; //given tokens

#endif
