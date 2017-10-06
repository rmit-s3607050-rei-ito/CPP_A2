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

#include "king.h"

// Constructor, calls parent using parameters
draughts::model::king::king(team t) : piece(t)
{
}

type draughts::model::king::get_type(void)
{
  return KING;
}

char draughts::model::king::get_icon(void) {
  char icon = ' ';

  if(pieceTeam == RED)
    icon = RED_K_PIECE;
  else
    icon = WHITE_K_PIECE;

  return icon;
}

coordinates draughts::model::king::get_backward_action(bool jump, int x, int y,
                                                       int direction) {
  // Essentially the reverse of a forward action, see piece.cpp for commenting
  int forwardX, forwardY;
  int movement;
  if(pieceTeam == RED) {
    if(jump)
      movement = UP_JUMP;
    else
      movement = UP;
  } else {
    if(jump)
      movement = DOWN_JUMP;
    else
      movement = DOWN;
  }

  forwardX = x + movement;
  forwardY = y + direction;
  return std::make_pair(forwardX, forwardY);
}
