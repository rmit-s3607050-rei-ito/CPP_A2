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

#include "menu.h"
#include "../nc_controller/command.h"

draughts::ncview::menu::menu(const std::string & theTitle,
  const std::vector<std::string>& text,
  draughts::ncview::command_vector commands) : title(theTitle), menu_text(text),
  menu_commands(std::move(commands))
{
}

void draughts::ncview::menu::activate(void)
{
  std::cout << title << std::endl;
  std::string underline(title.size(), '-');
  std::cout << underline << std::endl;
  int count;
  std::size_t end;
  int choice;

  std::string line;
  bool success = false;
  for(count = 0; count < static_cast<int>(menu_text.size()); ++count) {
    std::cout << count + 1 << ") " << menu_text[count] << std::endl;
  }
  while(!success) {
    try {
      std::cout << "Please enter your choice: ";
      std::getline(std::cin, line);
      choice = std::stoi(line, &end);
      if (end != line.size() || choice <= 0 ||
          choice > static_cast<int>(menu_text.size())) {
        std::cerr << "error: invalid input. Please try again." << std::endl;
      }
      else {
        success = true;
      }
    }
    catch(std::exception& ex) {
      std::cerr << "error: invalid input. Please try again."
          << std::endl;
      /* if the user pressed ctrl-d, we have to remove the
       * buffer input
       */
      if(std::cin.eof())
        std::cin.clear();
    }
  }
  (*(menu_commands[choice-1]))();
}


draughts::ncview::menu::menu(void)
{
}

void draughts::ncview::menu::set_title(const std::string& newTitle)
{
  title = newTitle;
}

void draughts::ncview::menu::set_text( const std::vector<std::string>& newText)
{
  menu_text = newText;
}

void draughts::ncview::menu::set_actions(command_vector& vec)
{
  menu_commands = std::move(vec);
}
