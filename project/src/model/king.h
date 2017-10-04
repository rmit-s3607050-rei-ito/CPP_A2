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

// Inheriting from piece
#include "piece.h"
// Piece char representation
const char RED_K_PIECE = 'X';
const char WHITE_K_PIECE = 'O';

namespace draughts
{
  namespace model
  {
    class king : public piece
    {
      public:
        king(team);
        type get_type(void);
        char get_icon(void);
        coordinates get_backward_action(bool, int, int, int);
    };
  }
}
