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

#include "board.h"

// Constructor, calls initialization of board
draughts::model::board::board(void)
{
}

// #################### Initialization and validation ####################
void draughts::model::board::init_board()
{
  // Iterate through each cell in the board and fill it with a piece, or empty
  for(int row = 0; row < WIDTH; row++) {
    for (int col = 0; col < HEIGHT; col++) {
      // Fill gaps between pieces with empty spaces
      if(((col + row) % 2) == 0) {
        std::unique_ptr<piece> emptyCell = std::make_unique<empty>(NO_TEAM);
        gameBoard[row][col] = std::move(emptyCell);
      } else {
        // Initialize middle rows (3 and 4) as empty
        if (row > X_END && row < O_START) {
          std::unique_ptr<piece> emptyCell = std::make_unique<empty>(NO_TEAM);
          gameBoard[row][col] = std::move(emptyCell);
        } // Initialize red 'x' pieces
        else if (row <= X_END) {
          std::unique_ptr<piece> redPiece = std::make_unique<normal>(RED);
          gameBoard[row][col] = std::move(redPiece);
        // Initialize white 'o' pieces
        } else {
          std::unique_ptr<piece> whitePiece = std::make_unique<normal>(WHITE);
          gameBoard[row][col] = std::move(whitePiece);
        }
      }
    }
  }
}

void draughts::model::board::check_valid_selection(team playerTeam, int x, int y)
{
  team selectedTeam = gameBoard[x][y]->get_team(); // team of selected piece
  std::string invalidSelection = isMsg;

  // 1. Tried to select an empty cell
  if(selectedTeam == NO_TEAM) {
    invalidSelection += "No piece to move at this cell";
    throw invalidSelection;
  }
  // 2. Selected a piece that does not belong to them
  else if (playerTeam != selectedTeam) {
    invalidSelection += "This piece does not belong to you";
    throw invalidSelection;
  }
}

void draughts::model::board::check_valid_move(int x1, int y1, int x2, int y2)
{
  piece *currentPiece = gameBoard[x1][y1].get();   // Piece selected
  type currType = gameBoard[x1][y1]->get_type();   // Type of piece selected
  team currTeam = gameBoard[x1][y1]->get_team();   // Team selected to jump
  team landTeam = gameBoard[x2][y2]->get_team();   // Landing spot
  team jumpTeam;                                   // What was jumped over

  // String to throw as an exception
  std::string invalidMove = imMsg;

  // Coords of cell jumped over
  std::pair<int,int> jumpCoords;

  // Movement difference for row and column
  int rowMove = x2 - x1;
  int colMove = y2 - y1;

  // A. Check if piece was a normal type whether it tried to move backwards
  if(currType == NORMAL) {
    if(currTeam == RED && rowMove == UP) {
      invalidMove += "Red cannot move up with a 'x' piece";
      throw invalidMove;
    }
    else if(currTeam == WHITE && rowMove == DOWN) {
      invalidMove += "White cannot down up with a 'o' piece";
      throw invalidMove;
    }
  }

  // B. Check all other movement types with the piece itself
  currentPiece->check_valid_move(x1, y1, x2, y2);

  // C. Perform board checks comparing if a jump was to be made
  if (colMove == DOWN_JUMP || colMove == UP_JUMP) {
    // Get type of cell 1 position before jump (based on moving rowMove/colMove)
    jumpCoords = get_coordinates_of_jump(x1, y1, x2, y2);
    jumpTeam = gameBoard[jumpCoords.first][jumpCoords.second]->get_team();

    // Landing spot has no piece in it
    if (landTeam == NO_TEAM) {
      // 1. But then there is nothing to jump over to get to there
      if (jumpTeam == NO_TEAM) {
        invalidMove += "There is nothing you can jump over";
        throw invalidMove;
      }
      // 2. Player tried to jump over their own piece
      else if (currTeam == jumpTeam){
        invalidMove += "You cannot jump over your own piece";
        throw invalidMove;
      }
      // Third case is where piece jumped over is of opponent's = valid, no check
    }
  }

  // D. Landing spot has a piece in it (for moving and jumps)
  if(landTeam != NO_TEAM) {
    // 1. Piece at spot is their own:
    if(currTeam == landTeam)
      invalidMove += "A piece that belongs to you is there";
    // 2. Piece is of opponent's, to jump over must specify empty spot
    else
      invalidMove += "Enemy piece is there. To jump over choose an empty cell";

    throw invalidMove;
  }
}

