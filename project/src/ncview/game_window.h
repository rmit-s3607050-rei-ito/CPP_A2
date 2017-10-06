
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

#include "window.h"
#include "../model/model.h"
#include <map>
#include <string>
#include <utility>
#include <boost/algorithm/string.hpp>

// Enables std::find, searching through list
#include <algorithm>
// Regular expression for input validation
#include <regex>
const std::string REGULAR_MOVE_REGEX = "[1-8],[1-8]-[1-8],[1-8]";

namespace draughts
{
  namespace ncview
  {
    using view_player = std::pair<int, std::string>;
    using player_pair = std::pair<view_player, view_player>;
    class game_window : public window
    {
      player_pair players;
      bool quit;

      // Printing
      void print_top_row(void);
      void print_line(int);
      void print_row(int);
      void print_possible_jumps(std::list<moves>);
      void print_turn_info(void);

      // Retrieve input from user
      moves get_move_input(void);
      moves get_jump_input(std::list<moves>);
      coordinates strtocoord(const std::string&);

      // Input validation, uses exception hence void type
      void validate_move_input(const std::string &);

      // Forced jumping
      moves perform_forced_jump(void);

      public:
        game_window(const player_pair&);
        virtual void activate(void) override;
        void display_board(void);
        virtual ~game_window(void){}
    };
  }
}
