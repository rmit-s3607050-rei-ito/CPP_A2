
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
#include <map>
#include <string>
#include <utility>
#include <boost/algorithm/string.hpp>

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

      void print_top_row(void);
      void print_line(int);
      void print_row(int);
      std::pair<std::pair<int,int>, std::pair<int,int>> get_move_input(void);
      std::pair<int,int> strtocoord(const std::string&);

      // Added function
      bool validate_move_input(const std::string &);

      public:
        game_window(const player_pair&);
        virtual void activate(void) override;
        void display_board(void);
        virtual ~game_window(void){}
    };
  }
}
