
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

#include "token.h"
#include "direction.h"
#include <iostream>
#include <list>

// Set of coordinates, x and y
typedef std::pair<int, int> coordinates;
// Pair of start and end coordinates
typedef std::pair<coordinates, coordinates> moves;

// Accounting for array difference (since they start from 0)
const int ARRAY_DIFF = 1;
// Height/width default to 8 (64 cells)
const int WIDTH = 8;
const int HEIGHT = 8;
// Values for initializing board
// 'x' tokens from 0 to 2 (display/input = 1 to 3)
const int X_START = 0;
const int X_END = 2;
// 'o' tokens from 5 to 7 (display/input = 6 to 8)
const int O_START = 5;
const int O_END = 7;
// Calculating movement on the board
const int JUMP = 1;
const int UP = (int)draughts::direction::UP;
const int DOWN = (int)draughts::direction::DOWN;
const int LEFT = -1;
const int RIGHT = 1;
const int UP_JUMP = UP - JUMP;
const int DOWN_JUMP = DOWN + JUMP;
// Checking for possible jumps
const int FIRST_COL = 0;
const int SECOND_COL = 1;
const int SECOND_LAST_COL = 6;
const int LAST_COL = 7;
const int RIGHT_JUMP = 2;
const int LEFT_JUMP = -2;
// Pre-appended string for invalid moves and invalid selections and possible jumps
const std::string isMsg = "Invalid selection: ";
const std::string imMsg = "Invalid move: ";
const std::string jumpMsg = "Token at: ";

namespace draughts
{
  namespace model
  {
    class board {
      // 2D array storing cell contents of the board
      token gameBoard[WIDTH][HEIGHT];
      /* All coords of tokens that are able to jump, reset when rechecking jumps
       * Essentially a list of pairs of coordinates: the token and where it lands */
      std::list<moves> forcedJumps;

      public:
        // Constructor
        board(void);
        // Initialization and validation
        void init_board();
        bool check_valid_selection(type, int, int);
        bool check_valid_move(int, int, int, int);
        bool is_same_type(type, type);
        // Move validation
        bool check_all_possible_moves(int, int);
        bool check_move_direction(int, int, int);
        // Jumping validation
        bool check_all_possible_jumps(type, int);
        bool check_individual_jump(int, int);
        bool check_jump_direction(int, int, int);
        bool can_jump(int, int, int, int);
        // Score related functions
        int move_token(int, int, int, int);
        bool promote_token(int, int);
        // Getters/Settters
        char get_token(int, int);
        type get_type(int, int);
        coordinates get_token_jumped_over(int, int, int, int);
        std::list<moves> get_forced_jumps(void);
        int get_width(void);
        int get_height(void);
    };
  }
}
