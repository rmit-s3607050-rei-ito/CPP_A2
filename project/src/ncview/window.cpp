
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
#include "ui.h"
#include "../model/model.h"
#include "../nc_controller/command.h"

draughts::ncview::window::window(void)
  : view(draughts::ncview::ui::get_instance()),
  the_model(draughts::model::model::get_instance())
{
}

std::string draughts::ncview::window::get_input(const std::string& prompt)
{
  std::string input;
  bool success = false;
  while(!success) {
    std::cout << prompt + ": ";
    try {
      std::getline(std::cin, input);
      if(input.empty()) {
        if(std::cin.eof()) {
          std::cin.clear();
        }
        throw input_cancelled();
      }
      success = true;
    }
    catch(input_cancelled & ic) {
      throw;
    }
  }
  return input;
}
