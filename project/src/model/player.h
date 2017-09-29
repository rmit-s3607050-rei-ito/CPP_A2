
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

// List to store all tokens in game
#include <list>
// Access to tokens as each player has their own set
#include "token.h"

#pragma once

namespace draughts
{
  namespace model
  {
    class player
    {
      private:
        int playerID;
        int playerScore;
        int numTokens;
        type playerType;

      public:
        // Constructor
        player(type);
        // Getters/Settters
        int get_id(void);
        int get_score(void);
        type get_type(void);
        void set_id(int);
        void set_score(int);
        void set_type(type);
        void reduce_num_tokens(int);
        void update_player_score(int);
    };
  }
}
