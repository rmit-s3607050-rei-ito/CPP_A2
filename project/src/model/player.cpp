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

#include "player.h"

// Constructor
draughts::model::player::player(team t) : player_team(t)
{
}

// Blank slate starting parameters for player
void draughts::model::player::initialize(void)
{
  player_score = 0;
  num_pieces = NUM_STARTING_PIECES;
}

// #################### Getters and Setters ####################
int draughts::model::player::get_id(void)
{
  return player_id;
}

int draughts::model::player::get_num_pieces(void)
{
  return num_pieces;
}

int draughts::model::player::get_score(void)
{
  return player_score;
}

team draughts::model::player::get_team(void)
{
  return player_team;
}

void draughts::model::player::set_id(int pID)
{
  player_id = pID;
}

// #################### Incremental change ####################
void draughts::model::player::reduce_piece_count(void)
{
  num_pieces--;
}

void draughts::model::player::increment_score(void)
{
  player_score++;
}
