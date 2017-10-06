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

// Constructor, calls parent using parameters
draughts::model::empty::empty(team t) : piece(t)
{
}

type draughts::model::empty::get_type(void)
{
  return EMPTY;
}

char draughts::model::empty::get_icon(void) {
  return EMPTY_PIECE;
}
