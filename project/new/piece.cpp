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

// Constructor, allocates type
draughts::model::piece::piece(void)
{
}

// #################### Getters and Setters ####################
team draughts::model::piece::get_team(void)
{
  return pieceTeam;
}
