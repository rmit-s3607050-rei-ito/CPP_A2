
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

const int NUM_STARTING_TOKENS = 12;

#pragma once

enum playerType { x, o };

namespace draughts
{
  namespace model
  {
    class player {
      private:
        int playerID;
        int playerScore;
        int numTokens;
        playerType pType;

      public:
        // Constructor
        player(void);
        // Getters/Settters
        int get_player_ID(void);
        int get_player_score(void);
        void set_id(int);
        void set_type(playerType);
        void reduce_num_tokens(int);
        void update_player_score(int);
        char get_token_char(void);
        // TODO x2
        // void promote_token(void);
        // void remove_token(void);
    };
  }
}
