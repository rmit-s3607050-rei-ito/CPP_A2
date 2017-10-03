
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

// Constructor, allocates type
draughts::model::token::token(void) : tokenType(EMPTY)
{
}

// #################### Getters and Setters ####################
type draughts::model::token::get_type(void) {
  return tokenType;
}

void draughts::model::token::set_type(type t){
  tokenType = t;
}

void draughts::model::token::promote_token(type t) {
  if(t == N_CROSS)
    set_type(K_CROSS);
  else if (t == N_CIRCLE)
    set_type(K_CIRCLE);
}

// #################### Display token ####################
char draughts::model::token::print_token(void) {
  char token = EMPTY_TOKEN;

  switch(tokenType) {
    case N_CIRCLE:
      token = N_O_TOKEN;
      break;
    case K_CIRCLE:
      token = K_O_TOKEN;
      break;
    case N_CROSS:
      token = N_X_TOKEN;
      break;
    case K_CROSS:
      token = K_X_TOKEN;
      break;
    case EMPTY:
      break;
  }

  return token;
}
