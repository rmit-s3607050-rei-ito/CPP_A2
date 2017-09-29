
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

// Storing all possible jumps
#include <list>
// Jumps you can make for a single token
const int MAX_JUMPS = 4; // For king pieces max = 4 (forward/back) + (left/right)

// What board elements appear as
const char N_O_TOKEN = 'o';
const char K_O_TOKEN = 'O';
const char N_X_TOKEN = 'x';
const char K_X_TOKEN = 'X';
const char EMPTY_TOKEN = ' ';

// How many tokens a player starts with, when 0 player loses the game
const int NUM_TOKENS = 12;

enum type { N_CIRCLE, K_CIRCLE, N_CROSS, K_CROSS, EMPTY };

namespace draughts
{
  namespace model
  {
    class token
    {
      type tokenType;     // Whether piece is normal or king, also factor player
      // Possible jumps a token can make, max 4 (for king piece)
      std::list<std::pair<int,int>> possibleJumps;

      public:
        // Constructor
        token(void);
        // Getters/Settters
        type get_type(void);
        void set_type(type);
        void promote_token(type);
        // Jumping related calculations
        void add_possible_jump(int, int);
        void reset_possible_jumps(void);
        // Return specific character for token
        char print_token(void);
    };
  }
}
