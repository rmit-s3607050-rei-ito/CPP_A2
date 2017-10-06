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

#include "piece.h"

// Constructor
draughts::model::piece::piece(team t) : pieceTeam(t)
{
}

// #################### Getters and Setters ####################
void draughts::model::piece::check_valid_move(int x1, int y1, int x2, int y2)
{
  // Movement difference for row and column
  int rowMove = x2 - x1;
  int colMove = y2 - y1;

  // String to hold exception message to throw
  std::string invalidMove = imMsg;

  // 1. Player tried to move forward or left/right
  if(rowMove == 0 || colMove == 0) {
    invalidMove += "You can only move diagonally";
    throw invalidMove;
  }

  /* 2. End coords cannot be both positive or both negative, must vary
   * if (Both positive || Both negative) */
  if ((x2 % 2 == 0 && y2 % 2 == 0) || (x2 % 2 != 0 && y2 % 2 != 0)) {
    invalidMove += "The selected cell is not reachable";
    throw invalidMove;
  }

  // 3. Player entered a move with a difference > 2
  if (colMove > DOWN_JUMP || colMove < UP_JUMP){
    invalidMove += "You cannot move more than 2 spaces";
    throw invalidMove;
  }
}

team draughts::model::piece::get_team(void)
{
  return pieceTeam;
}

coordinates draughts::model::piece::get_forward_action(bool jump, int x, int y,
                                                       int direction)
{
  // Coordinates of landing spot after a move
  int forwardX, forwardY;

  // Movement shift (+1 for move, +2 for jump)
  int movement;

  // Moving by row will vary whether going up or down, toggle between jump and move
  // 1. Red 'x' type pieces, forward = down + direction, backwards = reverse
  if(pieceTeam == RED) {
    if(jump)
      movement = DOWN_JUMP;
    else
      movement = DOWN;
  // 2. White 'o' type pieces, forward = up + direction, backwards = reverse
  } else {
    if(jump)
      movement = UP_JUMP;
    else
      movement = UP;
  }

  // Direction doesn't vary between piece types for column (y-axis) movement
  forwardX = x + movement;
  forwardY = y + direction;

  return std::make_pair(forwardX, forwardY);
}
