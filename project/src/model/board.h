
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
const int jump = 1;
const int up = (int)draughts::direction::UP;
const int down = (int)draughts::direction::DOWN;
const int upJump = up - jump;
const int downJump = down + jump;
// Checking for possible jumps
const int FIRST_COL = 0;
const int LAST_COL = 7;
const int RIGHT_JUMP = 2;
const int LEFT_JUMP = -2;
// Pre-appended string for invalid moves and invalid selections and possible jumps
const std::string isMsg = "Invalid selection: ";
const std::string imMsg = "Invalid move: ";
const std::string jumpMsg = "A jump must be taken with token at: ";

namespace draughts
{
  namespace model
  {
    class board {
      // 2D array storing cell contents of the board
      token gameBoard[WIDTH][HEIGHT];
      // Total number of non-empty tokens on the board
      int numTokens;

      public:
        // Constructor
        board(void);
        // Initialization and validation
        void init_board();
        bool validate_type(type, type);
        bool check_valid_selection(type, int, int);
        bool check_valid_move(int, int, int, int);
        // Jumping validation
        bool check_all_possible_jumps(void);
        bool check_individual_jump(int, int);
        bool check_jump_direction(int, int, int);
        bool can_jump(int, int, int, int);
        // Score related functions
        int move_token(int, int, int, int);
        int promote_token(int, int);
        // Getters/Settters
        char get_token(int, int);
        type get_type(int, int);
        std::pair<int,int> get_token_jumped_over(int, int, int, int);
        int get_width(void);
        int get_height(void);
    };
  }
}
