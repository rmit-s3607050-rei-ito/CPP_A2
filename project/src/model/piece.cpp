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

//

// #################### Functions that can be overidden ####################

// #################### Getters and Setters ####################
bool draughts::model::piece::check_valid_move(int startx, int starty,
                                              int endx, int endy)
{
  // Movement difference for row and column
  int rowMove = endx - startx;
  int colMove = endy - starty;

  // std::cout << "REACHED\n";
  // std::cout << rowMove << "," << colMove << "\n";

  // 1. Player tried to move forward or left/right
  if(rowMove == 0 || colMove == 0) {
    std::cout << imMsg << "You can only move diagonally" << std::endl;
    return false;
  }

  // Extra check. Player tried to move incorrectly with normal pieces
  if(pieceTeam == RED && rowMove == UP) {
    std::cout << imMsg << "Red cannot move up with a 'x' piece" << std::endl;
    return false;
  }
  else if(pieceTeam == WHITE && rowMove == DOWN) {
    std::cout << imMsg << "White cannot move down with a 'o' piece" << std::endl;
    return false;
  }

  /* 2. End coords cannot be both positive or both negative, must vary
   * if (Both positive || Both negative) */
  if ((endx % 2 == 0 && endy % 2 == 0) || (endx % 2 != 0 && endy % 2 != 0)) {
    std::cout << imMsg << "The selected cell is not reachable" << std::endl;
    return false;
  }

  // 3. Player entered a move with a difference > 2
  if (colMove > DOWN_JUMP || colMove < UP_JUMP){
    std::cout << imMsg << "You cannot move more than 2 spaces" << std::endl;
    return false;
  }

  return true;
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
