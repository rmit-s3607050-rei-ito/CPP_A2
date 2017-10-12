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

#include "ui.h"
#include "../nc_controller/controller.h"
#include "../model/model.h"
std::unique_ptr<draughts::ncview::ui> draughts::ncview::ui::instance = nullptr;

draughts::ncview::ui::ui(void)
  : the_controller(draughts::nc_controller::controller::get_instance()),
  the_model(draughts::model::model::get_instance())
{
}

void draughts::ncview::ui::main_menu(void)
{
  draughts::ncview::main_menu menu;
  menu.activate();
}

void draughts::ncview::ui::add_player(void)
{
  draughts::ncview::add_player_window newWin;
  newWin.activate();
}

void draughts::ncview::ui::play_game(void)
{
  try {
    player_selection_window newWin(the_model->get_player_list());
    newWin.activate();
  }
  catch(std::exception& ex) {
    std::cerr << "Exception: " << std::endl;
  }
}

draughts::ncview::ui* draughts::ncview::ui::get_instance(void)
{
  if(instance == nullptr)
    instance = std::unique_ptr<ui>(new ui());

  return instance.get();
}

void draughts::ncview::ui::delete_instance(void)
{
  instance.reset(nullptr);
}


void draughts::ncview::ui::show_game_window(draughts::ncview::player_pair
  players)
{
  game_window newWin(players);
  newWin.activate();
}

draughts::ncview::ui::~ui(void)
{
}
