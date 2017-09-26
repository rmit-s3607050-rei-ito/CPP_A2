
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

// Used to prevent magic numbers in init_tokens
const int NUM_TOKENS_PER_PLAYER = 12;
const int P2_ROW_START = 1;
const int P2_ROW_END = 3;
const int P1_ROW_START = 6;
const int P1_ROW_END = 8;
const int BOARD_WIDTH = 8;

const int EVEN = 2;
const int ODD = 1;
const int TOKEN_SPACING = 2;

enum playerType { p1, p2 };

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

      std::list<draughts::model::token> tokens;

      public:
        // Constructor
        player(void);
        // Getters/Settters
        std::list<draughts::model::token> get_tokens(void);
        int get_player_ID(void);
        int get_player_score(void);
        void initialize(int, playerType);
        void reduce_num_tokens(int);
        void update_player_score(int);
        char get_token_char(void);
        // Player's tokens
        void init_tokens(void);
        // TODO x2
        void promote_token(void);
        void remove_token(void);
    };
  }
}
