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

#include <iostream>
#include "util.h"

namespace draughts
{
  namespace model
  {
    class piece
    {
      protected:
        team pieceTeam;
        //coordinates position;

      public:
        piece(team);
        // Getters/Settters
        // 1. To be overidden
        virtual type get_type(void) = 0;
        virtual char get_icon(void) = 0;  // Get specific character for a piece
        // 2. Preset, cannot override
        team get_team(void);
    };
  }
}
