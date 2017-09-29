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

// What board elements appear as
// const char N_O_TOKEN = 'o';
// const char K_O_TOKEN = 'O';
// const char N_X_TOKEN = 'x';
// const char K_X_TOKEN = 'X';
// const char EMPTY_TOKEN = ' ';

enum team { RED, WHITE, NO_TEAM };
enum type { NORMAL, KING, EMPTY };

namespace draughts
{
  namespace model
  {
    class piece
    {
      private:
        team pieceTeam;

      public:
        piece(void);
        // Getters/Settters
        virtual type get_type(void) = 0;

        virtual bool check_move(int,int);

        team get_team(void);

        // void set_type(type);
        // void promote_token(type);
        // // Return specific character for token
        // char print_token(void);
    };
  }
}
