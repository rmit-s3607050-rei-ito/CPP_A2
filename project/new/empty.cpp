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

#include "empty.h"

// Constructor, allocates type
draughts::model::piece::empty(void)
{
}

type get_type(void)
{
  return EMPTY;
}

bool check_move(int diffx, int diffy)
{
  return false;
}

team draughts::model::piece::get_team(void)
{
  return pieceTeam;
}
