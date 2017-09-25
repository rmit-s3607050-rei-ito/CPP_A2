
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

#include "token.h"

// Constructor, allocates x, y, type and owner
draughts::model::token::token(int xPos, int yPos, tokenType tType) :
                                  x(xPos), y(yPos), pieceType(tType)
{
}

// #################### Getters and Setters ####################
int draughts::model::token::get_x_pos(void) {
  return x;
}

int draughts::model::token::get_y_pos(void) {
  return y;
}

tokenType draughts::model::token::get_type(void) {
  return pieceType;
}

// #################### Other functions ####################
char draughts::model::token::print_token(void) {
  // Player 1's token
  if(pieceType == p1Normal)
    return NORMAL_P1_TOKEN;
  else if (pieceType == p1King)
    return KING_P1_TOKEN;

  // Player 2's token
  else if (pieceType == p2Normal)
    return NORMAL_P2_TOKEN;
  else
    return KING_P2_TOKEN;
}