// #################### Validation: Any possible moves left ####################
bool draughts::model::board::check_all_possible_moves(int xPieces, int oPieces)
{
  type currentType;
  int totalPieces = xPieces + oPieces;

  // Loop through entire board to check whether a move could be made
  for(int row = 0; row < WIDTH; row++) {
    for(int col = 0; col < HEIGHT; col++) {
      // Store current type of piece being iterated upon
      currentType = gameBoard[row][col]->get_type();
      // Only check possible moves for non-empty cells
      if(currentType != EMPTY) {
        totalPieces--;
        // Pieces in Column 0 can only move right
        if(col == FIRST_COL) {
          if(check_move_direction(row, col, RIGHT))
            return true;
        }
        // Pieces in Column 8 can only move left
        else if(col == LAST_COL) {
          if(check_move_direction(row, col, LEFT))
            return true;
        }
        // Check both directions for the rest of the pieces
        else {
          if(check_move_direction(row, col, LEFT))
            return true;
          if(check_move_direction(row, col, RIGHT))
            return true;
        }
      }
      // All players' pieces have been checked, no moves available
      if(totalPieces == 0)
        return false;
    }
  }

  return false;
}

bool draughts::model::board::check_move_direction(int row, int col, int direction)
{
  piece *currentPiece = gameBoard[row][col].get();  // Piece being checked
  coordinates forward; // Coordinates of landing spot after move
  coordinates back;    // Also for landing spot, for king pieces only
  type currentType = gameBoard[row][col]->get_type();  // Type of piece to move

  // Obtain a forward move for the piece (1 cell move) based on the direction
  forward = currentPiece->get_forward_action(false, row, col, direction);

  // When direction in move is empty, there is a possible move
  if (gameBoard[forward.first][forward.second]->get_type() == EMPTY)
    return true;
  // For the king pieces also need to check backwards movement
  else if (currentType == KING) {
    // Cast the currentPiece to a king piece and check its backward move
    king *kingPiece = dynamic_cast<king*>(currentPiece);
    back = kingPiece->get_backward_action(false, row, col, direction);

    if(gameBoard[back.first][back.second]->get_type() == EMPTY)
      return true;
  }

  return false;
}

// #################### Jumping validation ####################
bool draughts::model::board::check_all_possible_jumps(team playerTeam, int count)
{
  bool possibleJump = false;
  team currentTeam;

  // Reset all previous checked jumps made beforehand
  forcedJumps.clear();

  // Loop through entire board to check whether a jump could be made
  for(int row = 0; row < WIDTH; row++) {
    for(int col = 0; col < HEIGHT; col++) {
      // Store team of piece being iterated upon
      currentTeam = gameBoard[row][col]->get_team();
      // Only check possible jumps for pieces that belong to the player
      if(playerTeam == currentTeam) {
        count--;
        if(check_individual_jump(row, col))
          possibleJump = true;
      }
      // All of player's pieces have been checked
      if(count == 0)
        return possibleJump;
    }
  }

  return possibleJump;
}

