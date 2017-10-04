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

#include "normal.h"

// Constructor, calls parent using parameters
draughts::model::normal::normal(team t) : piece(t)
{
}

type draughts::model::normal::get_type(void)
{
  return NORMAL;
}

char draughts::model::normal::get_icon(void) {
  if(pieceTeam == RED)
    return RED_N_PIECE;
  else
    return WHITE_N_PIECE;
}
