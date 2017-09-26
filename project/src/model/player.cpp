
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
draughts::model::player::player(void) : playerScore(0), numTokens(NUM_TOKENS_PER_PLAYER)
{
}

// #################### Getters and Setters ####################
std::list<draughts::model::token> draughts::model::player::get_tokens(void) {
  return tokens;
}

int draughts::model::player::get_player_ID(void) {
  return playerID;
}

int draughts::model::player::get_player_score(void) {
  return playerScore;
}

void draughts::model::player::initialize(int pID, playerType pt) {
  playerID = pID;
  pType = pt;

  init_tokens();
}

void draughts::model::player::reduce_num_tokens(int tokenChange) {
  numTokens -= tokenChange;
}

void draughts::model::player::update_player_score(int scoreChange) {
  playerScore += scoreChange;
}

char draughts::model::player::get_token_char(void){
  if (pType == p1)
    return NORMAL_P1_TOKEN;
  else
    return NORMAL_P2_TOKEN;
}

// #################### Player's tokens related functions ####################
void draughts::model::player::init_tokens(void) {
  int x, y, startPos;
  int midRowStart, topBotRowStart;
  int rowStart, rowEnd;
  tokenType tokType;

  /* Player 1 tokens (Bottom of the board)
   * Top Row = (6, 1), (6, 3), (6, 5), (6, 7)
   * Mid Row = (7, 2), (7, 4), (7, 6), (7, 8)
   * Bot Row = (8, 1), (8, 3), (8, 5), (8, 7) */
  if (pType == p1) {
    rowStart = P1_ROW_START;
    rowEnd = P1_ROW_END;
    midRowStart = ODD;      // xPos even, yPos = odd
    topBotRowStart = EVEN;  // xPos odd, yPos = even
    tokType = p1Normal;
  }
  /* Player 2 tokens (Top of the board)
  * Top Row = (1, 2), (1, 4), (1, 6), (1, 8)
  * Mid Row = (2, 1), (2, 3), (2, 5), (2, 7)
  * Bot Row = (3, 2), (3, 4), (3, 6), (3, 8) */
  else {
    rowStart = P2_ROW_START;
    rowEnd = P2_ROW_END;
    // Reverse of above with p1's area
    midRowStart = EVEN;
    topBotRowStart = ODD;
    tokType = p2Normal;
  }

  for (x = rowStart; x <= rowEnd; x++) {
    if(x % 2)
      startPos = midRowStart;
    else
      startPos = topBotRowStart;
    // Loop through 4 times per row for each token
    for (y = startPos; y <= BOARD_WIDTH; y += TOKEN_SPACING) {
      draughts::model::token playerToken(x, y, tokType);
      tokens.push_front(playerToken);
    }
  }
}

// TODO, this can be placed in token.h maybe too
void draughts::model::player::promote_token(void){
  // TODO
}

void draughts::model::player::remove_token(void){
  // TODO
}
