
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

// Accounting for array difference (since they start from 0)
const int ARRAY_DIFF = 1;
// height/width default to 8 (64 cells)
const int WIDTH = 8;
const int HEIGHT = 8;
// values for initializing board
// 'x' tokens from 0 to 2 (display/input = 1 to 3)
const int X_START = 0;
const int X_END = 2;
// 'o' tokens from 5 to 7 (display/input = 6 to 8)
const int O_START = 5;
const int O_END = 7;
// calculating movement on the board
const int jump = 1;
const int up = (int)draughts::direction::UP;
const int down = (int)draughts::direction::DOWN;
const int upJump = up - jump;
const int downJump = down + jump;
// Pre-appended string for invalid moves and invalid selections
const std::string isMsg = "Invalid selection: ";
const std::string imMsg = "Invalid move: ";


namespace draughts
{
  namespace model
  {
    class board {
      // 2D array storing cell contents of the board
      token gameBoard[WIDTH][HEIGHT];

      public:
        // Constructor
        board(void);
        // Initialization and validation
        void init_board(void);
        bool check_valid_selection(type, int, int);
        bool check_valid_move(int, int, int, int);
        bool validate_type(type, type);
        // Score related functions
        int move_token(int, int, int, int);
        int promote_token(int, int);
        bool check_possible_jump(void);
        // Getters/Settters
        char get_token(int, int);
        type get_type(int, int);
        std::pair<int,int> get_token_jumped_over(int, int, int, int);
        int get_width(void);
        int get_height(void);
    };
  }
}
