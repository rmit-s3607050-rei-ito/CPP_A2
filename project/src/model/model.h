
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

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

// Random for selecting which player will go first
#include <random>

// Players in game and tokens on the board
#include "player.h"
#include "token.h"

#pragma once

// Preventing magic numbers:
// height/width default to 8 (64 cells)
const int WIDTH = 8;
const int HEIGHT = 8;
// values for initializing board
const int X_END = 2;        // 'x' tokens from 0 to 2
const int O_START = 5;      // 'o' tokens from 5 to 7

namespace draughts
{
  namespace model
  {
    class model
    {
      // Game parameters
      private:
        // Game board dimensions
        int width;
        int height;
        // Player stats:
        player *currentPlayer;  // Pointer to which player is taking their turn
        player xPlayer;         // player using 'x' tokens
        player oPlayer;         // player using 'o' tokens

        // array representing the game board and the tokens placed upon it
        token board[WIDTH][HEIGHT];
        // map of players, datastructure map is used due to get_player_list() type
        std::map<int, std::string> playerList;
        // Number of players registered to the system. Allocates ID based on count
        int playerCount;

        static std::unique_ptr<model> instance;
        model(void);
        bool player_exists(const std::string&);

      public:
        // Model instance related functions
        static model * get_instance(void);
        static void delete_instance(void);
        virtual ~model(void);

        // Game related functions
        void start_game(int, int);
        bool make_move(int, int, int, int);
        void swap_current_player(void);
        int get_winner(void);

        // Player related functions
        int get_player_count(void);
        int get_player_score(int);
        int get_current_player(void);
        std::string get_player_name(int);
        std::map<int, std::string> get_player_list(void) const;
        bool add_player(const std::string &);
        char get_current_player_token(void);

        // Board related functions
        void init_board(void);
        int get_width(void);
        int get_height(void);
        char get_token(int,int);
    };
  }
}
