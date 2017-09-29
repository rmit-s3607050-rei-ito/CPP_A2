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

namespace draughts
{
  namespace model
  {
    class king : public piece
    {
      public:
        king(void);
        type get_type(void);
        bool check_move(int,int);
    };
  }
}
