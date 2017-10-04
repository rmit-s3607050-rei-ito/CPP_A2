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

#include "util.h"

namespace draughts
{
  namespace model
  {
    class piece
    {
      protected:
        team pieceTeam;

      public:
        // Constructor
        piece(team);
        // 1. To be overidden, = 0 means no base version
        virtual type get_type(void) = 0;
        virtual char get_icon(void) = 0;
        // 2. Preset, cannot override
        bool check_possible_move(void);
        bool check_valid_move(int, int, int, int);
        team get_team(void);
        coordinates get_forward_action(bool, int, int, int);
    };
  }
}