bool draughts::model::board::check_individual_jump(int row, int col) {
  bool possibleJump = false;

  // 1. Piece is present in column 1/2 (0/1 in array) = Check right for jump
  if(col == FIRST_COL || col == SECOND_COL) {
    if (check_jump_direction(row, col, RIGHT_JUMP))
      possibleJump = true;
  }
  // 2. Piece is present in column 7/8 (6/7 in array) = Check left for jump
  else if (col == SECOND_LAST_COL || col == LAST_COL) {
    if (check_jump_direction(row, col, LEFT_JUMP))
      possibleJump = true;
  }
  // 3. Piece is anywhere else = Check both left and right for jump
  else {
    if (check_jump_direction(row, col, RIGHT_JUMP))
      possibleJump = true;
    if (check_jump_direction(row, col, LEFT_JUMP))
      possibleJump = true;
  }

  return possibleJump;
}

bool draughts::model::board::check_jump_direction(int x, int y, int direction)
{
  // Mostly same as check_move_direction(), some extra comments/additions made.
  piece *currentPiece = gameBoard[x][y].get();
  type currentType = gameBoard[x][y]->get_type();
  coordinates forward, back;

  /* Check if jump land spot results in being out of bounds
   * Since diagonally is equal for both x and y, only need to check one
   * Needs to be between 0 - 7 inclusive, values below/above are out of bounds */
  bool forwardOutOfBounds = false;
  bool backwardsOutOfBounds = false;

  // Obtain a forward jump for the piece (2 cell move) based on the direction
  forward = currentPiece->get_forward_action(true, x, y, direction);

  // Check if forward jump ends up with piece being out of bounds
  if(forward.first > O_END || forward.first < X_START)
    forwardOutOfBounds = true;

  // When jump results in not being out of bounds check cell 2 spaces ahead
  if (!forwardOutOfBounds) {
    // When cell in 2 spaces ahead is empty check if piece can jump
    if (gameBoard[forward.first][forward.second]->get_type() == EMPTY) {
      if (can_jump(x, y, forward.first, forward.second))
        return true;
    }
  }
  if (currentType == KING) {
    // Cast the currentPiece to a king piece and check its backward jump
    king *kingPiece = dynamic_cast<king*>(currentPiece);
    back = kingPiece->get_backward_action(true, x, y, direction);

    // Check if backward jump ends up with piece being out of bounds
    if(back.first > O_END || back.first < X_START)
      backwardsOutOfBounds = true;

    // Same bounds checking as forwards
    if (!backwardsOutOfBounds) {
      if(gameBoard[back.first][back.second]->get_type() == EMPTY) {
        if (can_jump(x, y, back.first, back.second))
          return true;
      }
    }
  }

  return false;
}

bool draughts::model::board::can_jump(int x1, int y1, int x2, int y2)
{
  // Coordinates: Piece being checked, Landing location, Cell being jumped over
  coordinates start, end, coords;
  // Types: Current piece to check, Piece in cell being jumped over
  team currentTeam, jumpedOverTeam;

  // Get type of piece to jump and of piece that is going to be jumped over
  coords = get_coordinates_of_jump(x1, y1, x2, y2);
  currentTeam = gameBoard[x1][y1]->get_team();
  jumpedOverTeam = gameBoard[coords.first][coords.second]->get_team();

  // Check if jumped over piece's team is not the same as current player's
  if (jumpedOverTeam != NO_TEAM && currentTeam != jumpedOverTeam) {
    // Add +1 to received positions as array starts from 0 and display: 1 to 8
    x1 += ARRAY_DIFF;       y1 += ARRAY_DIFF;
    x2 += ARRAY_DIFF;       y2 += ARRAY_DIFF;
    // Store individual x,y values as coordinate sets
    start = std::make_pair(x1,y1);
    end = std::make_pair(x2,y2);
    // Add it to the list of forced jumps the player has to make
    forcedJumps.push_back(std::make_pair(start, end));

    return true;
  }

  return false;
}

