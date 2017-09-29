
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
#include "board.h"

#pragma once

namespace draughts
{
  namespace model
  {
    class model
    {
      // Game parameters
      private:
        player *currentPlayer;  // Pointer to which player is taking their turn
        player xPlayer;         // player using 'x' tokens
        player oPlayer;         // player using 'o' tokens

<<<<<<< HEAD
      // array representing the game board and the tokens placed upon it
      board gameBoard;
      // map of players, datastructure map is used due to get_player_list() type
      std::map<int, std::string> playerList;
      // Number of players registered to the system. Allocates ID based on count
      int playerCount;
=======
        // array representing the game board and the tokens placed upon it
        token board[WIDTH][HEIGHT];
        // map of players, datastructure map is used due to get_player_list() type
        std::map<int, std::string> playerList;
        // Number of players registered to the system. Allocates ID based on count
        int playerCount;
>>>>>>> c80b0ff320fea8b37066618a0a9081e68f31c63e

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
        void reduce_player_tokens(int);

        // Board related functions
        int get_width(void);
        int get_height(void);
        char get_token(int,int);
    };
  }
}
