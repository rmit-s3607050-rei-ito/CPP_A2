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

#include <list>

enum team { RED, WHITE, NO_TEAM };
enum type { NORMAL, KING, EMPTY };

// Set of coordinates, x and y
typedef std::pair<int, int> coordinates;

namespace draughts
{
  namespace model
  {
    class piece
    {
      private:
        team pieceTeam;
        char icon;
        coordinates position;

      public:
        piece(coordinates);
        // Getters/Settters
        virtual type get_type(void) = 0;

        virtual bool check_move(int,int);

        team get_team(void);

        // void set_type(type);
        // void promote_token(type);

        // Return specific character for token
        virtual char get_icon(void);
    };
  }
}
