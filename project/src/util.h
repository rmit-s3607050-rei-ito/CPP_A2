
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

#include <iostream>
#include "direction.h"

// Random number generation
const int MIN = 0;
const int MAX = 1;

// Piece related constants
enum team { RED, WHITE, NO_TEAM };
enum type { NORMAL, KING, EMPTY };

// Set of coordinates, x and y
typedef std::pair<int, int> coordinates;
// Pair of start and end coordinates
typedef std::pair<coordinates, coordinates> moves;

// Accounting for array difference (since they start from 0)
const int ARRAY_DIFF = 1;

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
const std::string isMsg = "Invalid Selection: ";
const std::string imMsg = "Invalid Move: ";
const std::string jumpMsg = "Token at: ";
