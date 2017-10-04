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
void draughts::model::board::init_board() {
  piece *redPiece, *whitePiece, *emptyCell;
  emptyCell = new empty(NO_TEAM);
  redPiece = new normal(RED);
  whitePiece = new normal(WHITE);
  // std::unique_ptr<piece> redPiece = std::make_unique<piece>(empty(NO_TEAM));
  // std::unique_ptr<piece> whitePiece = std::make_unique<piece>(normal(RED));
  // std::unique_ptr<piece> emptyCell = std::make_unique<piece>(normal(WHITE));


  for(int row = 0; row < WIDTH; row++) {
    for (int col = 0; col < HEIGHT; col++) {
      // Fill gaps between pieces with empty spaces
      if(((col + row) % 2) == 0)
        // gameBoard[row][col] = emptyCell;
        gameBoard[row][col] = std::move(emptyCell);
      else {
        // Initialize middle rows (3 and 4) as empty
        if (row > X_END && row < O_START)
          gameBoard[row][col] = emptyCell;
          // gameBoard[row][col] = std::move(emptyCell);
        // Initialize red 'x' pieces
        else if (row <= X_END)
          gameBoard[row][col] = redPiece;
          // gameBoard[row][col] = std::move(redPiece);
        // Initialize white 'o' pieces
        else
          gameBoard[row][col] = whitePiece;
          // gameBoard[row][col] = std::move(whitePiece);
      }
    }
  }

  // gameBoard[0][1] = emptyCell;
  // gameBoard[1][2] = redPiece;

  // Test draw
  // gameBoard[1][0] = redPiece;
  // gameBoard[2][3] = redPiece;
  // gameBoard[2][5] = redPiece;
  // gameBoard[2][7] = redPiece;
  // gameBoard[3][0] = redPiece;
  // gameBoard[3][2] = redPiece;
  // gameBoard[3][4] = redPiece;
  // gameBoard[3][6] = redPiece;
  //
  // gameBoard[4][1] = whitePiece;
  // gameBoard[4][3] = whitePiece;
  // gameBoard[4][5] = whitePiece;
  // gameBoard[4][7] = whitePiece;
  // gameBoard[5][0] = whitePiece;
  // gameBoard[5][2] = whitePiece;
  // gameBoard[5][4] = whitePiece;
  // gameBoard[5][6] = whitePiece;

  // gameBoard[2][1] = emptyCell;
  // gameBoard[4][1] = redPiece;
  //
  // gameBoard[4][3] = whitePiece;
  // gameBoard[4][5] = whitePiece;
  // gameBoard[5][0] = emptyCell;
  // gameBoard[6][1] = emptyCell;
}

bool draughts::model::board::check_valid_selection(team playerTeam, int x, int y)
{
  team selectedTeam = gameBoard[x][y]->get_team(); // team of selected piece

  // 1 Selected a piece that belongs to them exit
  if(playerTeam == selectedTeam)
    return true;

  // 2. Tried to select an empty cell
  if(selectedTeam == NO_TEAM)
    std::cout << isMsg << "No piece to move at this cell" << std::endl;
  else // 3. Selected a piece that does not belong to them
    std::cout << isMsg << "This piece does not belong to you" << std::endl;

  // Return false when either statements in 2. are true
  return false;
}

