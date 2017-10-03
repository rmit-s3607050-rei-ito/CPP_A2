
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

#include "model.h"

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;

// Private function, input validation: checking if player is already in list
bool draughts::model::model::player_exists(const std::string &pname)
{
  /* NOTE: Essentially the same logic as get_player_name, so majority of
   * commenting has been left out */

  // Flag to determine whether player exists
  bool found = false;
  auto player = playerList.begin();
  std::string playerName = "";

  while(player != playerList.end()){
    playerName = player->second;

    if(pname == playerName) {
      found = true;
      break;
    }
    player++;
  }

  return found;
}

// Constructor for model, player types and none registered
draughts::model::model::model(void) : red(RED), white(WHITE), playerCount(0)
{
}

// #################### Model instance related functions ####################
draughts::model::model * draughts::model::model::get_instance(void)
{
  if(instance == nullptr)
  {
    instance = std::unique_ptr<model>(new model);
  }
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
  // All of these ensure replayability, refreshing game parameters every time
  srand(time(NULL));

  // 2. Initialize game board
  gameBoard.init_board();

  // 3. Initialize/Reset players, set starting token count and score to 0
  red.initialize();
  white.initialize();

  // 5. Randomly decide which player is assigned to 'x' and 'o' tokens
  int startingPlayer = rand() % 2;
  if (startingPlayer == 0) {
    red.set_id(plr1);
    white.set_id(plr2);
  } else {
    red.set_id(plr2);
    white.set_id(plr1);
  }

  // Given the rules, the player with x tokens always go first
  currentPlayer = &red;
}

void draughts::model::model::swap_current_player(void){
  if(currentPlayer == &red)
    currentPlayer = &white;
  else
    currentPlayer = &red;
}

// bool draughts::model::model::make_move(int startx, int starty, int endx, int endy)
// {
//   // Same as get_token: since array starts from 0, we need to minus 1 from input
//   startx -= ARRAY_DIFF;
//   starty -= ARRAY_DIFF;
//   endx -= ARRAY_DIFF;
//   endy -= ARRAY_DIFF;
//
//   type playerType = currentPlayer->get_type();
//   // Validation for both start and end coordinates
//   bool validSelection = false;        // (startx, starty)
//   bool validMove = false;             // (endx, endy)
//   // Determine whether score is to be updated or token counts
//   bool capturedToken = false;
//   bool promotion = false;
//
//   // 1. Catch when player selected same start and end positions
//   if (startx == endx && starty == endy) {
//     std::cout << "Invalid move, start and end are the same." << std::endl;
//     return false;
//   }
//   else { // 2. Check if player selected right token
//     validSelection = gameBoard.check_valid_selection(playerType, startx, starty);
//
//     // When right token selected, check if they entered in a possible move
//     if (validSelection)
//       validMove = gameBoard.check_valid_move(startx, starty, endx, endy);
//   }
//
//   // When all checks have been passed move the token and swap players
//   if(validMove) {
//     // Move the token
//     capturedToken = gameBoard.move_token(startx, starty, endx, endy);
//     // If move resulted in a token being removed from the game
//     if(capturedToken) {
//       // Add 1 to score and reduce number of tokens for other player by 1
//       currentPlayer->increment_score();
//       reduce_player_tokens();
//     }
//     // If move resulted in token ending up at the opposite end of the board
//     if (endx == X_START || endx == O_END) {
//       // Try to promote the token
//       promotion = gameBoard.promote_token(endx, endy);
//       // Add 1 to score if the token has been successfully promoted
//       if (promotion)
//         currentPlayer->increment_score();
//     }
//   }
//   return validMove;
// }

