
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
draughts::model::player::player(type t) : playerType(t)
{
}

// Blank slate starting parameters for player
void draughts::model::player::initialize(void){
  playerScore = 0;
  numTokens = NUM_TOKENS;
}

// #################### Getters and Setters ####################
int draughts::model::player::get_id(void) {
  return playerID;
}

int draughts::model::player::get_num_tokens(void) {
  return numTokens;
}

int draughts::model::player::get_score(void) {
  return playerScore;
}

type draughts::model::player::get_type(void){
  return playerType;
}

void draughts::model::player::set_id(int pID) {
  playerID = pID;
}

void draughts::model::player::set_type(type ttype) {
  playerType = ttype;
}

// #################### Incremental change ####################
void draughts::model::player::reduce_token_count(void) {
  numTokens--;
}

void draughts::model::player::increment_score(void) {
  playerScore++;
}
