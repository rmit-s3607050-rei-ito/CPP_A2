
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

draughts::ncview::game_window::game_window(const player_pair & theplayers)
  : players(theplayers), quit(false)
{
}

// #################### Public functions ####################
void draughts::ncview::game_window::activate(void)
{
  bool validMove = false;       // Move is of format x,y-x,y
  bool mustJump = false;        // Player must make their token jump
  bool isDraw = false;          // Game didnt end in a draw
  //bool jumpMade = false;        // Jump made, check for extra jumps
  moves move;                   // move to make

  while(!quit)
  {
    int playernum = EOF;
    try
    {
      display_board();
      playernum = themodel->get_current_player();
      // Print out message on whose turn it is, their token type and their score
      std::cout << "It is " << themodel->get_player_name(playernum)
          << "'s turn (" << themodel->get_current_player_token()
          << "), their score is " << themodel->get_player_score(playernum)
          << std::endl;
      // Check if a jump must be made and reset the fact one has been made if made
      mustJump = themodel->check_forced_jump();

      // Jump (2 cells diagonally)
      if(mustJump) {
        std::cout << "Forced jump! A jump must be made" << std::endl;
        // Get number of available options for the forced jump
        std::list<moves> forcedMoves = themodel->get_forced_jumps();

        // Only 1 forced move, automatically select first token
        if(forcedMoves.size() == 1)
          move = forcedMoves.front();
        // More than one available option, player choses which move they want
        else
          move = get_jump_input(forcedMoves);

        // Make a jump using the obtained move
        themodel->make_move(move.first.first, move.first.second,
                            move.second.first, move.second.second);
        // Print out jump that has been made for clearer visualization
        std::cout << "Token: " << move.first.first << "," << move.first.second <<
               " ended at: " << move.second.first << "," << move.second.second <<
        std::endl;

        // Recheck if there are any more forced jumps, if so loop again using same player
        if (!themodel->check_forced_jump())
          themodel->swap_current_player();
      }
      // Normal move (1 cell diagonally at a time)
      else {
        // Get input for a normal move for when there are no forced jumps
        while (!validMove) {
          move = get_move_input();
          validMove = themodel->make_move(move.first.first, move.first.second,
                                          move.second.first, move.second.second);
        }
        themodel->swap_current_player();  // Switch to next player after move made
        validMove = false;                // Reset valid move for next player
      }

      // Check if the game has ended or not
      if(themodel->game_draw()) {
        quit = true;
        isDraw = true;
      }
      else
        quit = themodel->game_ended();
    }
    catch(std::exception & ex) {
      std::cerr << ex.what() << std::endl;
      return;
    }
  }

  // Show board's final state when game ended
  display_board();

  // Obtain winner once game has ended
  if(!isDraw)
    themodel->get_winner();
  else
    themodel->get_draw_message();
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

// #################### Print functions ####################
void draughts::ncview::game_window::print_top_row(void)
{
  int xcount;
  std::cout << " ";
  for (xcount = 0; xcount < themodel->get_width(); ++xcount)
    std::cout << " " << xcount + 1 << " |";

  std::cout << std::endl;
}

void draughts::ncview::game_window::print_row(int rownum)
{
  int xcount;
  std::cout << rownum + 1;
  for(xcount = 0; xcount < themodel->get_width(); ++xcount)
  {
    std::string token;
    // When the token is an 'x' or 'X' color it red
    if (themodel->get_token(rownum + 1, xcount + 1) == 'x'
    ||themodel->get_token(rownum + 1, xcount + 1) == 'X') {
      token = "\033[31m";
      token.append(1, themodel->get_token(rownum + 1, xcount + 1));
      token.append("\033[0m");
    }
    // Color it white for any other token
    else
      token = themodel->get_token(rownum + 1, xcount + 1);

    // Separate tokens using spaces and delimeter '|'
    std::cout << " " << token << " |";
  }
  std::cout << std::endl;
}

void draughts::ncview::game_window::print_line(int numdashes)
{
  int count;
  for(count = 0; count < numdashes; ++count)
    std::cout << '-';
}

void draughts::ncview::game_window::print_possible_jumps(std::list<moves> allMoves) {
  std::cout << "Choose one of the following moves:" << std::endl;
  for (moves move : allMoves) {
    std::cout << " Token: " << move.first.first << "," << move.first.second <<
              " | Land at: " << move.second.first << "," << move.second.second <<
    std::endl;
  }
}

// #################### Retrieving input from user ####################
moves draughts::ncview::game_window::get_move_input(void)
{
  std::string input;                        // String read in
  moves moveCoords;                         // Result movement
  coordinates start, end;                   // Start and end coordinates
  std::vector<std::string> moves, coords;   // String result to parse into moves

  // Loop ensuring that user enters input in correct format
  bool validInput = false;
  while (!validInput) {
    input = get_input("Please enter your next move, Format = row,col-row,col");
    validInput = validate_move_input(input);
  }

  // Split input and store into moves based on delimeter '-'
  boost::split(moves, input, [](char ch) { return ch == '-'; });

  // Convert both start and end into move coordinates and return as pair output
  start = strtocoord(moves[0]);
  end = strtocoord(moves[1]);
  moveCoords = std::make_pair(start, end);

  return moveCoords;
}

moves draughts::ncview::game_window::get_jump_input(std::list<moves> jumpList)
{
  moves moveCoords;                  // Output move coordinates
  bool validJump = false;            // Looping until a valid jump been chosen
  std::list<moves>::iterator inList; // Check if move is a selectable move

  // List to player the possible jumps
  print_possible_jumps(jumpList);

  // Loop receiving input to see whether player selected a possible jump
  while (!validJump) {
    // Retrieve move coordinates via get_move_input() from player
    moveCoords = get_move_input();

    // Search in the list of jumps to see if selected coordinates are in there
    inList = std::find(jumpList.begin(), jumpList.end(), moveCoords);

    // Exit and return when found
    if(inList != jumpList.end()) {
      validJump = true;
      std::cout << "Valid jump chosen\n";
    } else
      print_possible_jumps(jumpList);
  }

  return moveCoords;
}

coordinates draughts::ncview::game_window::strtocoord(const std::string& input)
{
  int x, y;

  std::vector<std::string> parts;
  boost::split(parts, input, [](char ch) { return ch == ','; });

  x = stoi(parts[0]);
  y = stoi(parts[1]);

  return std::make_pair(x,y);
}

// #################### Input validation ####################
bool draughts::ncview::game_window::validate_move_input(const std::string &input){
  bool validMove = false;
  std::regex moveCheck(REGULAR_MOVE_REGEX);
  std::string invalidMove = imMsg +
    "Coordinates = (across,down). Values between 1-8, separated by ','";

  if (std::regex_match(input, moveCheck))
    validMove = true;
  else
    std::cout << invalidMove << std::endl;

  return validMove;
}
