
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

#include "add_player_window.h"
#include "ui.h"
#include "../model/model.h"
#include "../nc_controller/command.h"

void draughts::ncview::add_player_window::activate(void)
{
  std::string name;
  bool success = false;
  std::string recv;

  while(!success){
    try {
      name = window::get_input("Please enter the name for the new player");
      draughts::model::model * themodel = draughts::model::model::get_instance();
      success = themodel->add_player(name);
    }
    catch(std::exception& ex)
    {
      std::cerr << ex.what() << std::endl;
      return;
    }
    if (!success)
      std::cout << name << " already exists in the roster" << std::endl;
  }
  std::cout << "Successfully added " << name << " to player roster." << std::endl;
  std::cout << "Press <enter> to continue: " << std::endl;
  std::cin.get();
  view->main_menu();
}
