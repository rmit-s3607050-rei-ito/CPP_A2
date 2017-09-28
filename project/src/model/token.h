
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

#pragma once

// What board elements appear as
const char N_O_TOKEN = 'o';
const char K_O_TOKEN = 'O';
const char N_X_TOKEN = 'x';
const char K_X_TOKEN = 'X';
const char EMPTY_TOKEN = ' ';

enum type { N_CIRCLE, K_CIRCLE, N_CROSS, K_CROSS, EMPTY };

namespace draughts
{
  namespace model
  {
    class token
    {
      private:
        type tokenType;     // Whether piece is normal or king, also factor player

      public:
        // Constructor
        token(void);
        // Getters/Settters
        type get_type(void);
        void set_type(type);
        // Return specific character for token
        char print_token(void);
    };
  }
}