// bool draughts::model::model::check_forced_jump(void) {
//   // Check if a player is forced to make a jump
//   type currentType = currentPlayer->get_type();
//   int numTokens = currentPlayer->get_num_tokens();
//
//   return gameBoard.check_all_possible_jumps(currentType, numTokens);
// }
//
// bool draughts::model::model::game_draw(void) {
//   bool possibleMove;
//   // Check both players, their token count
//   int xPlayerTokens, oPlayerTokens;
//   xPlayerTokens = red.get_num_tokens();
//   oPlayerTokens = white.get_num_tokens();
//
//   // Check if any piece in the entire game can move
//   possibleMove = gameBoard.check_all_possible_moves(xPlayerTokens, oPlayerTokens);
//
//   // When there are still moves available it is not a draw
//   if(possibleMove)
//     return false;
//
//   return true;
// }
//
// bool draughts::model::model::game_ended(void) {
//   int xPlayerTokens, oPlayerTokens;
//   xPlayerTokens = red.get_num_tokens();
//   oPlayerTokens = white.get_num_tokens();
//
//   // If either has 0, game has ended with a winner
//   if (xPlayerTokens == 0 || oPlayerTokens == 0)
//     return true;
//
//   return false;
// }
//
// void draughts::model::model::get_winner(void)
// {
//   int wID, wScore;
//   std::string wName;
//
//   // At the end, turn swapped to loser player, swap it back to winner
//   swap_current_player();
//
//   wID = currentPlayer->get_id();
//   wName = get_player_name(wID);
//   wScore = get_player_score(wID);
//
//   // Prints out message of the winner of the game
//   std::cout << std::endl << GAME_OVER_TEXT << std::endl;
//   std::cout << "The winner of this game is: " << std::endl;
//   std::cout << "[" << wName << "] with a score of: " << wScore << std::endl;
//   std::cout << TO_MAIN_MENU_TEXT << std::endl << std::endl;
// }

// void draughts::model::model::get_draw_message(void) {
//   std::cout << std::endl << GAME_OVER_TEXT << std::endl;
//   std::cout << "There are no more possible moves left on the board" << std::endl;
//   std::cout << "The game ended in a draw!" << std::endl;
//   std::cout << TO_MAIN_MENU_TEXT << std::endl << std::endl;
// }

// #################### Player related functions ####################
int draughts::model::model::get_player_count(void)
{
  return playerCount;
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
  return currentPlayer->get_id(); // Return ID of current player
}

std::string draughts::model::model::get_player_name(int id)
{
  // Iterator used to loop through map
  auto player = playerList.begin();

  // Key, value pair for each map entry
  int playerID = 0;
  std::string playerName = "[ERROR] - Player could not be found";

  // Iterate to find player
  while(player != playerList.end()){
    playerID = player->first;

    if(id == playerID) {
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
  return playerList;
}

/*  NOTE: return type changed from void to bool, to determine whether add player
 * was successful, false = could not add new player, true = added to list */
bool draughts::model::model::add_player(const std::string& p)
{
  // Immediately exit if player already present in map, otherwise proceed
  if(player_exists(p))
    return false;

  // Get total number of players to determine ID to allocate
  int pID = get_player_count();

  // Create player name/id pair to add to map
  std::pair<int, std::string> player(pID, p);

  // Add player to map and increment total number of players registered by 1
  playerList.insert(player);
  playerCount++;

  return true;
}

char draughts::model::model::get_current_player_token() {
  /* Return char symbol of token using inline if statement
   * 1. Get token type from current player
   * 2. If it is N_CROSS return N_X_TOKEN ('x')
   * 3. Otherwise return N_O_TOKEN ('o')
   */
  team currentTeam = currentPlayer->get_team();
  if(currentTeam == RED)
    return RED_N_PIECE;
  else
    return WHITE_N_PIECE;
}

void draughts::model::model::reduce_player_tokens() {
  if(currentPlayer == &red)
    white.reduce_token_count();
  else
    red.reduce_token_count();
}

// #################### Board related functions ####################
int draughts::model::model::get_width(void)
{
  return gameBoard.get_width();
}

int draughts::model::model::get_height(void)
{
  return gameBoard.get_height();
}

char draughts::model::model::get_token(int x ,int y)
{
  // Since array starts from 0, we need to minus 1 from input
  int xPos = x - ARRAY_DIFF;
  int yPos = y - ARRAY_DIFF;

  return gameBoard.get_token(xPos, yPos);
}

// std::list<moves> draughts::model::model::get_forced_jumps(void) {
//   return gameBoard.get_forced_jumps();
// }
