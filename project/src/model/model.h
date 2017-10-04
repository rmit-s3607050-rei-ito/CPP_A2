
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

// Players in game and pieces on the board
#include "player.h"
// #include "piece.h"
#include "board.h"

// Game over and back to main menu message
const std::string GAME_OVER_TEXT = "========== GAME OVER ==========";
const std::string TO_MAIN_MENU_TEXT = "Returning to the main menu...";

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
        player red;             // player using 'x' pieces
        player white;           // player using 'o' pieces

        // Array representing the game board and the pieces placed upon it
        board gameBoard;
        // Map of players, datastructure map is used due to get_player_list() type
        std::map<int, std::string> playerList;
        // Number of players registered to the system. Allocates ID based on count
        int playerCount;

        static std::unique_ptr<model> instance;
        model(void);                            // Constructor
        bool player_exists(const std::string&);

      public:
        // Model instance related functions
        static model * get_instance(void);
        static void delete_instance(void);
        virtual ~model(void);

        // Game related functions
        void start_game(int, int);
        void swap_current_player(void);
        bool make_move(int, int, int, int);
        bool check_forced_jump(void);
        bool game_draw(void);
        bool game_ended(void);
        void get_winner(void);
        void get_draw_message(void);

        // Player related functions
        int get_player_count(void);
        int get_player_score(int);
        int get_current_player(void);
        std::string get_player_name(int);
        std::map<int, std::string> get_player_list(void) const;
        bool add_player(const std::string &);
        char get_current_player_piece(void);
        void reduce_player_pieces(void);

        // Board related functions
        int get_width(void);
        int get_height(void);
        char get_piece(int,int);
        std::list<moves> get_forced_jumps(void);
    };
  }
}
