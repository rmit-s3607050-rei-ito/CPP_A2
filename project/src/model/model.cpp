
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

  // 1. Assign id to players and initialize type. Internally set up tokens
  player1.initialize(plr1, p1);
  player2.initialize(plr2, p2);

  // 2. Randomly decide which player will go first (pseudo random)
  int startingPlayer = rand() % 2;
  if (startingPlayer == 0)
    currentPlayer = &player1;
  else
    currentPlayer = &player2;

}

int draughts::model::model::get_winner()
{
  return EOF;
}

void draughts::model::model::make_move(int playernum, int startx, int starty,
                                                      int endx, int endy)
{
  
}

// #################### Player related functions ####################
/*  NOTE: return type changed from void to bool, to determine whether add player
 * was successful, false = could not add new player, true = added to list */
int draughts::model::model::get_player_count()
{
 return playerCount;
}

int draughts::model::model::get_player_score(int playernum)
{
  /* NOTE: Assumes only scores are tracked for the two players in game, not players
   * present in list. Compares ID with playernum, return their matching score */
  if (playernum == player1.get_player_ID())
    return player1.get_player_score();
  else
    return player2.get_player_score();
}

int draughts::model::model::get_current_player(void)
{
  // Return ID of current player
  return currentPlayer->get_player_ID();
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

// #################### Board related functions ####################
int draughts::model::model::get_width()
{
  return width;
}

int draughts::model::model::get_height()
{
  return height;
}

char draughts::model::model::get_token(int x ,int y)
{
  int xPos, yPos;

  std::list<token> p1Tokens = player1.get_tokens();
  std::list<token> p2Tokens = player2.get_tokens();

  // Look for token in list of tokens for both players
  for(token t : p1Tokens) {
    xPos = t.get_x_pos();
    yPos = t.get_y_pos();

    if(xPos == x && yPos == y)
      return t.print_token();
  }

  for(token t : p2Tokens) {
    xPos = t.get_x_pos();
    yPos = t.get_y_pos();

    if(xPos == x && yPos == y)
      return t.print_token();
  }

  // Return blank when token not found
  return EMPTY;
}
