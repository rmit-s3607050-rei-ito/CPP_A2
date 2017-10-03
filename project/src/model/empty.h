/* COSC1254 - Programming using C++ - Assignment 2
 * Assignment done as a pair
 * -----------------------------------------------------------------------------
 * Name             : Rei Ito
 * Student Number   : s3607050
 * -----------------------------------------------------------------------------
 * Name             : Pacific Thai
 * Student Number   : s3429648
 * -----------------------------------------------------------------------------
 */

#pragma once

// #include "piece.h"

const char EMPTY_PIECE = ' ';

namespace draughts
{
  namespace model
  {
    class empty : public piece
    {
      public:
        empty(void);
        type get_type(void);
        bool check_move(int,int);
        char get_icon(void);
    };
  }
}
