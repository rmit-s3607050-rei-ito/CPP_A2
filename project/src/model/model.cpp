
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

// Constructor for model, assign default width/height, player types and none registered
draughts::model::model::model(void) : xPlayer(N_CROSS), oPlayer(N_CIRCLE),
                                      playerCount(0)
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
  // Create random seed
  srand(time(NULL));

  // Randomly decide which player is assigned to 'x' and 'o' tokens
  int startingPlayer = rand() % 2;
  if (startingPlayer == 0) {
    xPlayer.set_id(plr1);
    oPlayer.set_id(plr2);
  } else {
    xPlayer.set_id(plr2);
    oPlayer.set_id(plr1);
  }

  // Given the rules, the player with x tokens always go first
  currentPlayer = &xPlayer;
}

void draughts::model::model::swap_current_player(void){
  if(currentPlayer == &xPlayer)
    currentPlayer = &oPlayer;
  else
    currentPlayer = &xPlayer;
}

int draughts::model::model::get_winner(void)
{
  return EOF;
}

bool draughts::model::model::make_move(int startx, int starty, int endx, int endy)
{
  // Same as get_token: since array starts from 0, we need to minus 1 from input
  startx -= ARRAY_DIFF;
  starty -= ARRAY_DIFF;
  endx -= ARRAY_DIFF;
  endy -= ARRAY_DIFF;

  bool validSelection = false;        // (startx, starty) validation
  bool validMove = false;             // (endx, endy) validation
  int scoreUpdate = 0;
  type playerType = currentPlayer->get_type();

  // NOTE: TEST EXTRA MOVE CHECK
  bool extraMove = false;

  // 1. Catch when player selected same start and end positions
  if (startx == endx && starty == endy) {
    std::cout << "Invalid move, start and end are the same." << std::endl;
    return false;
  }
  else { // 2. Check if player selected right token
    validSelection = gameBoard.check_valid_selection(playerType, startx, starty);

    // When right token selected, check if they entered in a possible move
    if (validSelection)
      validMove = gameBoard.check_valid_move(startx, starty, endx, endy);
  }

  // When all checks have been passed move the token and swap players
  if(validMove) {
    // Check if move resulted in a token being removed from the game
    scoreUpdate = gameBoard.move_token(startx, starty, endx, endy);

    if (endx == X_START || endx == O_END)
      scoreUpdate += gameBoard.promote_token(endx, endy);

    if (scoreUpdate > 1) {
      // Increase player's score by one since they removed a opponent's token
      currentPlayer->update_player_score(scoreUpdate);
      // Reduce number of tokens for other player by 1
      reduce_player_tokens(1);
      // TODO: check if any more moves can be made
      //extraMove = gameBoard.check_extra_moves(endx, endy);
    }
    // Switch player turn when done
    //if (!extraMove)
      //swap_current_player();
  }
  return validMove;
}

// #################### Player related functions ####################
int draughts::model::model::get_player_count(void)
{
  return playerCount;
}

int draughts::model::model::get_player_score(int playernum)
{
  /* NOTE: Assumes only scores are tracked for the two players in game, not players
   * present in list. Compares ID with playernum, return their matching score */
  if (playernum == xPlayer.get_id())
    return xPlayer.get_score();
  else
    return oPlayer.get_score();
}

int draughts::model::model::get_current_player(void)
{
  // Return ID of current player
  return currentPlayer->get_id();
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

std::map<int, std::string> draughts::model::model::get_player_list(void)
    const
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
  return (currentPlayer->get_type() == N_CROSS) ? N_X_TOKEN : N_O_TOKEN;
}

void draughts::model::model::reduce_player_tokens(int tokenChange) {
  if(currentPlayer == &xPlayer)
    oPlayer.reduce_num_tokens(tokenChange);
  else
    xPlayer.reduce_num_tokens(tokenChange);
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

  return gameBoard.get_token(xPos, yPos);;
}
