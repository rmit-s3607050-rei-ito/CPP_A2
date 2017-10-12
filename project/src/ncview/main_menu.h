/* COSC1254 - Programming using C++ - Assignment 2
 * Assignment done as a pair
 * -----------------------------------------------------------------------------
 * Name             : Rei Ito
 * Student Number   : s3607050
 * -----------------------------------------------------------------------------
 * Name             : Pacific Thai
 * Student Number   : s3429648
 * -----------------------------------------------------------------------------
 * Using skeleton code provided by Paul Miller
 */

#include "menu.h"

#pragma once

namespace draughts
{
  namespace ncview
  {
    class main_menu : public menu
    {
      static const std::vector<std::string> strings;
      public:
        main_menu(void);
        virtual ~main_menu(void);
    };
  }
}
