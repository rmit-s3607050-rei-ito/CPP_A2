/* COSC1254 - Programming using C++ - Assignment 2
 * Assignment done as a pair
 * -----------------------------------------------------------------------------
 * Name             : Rei Ito
 * Student Number   : s3607050
 * -----------------------------------------------------------------------------
 * Name             : Pacific Thai
 * Student Number   : s3429648
 * -----------------------------------------------------------------------------
  * Using skeleton code provided by Paul Miller
 */

#include "main_menu.h"
#include "add_player_window.h"
#include "game_window.h"
#include "player_selection_window.h"

#pragma once

namespace draughts
{
  namespace nc_controller
  {
    class controller;
  }
  namespace model
  {
    class model;
  }
  namespace ncview
  {
    class ui
    {
      draughts::nc_controller::controller * the_controller;
      draughts::model::model * the_model;
      ui(void);
      static std::unique_ptr<ui> instance;
      public:
        void main_menu(void);
        void add_player(void);
        void play_game(void);
        void show_game_window(player_pair);
        static ui* get_instance(void);
        static void delete_instance(void);
        virtual ~ui(void);
    };
  }
}
