
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
  std::string recv;
  std::string proceed;
  bool success = false;

  while(!success){
    try {
      name = window::get_input("Please enter the name for the new player");
      draughts::model::model * themodel = draughts::model::model::get_instance();
      themodel->add_player(name);
      success = true; // When adding player done, and no exception thrown proceed
    }
    // Catch exception that is thrown when new player could not be added
    catch(std::string errorMessage) {
      std::cout << errorMessage << std::endl;
    }
    catch(std::exception& ex)
    {
      std::cerr << ex.what() << std::endl;
      return;
    }
  }
  std::cout << "Successfully added " << name << " to player roster." << std::endl;
  std::cout << "Press <enter> to continue: " << std::endl;
  std::getline(std::cin, proceed); // Stored, ensure doesn't carry over to menu
  view->main_menu();
}
