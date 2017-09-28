
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

// Constructor for model, assign default width, height, start with no players
draughts::model::model::model(void) : width(WIDTH), height(HEIGHT), playerCount(0)
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

  // 1. initialize board
  init_board();

  // 2. Allocate type for players
  xPlayer.set_type(N_CROSS);
  oPlayer.set_type(N_CIRCLE);

  // 3. Randomly decide which player is assigned to 'x' and 'o' tokens
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
  //std::cout << "#################### Received: ####################" << std::endl;
  //std::cout << "PlayerNum: " << playernum << std::endl;
  //std::cout << "     Move: " << startx << " , " << starty << std::endl;
  //std::cout << "       To: " << endx << " , " << endy << std::endl;

  // 1. Check if player selected a token that belongs to them
  if (startx == endx && starty == endy) {
    std::cout << "Invalid move, start and end are the same." << std::endl;
    return false;
  }
  else if (currentPlayer->get_type() == N_CROSS) {
    if (board[startx][starty].get_type() == N_CROSS) {
      // check if piece can move
      return true;
    } else if (board[startx][starty].get_type() == K_CROSS) {
      return true;
    } else {
      std::cout << "Invalid start, other player or empty square" << std::endl;
      return false;
    }
  } else {
    if (board[startx][starty].get_type() == N_CIRCLE) {
      return true;
    } else if (board[startx][starty].get_type() == K_CIRCLE) {
      return true;
    } else {
      std::cout << "Invalid start, other player or empty square" << std::endl;
      return false;
    }
  }

  

  return false;

  //currentPlayer.validate_selection(startx, starty);
}

// #################### Player related functions ####################
/*  NOTE: return type changed from void to bool, to determine whether add player
 * was successful, false = could not add new player, true = added to list */
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
  return (currentPlayer->get_type() == N_CROSS) ? N_X_TOKEN : N_O_TOKEN;
}

// #################### Board related functions ####################
void draughts::model::model::init_board(void) {
  for(int row = 0; row < WIDTH; row++) {
    for (int col = 0; col < HEIGHT; col++) {
      // Fill gaps between tokens with empty spaces
      if(((col + row) % 2) == 0) {
        board[row][col].set_type(EMPTY);
      } else {
        // Initialize middle rows (3 and 4) as empty
        if (row > X_END && row < O_START)
          board[row][col].set_type(EMPTY);
        // Initialize 'x' tokens
        else if (row <= X_END)
          board[row][col].set_type(N_CROSS);
        // Initialize 'o' tokens
        else
          board[row][col].set_type(N_CIRCLE);
      }
    }
  }
}

int draughts::model::model::get_width(void)
{
  return width;
}

int draughts::model::model::get_height(void)
{
  return height;
}

char draughts::model::model::get_token(int x ,int y)
{
  // Since array starts from 0, we need to minus 1 from input
  int xPos = x-1;
  int yPos = y-1;

  token gameToken = board[xPos][yPos];
  return gameToken.print_token();
}