// #################### Score related functions ####################
bool draughts::model::board::move_piece(int x1, int y1, int x2, int y2)
{
  // Moved piece parameters
  type movedType = gameBoard[x1][y1]->get_type();
  team movedTeam = gameBoard[x1][y1]->get_team();
  // Create new piece that is a duplicate to the old to move to the new location
  std::unique_ptr<piece> movedPiece;
  if (movedType == NORMAL)
    movedPiece = std::make_unique<normal>(movedTeam);
  else
    movedPiece = std::make_unique<king>(movedTeam);

  // Empty cell to allocate to cell where piece moved from
  std::unique_ptr<piece> emptyCell = std::make_unique<empty>(NO_TEAM);

  coordinates coords;           // Coordinates of cell to remove if jumped over
  bool scoreUpdate = false;     // Flag to tell model if score is to be updated

  int colMove = y2 - y1;

  /* Check if player moved two spaces, Since bad cases have been caught,
   * this is when a enemy piece is to be removed */
  if (colMove == DOWN_JUMP || colMove == UP_JUMP) {
    // Create an empty cell if a piece has been jumped over
    std::unique_ptr<piece> emptyJumpCell = std::make_unique<empty>(NO_TEAM);
    // Get coordinates of piece that is jumped over
    coords = get_coordinates_of_jump(x1, y1, x2, y2);
    // Set it to empty
    gameBoard[coords.first][coords.second] = std::move(emptyJumpCell);
    // Increase score of current player by 1
    scoreUpdate = true;
  }

  // Set new cell contents to contain the piece moved
  gameBoard[x2][y2] = std::move(movedPiece);
  // Set original cell where piece moved from to be empty
  gameBoard[x1][y1] = std::move(emptyCell);
  // Return score update (0 if no jump has been made, +1 if so)
  return scoreUpdate;
}

bool draughts::model::board::promote_piece(int x, int y)
{
  // Return 1 if piece has been promoted (+1 score), or 0 when no promotion
  type pieceType = gameBoard[x][y]->get_type();
  team pieceTeam;
  std::unique_ptr<piece> kingPiece;

  // Only able to promote normal 'o' and normal 'x' pieces
  if(pieceType == NORMAL) {
    // Get the team the piece belongs to
    pieceTeam = gameBoard[x][y]->get_team();
    // Create a king piece with same team
    kingPiece = std::make_unique<king>(pieceTeam);
    // Place the king piece on the board
    gameBoard[x][y] = std::move(kingPiece);

    return true;
  }

  return false;
}

// #################### Getters and Setters ####################
char draughts::model::board::get_piece(int x, int y)
{
  return gameBoard[x][y]->get_icon();
}

coordinates draughts::model::board::get_coordinates_of_jump(int x1, int y1,
                                                            int x2, int y2)
{
  // Calculate coordinates of cell being jumped over, jump factor added later
  coordinates coords;
  int jumpX = x1;
  int jumpY = y1;

  int rowMove = x2 - x1;
  int colMove = y2 - y1;

  /* Shift coordinate back by one, there are 4 Cases:
  * rowMove = -ive and colMove = +ive: jumpX - jump, jumpY + jump
  * rowMove = +ive and colMove = -ive: jumpX + jump, jumpY - jump
  * rowMove = -ive and colMove = -ive: jumpX and jumpY - jump
  * rowMove = +ive and colMove = +ive: jumpX and jumpY + jump */

 if(rowMove < 0)
   jumpX -= JUMP;
 else
   jumpX += JUMP;

 if(colMove < 0)
   jumpY -= JUMP;
 else
   jumpY += JUMP;

  coords = std::make_pair(jumpX, jumpY);
  return coords;
}

std::list<moves> draughts::model::board::get_forced_jumps(void)
{
  return forcedJumps;
}

void draughts::model::board::reset_jump_list(void)
{
  forcedJumps.clear();
}

int draughts::model::board::get_width(void)
{
  return WIDTH;
}

int draughts::model::board::get_height(void)
{
  return HEIGHT;
}
