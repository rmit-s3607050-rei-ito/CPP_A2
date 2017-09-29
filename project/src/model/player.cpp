
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

// Constructor, set initial score to 0, number of tokens in possession 12
draughts::model::player::player(type t) : playerScore(0), numTokens(NUM_TOKENS)
{
  playerType = t;
}

// #################### Getters and Setters ####################

int draughts::model::player::get_id(void) {
  return playerID;
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

void draughts::model::player::set_score(int score) {
  playerScore = score;
}

void draughts::model::player::set_type(type ttype) {
  playerType = ttype;
}

void draughts::model::player::reduce_num_tokens(int tokenChange) {
  numTokens -= tokenChange;
}

void draughts::model::player::update_player_score(int scoreChange) {
  playerScore += scoreChange;
}
