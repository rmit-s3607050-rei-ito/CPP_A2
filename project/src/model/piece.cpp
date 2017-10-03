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

// Constructor, by default no team unless set
draughts::model::piece::piece(team t) : pieceTeam(t)
{
}

// #################### Getters and Setters ####################
// void draughts::model::piece::set_team(team t)
// {
//   pieceTeam = t;
// }

team draughts::model::piece::get_team(void)
{
  return pieceTeam;
}
