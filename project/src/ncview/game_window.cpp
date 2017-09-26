
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

#include "game_window.h"
#include "../model/model.h"

draughts::ncview::game_window::game_window(const player_pair & theplayers)
    : players(theplayers), quit(false)
{
}

void draughts::ncview::game_window::activate(void)
{
  while(!quit)
  {
    int playernum = EOF;
    try
    {
      display_board();
      playernum = themodel->get_current_player();
      std::cout << "It is " << themodel->get_player_name(playernum)
          << "'s turn (" << themodel->get_current_player_token()
          << "), their score is " << themodel->get_player_score(playernum)
          << std::endl;
    }
    catch(std::exception & ex)
    {
      std::cerr << ex.what() << std::endl;
      return;
    }
    try
    {
      std::pair<std::pair<int,int>,std::pair<int,int>> move_coords;
      move_coords = get_move_input();
      themodel->make_move(playernum,
                          move_coords.first.first,  move_coords.first.second,
                          move_coords.second.first, move_coords.second.second);
    }
    catch(std::exception& ex)
    {
      std::cerr << ex.what() << std::endl;
    }
  }
}

std::pair<std::pair<int,int>, std::pair<int,int>>
    draughts::ncview::game_window::get_move_input(void)
{
  std::string input;
  std::pair<std::pair<int,int>,std::pair<int,int>> move;
  std::pair<int,int> start;
  std::pair<int,int> end;

  bool validInput = false;
  /* NOTE: Changed from:
   * std::cout << "Please enter your next move: ";
   * get_input(input);
   * get_input()'s parameter is a string prompt, so we have no idea why input
   * was passed into it and why the prompt was placed before it
   */

  while (!validInput) {
    input = get_input("Please enter your next move, Format = x,y-x,y: ");
    validInput = validate_move_input(input);
  }

  std::vector<std::string> moves;
  std::vector<std::string> coords;
  boost::split(moves, input, [](char ch) { return ch == '-'; });

  start = strtocoord(moves[0]);
  end = strtocoord(moves[1]);
  move = std::make_pair(start, end);
  return move;
}

void draughts::ncview::game_window::print_top_row(void)
{
  int xcount;
  std::cout << " ";
  for (xcount = 0; xcount < themodel->get_width(); ++xcount)
  {
    std::cout << " " << xcount + 1 << " |";
  }
  std::cout << std::endl;
}

std::pair<int,int> draughts::ncview::game_window::strtocoord(
    const std::string& input)
{
  int x, y;

  std::vector<std::string> parts;
  boost::split(parts, input, [](char ch) { return ch == ','; });

  x = stoi(parts[0]);
  y = stoi(parts[1]);

  return std::make_pair(x,y);
}

void draughts::ncview::game_window::print_row(int rownum)
{
  int xcount;
  std::cout << rownum + 1;
  for(xcount = 0; xcount < themodel->get_width(); ++xcount)
  {
    std::cout << " " << themodel->get_token(rownum + 1, xcount + 1) << " |";
  }
  std::cout << std::endl;
}

void draughts::ncview::game_window::print_line(int numdashes)
{
  int count;
  for(count = 0; count < numdashes; ++count)
  {
    std::cout << '-';
  }
}

void draughts::ncview::game_window::display_board(void)
{
  int ycount;

  print_top_row();
  print_line(themodel->get_width() * 4);
  std::cout << std::endl;

  for(ycount = 0; ycount < themodel->get_height(); ycount++)
  {
    print_row(ycount);
    print_line(themodel->get_width() * 4);
    std::cout << std::endl;
  }
}

// #################### Validate move input ####################
bool draughts::ncview::game_window::validate_move_input(const std::string &input){
  bool validMove = false;
  std::regex moveCheck(MOVE_REGEX);
  std::string invalidMove = "Invalid Move, Numbers for x and y must be between 1-8";

  if (std::regex_match(input, moveCheck))
    validMove = true;
  else
    std::cout << invalidMove << std::endl;

  return validMove;
}
