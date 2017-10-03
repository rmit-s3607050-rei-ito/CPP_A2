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

// Constructor, allocates type
draughts::model::piece::king(void)
{
}

type get_type(void)
{
  return KING;
}

bool check_move(int diffx, int diffy)
{
  return false;
}

team draughts::model::piece::get_team(void)
{
  return pieceTeam;
}

char draughts::model::piece::get_icon(void) {
  if(team == RED)
    return RED_K_PIECE;
  else
    return WHITE_K_PIECE;
}
