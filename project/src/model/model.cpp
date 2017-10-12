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

#include "model.h"

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;

// Private function, input validation: checking if player is already in list
void draughts::model::model::player_exists(const std::string &pname)
{
  // Iterator through player list
  auto player = player_list.begin();
  // Name of player being checked and the error message for exception case
  std::string playerName = "";
  std::string existingPlayerMessage = "";

  while (player != player_list.end()) {
    playerName = player->second;

    // Throw exception when player has not been found
    if (pname == playerName) {
      existingPlayerMessage = pname + " already exists in the roster";
      throw existingPlayerMessage;
    }
    player++;
  }
}

// Constructor for model, player types and none registered
draughts::model::model::model(void) : red(RED), white(WHITE), player_count(0)
{
}

// #################### Model instance related functions ####################
draughts::model::model * draughts::model::model::get_instance(void)
{
  if (instance == nullptr)
    instance = std::unique_ptr<model>(new model);

  return instance.get();
}

void draughts::model::model::delete_instance(void)
{
  instance.reset(nullptr);
}

draughts::model::model::~model(void)
{
}

// #################### Game related functions ####################
void draughts::model::model::start_game(int plr1, int plr2)
{
  // 1. Setting up random generation for player selection
  std::random_device rd; // 1a. Create a random device
  std::default_random_engine dre(rd()); // 1b. Create a random engine, device param
  std::uniform_int_distribution<int> uid(MIN, MAX); // 1c. Create the range of values
  int startingPlayer = uid(dre); // 1d. Store the randomly generated number

  // 2. Initialize game board
  game_board.init_board();

  // 3. Initialize/Reset players, set starting piece count and score to 0
  red.initialize();
  white.initialize();

  // 4. Randomly decide which player is assigned to 'x' and 'o' pieces
  if (startingPlayer == 0) {
    red.set_id(plr1);
    white.set_id(plr2);
  }
  else {
    red.set_id(plr2);
    white.set_id(plr1);
  }

  // Given the rules, the player with x pieces always go first
  current_player = &red;
}

void draughts::model::model::swap_current_player(void)
{
  if (current_player == &red)
    current_player = &white;
  else
    current_player = &red;
}

void draughts::model::model::make_move(int startx, int starty, int endx, int endy)
{
  // Same as get_piece: since array starts from 0, we need to minus 1 from input
  startx -= ARRAY_DIFF;
  starty -= ARRAY_DIFF;
  endx -= ARRAY_DIFF;
  endy -= ARRAY_DIFF;

  team player_team = current_player->get_team();
  // Determine whether score is to be updated or piece counts
  bool capturedToken = false;
  bool promotion = false;

  // 1. Catch when player selected same start and end positions
  if (startx == endx && starty == endy)
    throw std::string("Invalid move, start and end are the same");
  else { // 2. Check if player selected right piece
    game_board.check_valid_selection(player_team, startx, starty);
    // When right piece selected, check if they entered in a possible move
    game_board.check_valid_move(startx, starty, endx, endy);
  }

  // When all checks have been passed move the piece and swap players
  capturedToken = game_board.move_piece(startx, starty, endx, endy);
  // If move resulted in a piece being removed from the game
  if (capturedToken) {
    // Add 1 to score and reduce number of pieces for other player by 1
    current_player->increment_score();
    reduce_player_pieces();
  }
  // If move resulted in piece ending up at the opposite end of the board
  if (endx == X_START || endx == O_END) {
    // Try to promote the piece, nothing happens if piece is of king type
    promotion = game_board.promote_piece(endx, endy);
    // Add 1 to score if the piece has been successfully promoted
    if (promotion)
      current_player->increment_score();
  }
}

bool draughts::model::model::check_individual_jump(int x, int y)
{
  // Clear the list of all previous possible jumps and check for individual jump
  game_board.reset_jump_list();
  // Check if the piece at the particular spot can jump again
  return game_board.check_individual_jump(x, y);
}

bool draughts::model::model::check_all_forced_jumps(void)
{
  // Check if the current player is forced to make a jump
  team currentTeam = current_player->get_team();
  int num_pieces = current_player->get_num_pieces();

  return game_board.check_all_possible_jumps(currentTeam, num_pieces);
}

