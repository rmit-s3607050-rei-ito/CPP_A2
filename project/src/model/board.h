
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

#include <memory>
#include <list>

#include "piece.h"
#include "empty.h"
#include "normal.h"
#include "king.h"

// Height/width default to 8 (64 cells)
const int WIDTH = 8;
const int HEIGHT = 8;

namespace draughts
{
  namespace model
  {
    class board {
      // 2D array storing cell contents of the board
      std::unique_ptr<piece> gameBoard[WIDTH][HEIGHT];

    /* All coords of pieces that are able to jump, reset when rechecking jumps
     * Essentially a list of pairs of coordinates: the piece and where it lands */
      std::list<moves> forcedJumps;

      public:
        // Constructor
        board(void);
        // Initialization and validation (via exceptions)
        void init_board();
        void check_valid_selection(team, int, int);
        void check_valid_move(int, int, int, int);
        // Move validation
        bool check_all_possible_moves(int, int);
        bool check_move_direction(int, int, int);
        // Jumping validation
        bool check_all_possible_jumps(team, int);
        bool check_individual_jump(int, int);
        bool check_jump_direction(int, int, int);
        bool can_jump(int, int, int, int);
        // Score related functions
        bool move_piece(int, int, int, int);
        bool promote_piece(int, int);
        // Getters/Settters
        char get_piece(int, int);
        coordinates get_coordinates_of_jump(int, int, int, int);
        std::list<moves> get_forced_jumps(void);
        void reset_jump_list(void);
        int get_width(void);
        int get_height(void);
    };
  }
}