bool draughts::model::board::check_valid_move(int x1, int y1, int x2, int y2)
{
  piece *currentPiece = gameBoard[x1][y1];       // Piece selected
  type currType = gameBoard[x1][y1]->get_type(); // Type of piece selected
  team currTeam = gameBoard[x1][y1]->get_team(); // Team selected to jump
  team landTeam = gameBoard[x2][y2]->get_team(); // Landing spot
  team jumpTeam;                                 // What was jumped over

  // Coords of cell jumped over
  std::pair<int,int> jumpCoords;

  // Movement difference for row and column
  int rowMove = x2 - x1;
  int colMove = y2 - y1;

  // A. Check if piece was a normal type whether it tried to move backwards
  if(currType == NORMAL) {
    if(currTeam == RED && rowMove == UP) {
      std::cout << imMsg << "Red cannot move up with a 'x' piece" << std::endl;
      return false;
    }
    else if(currTeam == WHITE && rowMove == DOWN) {
      std::cout << imMsg << "White cannot move down with a 'o' piece" << std::endl;
      return false;
    }
  }

  // B. Check all other movement types with the piece itself
  if(!(currentPiece->check_valid_move(x1, y1, x2, y2)))
    return false;

  // C. Perform board checks comparing if a jump was to be made
  if (colMove == DOWN_JUMP || colMove == UP_JUMP) {
    // Get type of cell 1 position before jump (based on moving rowMove/colMove)
    jumpCoords = get_coordinates_of_jump(x1, y1, x2, y2);
    jumpTeam = gameBoard[jumpCoords.first][jumpCoords.second]->get_team();

    // Landing spot has no piece in it
    if (landTeam == NO_TEAM) {
      // 1. But then there is nothing to jump over to get to there
      if (jumpTeam == NO_TEAM) {
        std::cout << imMsg << "There is nothing you can jump over" << std::endl;
        return false;
      }
      // 2. Player tried to jump over their own piece
      else if (currTeam == jumpTeam){
        std::cout << imMsg << "You cannot jump over your own piece" << std::endl;
        return false;
      }
    }
  }

  // D. Landing spot has a piece in it (for moving and jumps)
  if(landTeam != NO_TEAM) {
    // 1. Piece at spot is their own:
    if(currTeam == landTeam)
      std::cout << imMsg << "A piece that belongs to you is there" << std::endl;
    // 2. Piece is of opponent's, to jump over must specify empty spot
    else {
      std::cout << imMsg << "Enemy piece is in that spot." << " To jump choose"
                << " an empty landing cell " << std::endl;
    }
    return false;
  }

  return true;
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
  piece *currentPiece = gameBoard[row][col];  // Piece being checked
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
      }
      // All of player's pieces have been checked
      if(count == 0)
        return possibleJump;
    }
  }

  return possibleJump;
}

bool draughts::model::board::check_jump_direction(int x, int y, int direction)
{
  // Mostly same as check_move_direction(), some extra comments/additions made.
  piece *currentPiece = gameBoard[x][y];
  type currentType = gameBoard[x][y]->get_type();
  coordinates forward, back;

  /* Check if jump land spot results in being out of bounds
   * Since diagonally is equal for both x and y, only need to check one
   * Needs to be between 0 - 7 inclusive, values below/above are out of bounds */
  bool forwardOutOfBounds = false;
  bool backwardsOutOfBounds = false;

  // Obtain a forward jump for the piece (2 cell move) based on the direction
  forward = currentPiece->get_forward_action(true, x, y, direction);

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
  piece *movedPiece = gameBoard[x1][y1];
  piece *emptyCell = new empty(NO_TEAM);  // Empty cell to overwrite removed piece
  coordinates coords;           // Coordinates of cell to remove if jumped over
  bool scoreUpdate = false;     // Flag to tell model if score is to be updated

  int colMove = y2 - y1;

  /* Check if player moved two spaces, Since bad cases have been caught,
   * this is when a enemy piece is to be removed */
  if (colMove == DOWN_JUMP || colMove == UP_JUMP) {
    // Get coordinates of piece that is jumped over
    coords = get_coordinates_of_jump(x1, y1, x2, y2);
    // Set it to empty
    gameBoard[coords.first][coords.second] = emptyCell;
    // Increase score of current player by 1
    scoreUpdate = true;
  }

  // Set new cell contents to contain the piece moved
  gameBoard[x2][y2] = movedPiece;
  // Set original cell where piece moved from to be empty
  gameBoard[x1][y1] = emptyCell;
  // Return score update (0 if no jump has been made, +1 if so)
  return scoreUpdate;
}

bool draughts::model::board::promote_piece(int x, int y)
{
  // Return 1 if piece has been promoted (+1 score), or 0 when no promotion
  type pieceType = gameBoard[x][y]->get_type();
  team pieceTeam;
  piece *kingPiece;

  // Only able to promote normal 'o' and normal 'x' pieces
  if(pieceType == NORMAL) {
    pieceTeam = gameBoard[x][y]->get_team(); // Get the team the piece belongs to
    kingPiece = new king(pieceTeam);         // Create a king piece with same team
    gameBoard[x][y] = kingPiece;             // Place the king piece on the board

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

int draughts::model::board::get_width(void)
{
  return WIDTH;
}

int draughts::model::board::get_height(void)
{
  return HEIGHT;
}
