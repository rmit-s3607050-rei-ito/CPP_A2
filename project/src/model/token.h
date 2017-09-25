
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
const char NORMAL_P1_TOKEN = 'o';
const char KING_P1_TOKEN = 'O';
const char NORMAL_P2_TOKEN = 'x';
const char KING_P2_TOKEN = 'X';
const char EMPTY = ' ';

enum tokenType { p1Normal, p1King, p2Normal, p2King };

namespace draughts
{
  namespace model
  {
    class token {
      private:
        int x;
        int y;
        tokenType pieceType;     // Whether piece is normal or king, also factor player

      public:
        // Constructor
        token(int, int, tokenType);
        // Getters/Settters
        int get_x_pos(void);
        int get_y_pos(void);
        tokenType get_type(void);
        // Return specific character for token
        char print_token(void);
    };
  }
}
