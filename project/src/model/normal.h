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

const char RED_N_PIECE = 'x';
const char WHITE_N_PIECE = 'o';

namespace draughts
{
  namespace model
  {
    class normal : public piece
    {
      public:
        normal(void);
        type get_type(void);
        bool check_move(int,int);
        char get_icon(void);
    };
  }
}