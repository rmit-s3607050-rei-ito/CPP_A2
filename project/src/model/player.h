
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
// #include "token.h"
#include "piece.h"

// How many tokens a player starts with, when 0 player loses the game
const int STARTING_TOKENS = 12;

#pragma once

namespace draughts
{
  namespace model
  {
    class player
    {
      int playerID;
      int playerScore;
      int numTokens;
      team playerTeam;

      public:
        // Constructor and initialization
        player(team);
        void initialize(void);
        // Getters/Settters
        int get_id(void);
        int get_num_tokens(void);
        int get_score(void);
        team get_team(void);
        void set_id(int);
        // void set_type(type);
        // Changing token count and score by -1 and + 1 respectively
        void reduce_token_count(void);
        void increment_score(void);
    };
  }
}