// #################### Game state ####################
bool draughts::model::model::game_draw(void)
{
  bool possibleMove;
  // Check both players, their piece count
  int xPlayerTokens, oPlayerTokens;
  xPlayerTokens = red.get_num_pieces();
  oPlayerTokens = white.get_num_pieces();

  // Check if any piece in the entire game can move
  possibleMove = game_board.check_all_possible_moves(xPlayerTokens,
    oPlayerTokens);

  // When there are still moves available it is not a draw
  if (possibleMove)
    return false;

  return true;
}

bool draughts::model::model::game_ended(void)
{
  int xPlayerTokens, oPlayerTokens;
  xPlayerTokens = red.get_num_pieces();
  oPlayerTokens = white.get_num_pieces();

  // If either has 0, game has ended with a winner
  if (xPlayerTokens == 0 || oPlayerTokens == 0)
    return true;

  return false;
}

void draughts::model::model::get_winner(void)
{
  int wID, wScore;
  std::string wName;

  // At the end, turn swapped to loser player, swap it back to winner
  swap_current_player();

  wID = current_player->get_id();
  wName = get_player_name(wID);
  wScore = get_player_score(wID);

  // Prints out message of the winner of the game
  std::cout << std::endl << GAME_OVER_TEXT << std::endl;
  std::cout << "The winner of this game is: " << std::endl;
  std::cout << "[" << wName << "] with a score of: " << wScore << std::endl;
  std::cout << TO_MAIN_MENU_TEXT << std::endl << std::endl;
}

void draughts::model::model::get_draw_message(void)
{
  std::cout << std::endl << GAME_OVER_TEXT << std::endl;
  std::cout << "There are no more possible moves left on the board"
    << std::endl;
  std::cout << "The game ended in a draw!" << std::endl;
  std::cout << TO_MAIN_MENU_TEXT << std::endl << std::endl;
}

// #################### Player related functions ####################
int draughts::model::model::get_player_count(void)
{
  return player_count;
}

int draughts::model::model::get_player_score(int playernum)
{
  /* NOTE: Assumes only scores are tracked for the two players in game, not players
   * present in list. Compares ID with playernum, return their matching score */
  if (playernum == red.get_id())
    return red.get_score();
  else
    return white.get_score();
}

int draughts::model::model::get_current_player(void)
{
  return current_player->get_id(); // Return ID of current player
}

std::string draughts::model::model::get_player_name(int id)
{
  // Iterator used to loop through map
  auto player = player_list.begin();

  // Key, value pair for each map entry
  int player_id = 0;
  std::string playerName = "[ERROR] - Player could not be found";

  // Iterate to find player
  while (player != player_list.end()) {
    player_id = player->first;

    if (id == player_id) {
      playerName = player->second;
      break;
    }
    // Move onto next player in map
    player++;
  }

  // If not found error message is returned as name is not overwritten
  return playerName;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) const
{
  return player_list;
}

void draughts::model::model::add_player(const std::string& p)
{
  /* Check if player exists or not if so exception is thrown */
  player_exists(p);

  // Get total number of players to determine ID to allocate
  int pID = get_player_count();

  // Create player name/id pair to add to map
  std::pair<int, std::string> player(pID, p);

  // Add player to map and increment total number of players registered by 1
  player_list.insert(player);
  player_count++;
}

char draughts::model::model::get_current_player_piece()
{
  /* Return char symbol of piece using inline if statement
   * 1. Get piece type from current player
   * 2. If it is N_CROSS return N_X_TOKEN ('x')
   * 3. Otherwise return N_O_TOKEN ('o')
   */
  team currentTeam = current_player->get_team();
  if (currentTeam == RED)
    return RED_N_PIECE;
  else
    return WHITE_N_PIECE;
}

void draughts::model::model::reduce_player_pieces()
{
  if (current_player == &red)
    white.reduce_piece_count();
  else
    red.reduce_piece_count();
}

// #################### Board related functions ####################
int draughts::model::model::get_width(void)
{
  return game_board.get_width();
}

int draughts::model::model::get_height(void)
{
  return game_board.get_height();
}

char draughts::model::model::get_piece(int x ,int y)
{
  // Since array starts from 0, we need to minus 1 from input
  int xPos = x - ARRAY_DIFF;
  int yPos = y - ARRAY_DIFF;

  return game_board.get_piece(xPos, yPos);
}

std::list<moves> draughts::model::model::get_forced_jumps(void)
{
  return game_board.get_forced_jumps();
}
