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

namespace draughts
{
  namespace model
  {
    class king : public piece
    {
      public:
        king(team);
        // Overridden functions
        virtual type get_type(void) override;
        virtual char get_icon(void) override;
        // Own unique function
        coordinates get_backward_action(bool, int, int, int);
    };
  }
}
