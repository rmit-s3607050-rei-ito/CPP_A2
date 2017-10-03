/*
  COSC1254 Assignment 1
  Author: Rei Ito (s3607050)
*/

#include <chrono>

#include "util.h"
#include "datastructure.h"
#include "list.h"
#include "vector.h"
#include "multiset.h"
#include "customlist.h"
#include "customtree.h"

// name spaces
using namespace std;
using namespace boost::program_options;

int main(int argc, const char *argv[]) {
  bool debug = false; //debug text toggle

  string datFileName, txtFileName, outFileName; ///file names

  DataStructure *dStruct; //used structure

  map<string, int> outMap; //counter map

  if (argc != N_ARG) { //arg count check
    cout << "invalid amount of arguments: " << N_ARG << " required\n";
    exit(EXIT_FAILURE);
  }

  options_description desc{ "Options" }; //init option menu
  desc.add_options() //specify options
    ("help,h", "help screen")
    ("datastructure,s", value<string>(), "specify datastructure\n"
                              "Use: 'list', 'vector', 'set',"
                              "'customList', 'customTree'")
    ("dictionary,d", value<string>(), "specify dictionary file (.dat)")
    ("text,t", value<string>(), "specify text file (.txt)")
    ("out,o", value<string>(), "specify output file (.csv)");

  variables_map vm;

  try { //try/catch for vairous errors
    store(parse_command_line(argc, argv, desc), vm); //store menu options
    notify(vm); //update

    if (vm.count("help")) //print help menu
      cout << desc << "\n";
    else if (vm.count("datastructure") && vm.count("dictionary")
      && vm.count("text") && vm.count("out")) { //check for all flags

      // valid type check & struct store
      if (vm["datastructure"].as<string>() == "list")
        dStruct = new List;
      else if (vm["datastructure"].as<string>() == "vector")
        dStruct = new Vector;
      else if (vm["datastructure"].as<string>() == "set")
        dStruct = new Set;
      else if (vm["datastructure"].as<string>() == "customList")
        dStruct = new CustomList;
      else if (vm["datastructure"].as<string>() == "customTree")
        dStruct = new CustomTree;
      else //invalid datastructure
        throw error("invalid datastructure");

      // valid file checking & name store
      if (boost::ends_with(vm["text"].as<string>(), ".txt")) //text
        txtFileName = vm["text"].as<string>();
      else //invalid file type
        throw error("wrong file type");

      if (
        boost::ends_with(vm["dictionary"].as<string>(), ".dat")
        || boost::ends_with(vm["dictionary"].as<string>(), ".dict")
      ) //dictionary (supports two file types)
        datFileName = vm["dictionary"].as<string>();
      else //invalid file type
        throw error("wrong file type");

      outFileName = vm["out"].as<string>(); //output (no validation)
    }
    else //hits nothing or not enough arguments
      throw error("not enough flags");

    // file checking & data store (text + dictionary)
    if (!dStruct->add(txtFileName, true))
      throw error("unable to open file: " + txtFileName); //unable to open file
    else if (!dStruct->add(datFileName, false))
      throw error("unable to open file: " + datFileName); //unable to open file

    // search, count & store into map
    outMap = dStruct->search();

    // save map into output file
    ofstream outFile(outFileName);
    if (outFile.is_open()) { //check open
      for (auto m : outMap) { //map loop
        outFile << m.first << ": "; //store string
        if (m.second == 0) //empty check
          outFile << "none" << "\n";
        else
          outFile << m.second << "\n";

        if (debug) //print process
          cout << "saving: " << m.first << ": " << m.second << endl;
      }
    }
    else //unable to open file
      throw error("unable to open file: " + outFileName);
  }
  catch (const error &ex) { //all other errors & print help menu
    std::cerr << ex.what() << "\n";
    cout << desc << "\n";
  }
}
