#include "model.h"

/* Model related functions */
// Pointer to model instance that is created when program started
std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;

// Constructor for model, assign default width, height, start with no players
draughts::model::model::model(void) : width(WIDTH), height(HEIGHT), playerCount(0)
{
}

draughts::model::model * draughts::model::model::get_instance(void)
{
  // Create new instance to model
  if(instance == nullptr)
  {
    instance = std::unique_ptr<model>(new model);
  }
  return instance.get();
}

int draughts::model::model::get_player_score(int playernum)
{
  // Compare the ID of playernum with each player, return their matching score
  if (playernum == player1)
    return p1Score;
  else
    return p2Score;
}

void draughts::model::model::start_game(int plr1, int plr2)
{
  // Create random seed
  srand(time(NULL));

  // 1. Assign player1 to plr1 and player2 to plr2
  player1 = plr1;
  player2 = plr2;

  // 2. Initialize p1 and p2's scores as 0
  p1Score = 0;
  p2Score = 0;

  // 1. Randomly decide which player will go first (pseudo random)
  int startingPlayer = rand() % 2;
  if (startingPlayer == 0)
    currentPlayer = player1;
  else
    currentPlayer = player2;

}

int draughts::model::model::get_winner()
{
  return EOF;
}

std::string draughts::model::model::get_player_name(int id)
{
  // Iterator used to loop through map
  auto player = playerList.begin();

  // Key, value pair for each map entry
  int playerID = 0;
  std::string playerName = "[ERROR] - Player could not be found";

  std::cout << "Using id: " << id << std::endl;

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

char draughts::model::model::get_token(int x ,int y)
{
  return '\0';
}

void draughts::model::model::make_move(int playernum,
        int startx, int starty, int endx, int endy)
{
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

int draughts::model::model::get_current_player(void)
{
  return currentPlayer;
}

std::map<int, std::string> draughts::model::model::get_player_list(void)
    const
{
  return playerList;
}

void draughts::model::model::delete_instance(void)
{
  instance.reset(nullptr);
}

int draughts::model::model::get_player_count()
{
  return playerCount;
}

int draughts::model::model::get_width()
{
  return width;
}

int draughts::model::model::get_height()
{
  return height;
}

draughts::model::model::~model(void)
{
}
