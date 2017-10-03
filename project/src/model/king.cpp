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

// bool check_move(int diffx, int diffy)
// {
//   return false;
// }

char draughts::model::king::get_icon(void) {
  if(pieceTeam == RED)
    return RED_K_PIECE;
  else
    return WHITE_K_PIECE;
}
