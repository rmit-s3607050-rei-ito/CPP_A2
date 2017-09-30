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
  token empty, nCross, nCircle;
  empty.set_type(EMPTY);
  nCross.set_type(N_CROSS);
  nCircle.set_type(N_CIRCLE);

  for(int row = 0; row < WIDTH; row++) {
    for (int col = 0; col < HEIGHT; col++) {
      // Fill gaps between tokens with empty spaces
      if(((col + row) % 2) == 0) {
        gameBoard[row][col] = empty;
      } else {
        // Initialize middle rows (3 and 4) as empty
        if (row > X_END && row < O_START) {
          gameBoard[row][col] = empty;
        }
        // Initialize 'x' tokens
        else if (row <= X_END) {
          gameBoard[row][col] = nCross;
        }
        // Initialize 'o' tokens
        else {
          gameBoard[row][col] = nCircle;
        }
      }
    }
  }

  // gameBoard[1][0] = nCross;
  //
  // gameBoard[2][3] = nCross;
  // gameBoard[2][5] = nCross;
  // gameBoard[2][7] = nCross;
  // gameBoard[3][0] = nCross;
  // gameBoard[3][2] = nCross;
  // gameBoard[3][4] = nCross;
  // gameBoard[3][6] = nCross;
  //
  // gameBoard[4][1] = nCircle;
  // gameBoard[4][3] = nCircle;
  // gameBoard[4][5] = nCircle;
  // gameBoard[4][7] = nCircle;
  // gameBoard[5][0] = nCircle;
  // gameBoard[5][2] = nCircle;
  // gameBoard[5][4] = nCircle;
  // gameBoard[5][6] = nCircle;
}

bool draughts::model::board::check_valid_selection(type playerType, int x, int y) {
  type tokenType = get_type(x, y);

  // 1a. Check player type against token type, if valid type, return
  if(is_same_type(playerType, tokenType))
    return true;

  // 2. Tried to select an empty cell
  if(tokenType == EMPTY)
    std::cout << isMsg << "No token to move at this cell" << std::endl;
  else // 3. Selected a token that does not belong to them
    std::cout << isMsg << "This token does not belong to you" << std::endl;

  // False when they select an empty slot or a token that doesnt belong to them
  return false;
}

bool draughts::model::board::check_valid_move(int startx, int starty, int endx, int endy) {
  type startType = get_type(startx, starty); // Token type selected to jump
  type endType = get_type(endx, endy);       // Landing spot
  type jumpType;                             // What was jumped over at jump

  // Coords of cell jumped over
  std::pair<int,int> jumpCoords;

  // Movement difference for row and column
  int rowMove = endx - startx;
  int colMove = endy - starty;

  // 1. Player tried to move forward or left/right
  if(rowMove == 0 || colMove == 0) {
    std::cout << imMsg << "You can only move diagonally" << std::endl;
    return false;
  }

  // 3. Player tried to move incorrectly with normal tokens
  if(startType == N_CROSS && rowMove == up) {
    std::cout << imMsg << "You cannot move up with a 'x' token" << std::endl;
    return false;
  }
  else if(startType == N_CIRCLE && rowMove == down) {
    std::cout << imMsg << "You cannot move down with a 'o' token" << std::endl;
    return false;
  }

  /* End coords cannot be both positive or both negative, must vary
   * if (Both positive || Both negative) */
  if ((endx % 2 == 0 && endy % 2 == 0) || (endx % 2 != 0 && endy % 2 != 0)) {
    std::cout << imMsg << "The selected cell is not reachable" << std::endl;
    return false;
  }

  // 4. Player entered a move with a difference > 2
  if (colMove > downJump || colMove < upJump){
    std::cout << imMsg << "You cannot move more than 2 spaces" << std::endl;
    return false;
  }

  // 5. Player moved 2 spaces
  if (colMove == downJump || colMove == upJump) {
    // Get type of cell 1 position before jump (based on moving rowMove/colMove)
    jumpCoords = get_token_jumped_over(startx, starty, endx, endy);
    jumpType = get_type(jumpCoords.first, jumpCoords.second);

    // Check which type this is
    if (endType == EMPTY) {
      if (jumpType == EMPTY) {
        std::cout << imMsg << "There is nothing you can jump over" << std::endl;
        return false;
      }
      else if (is_same_type(startType, jumpType)){
        std::cout << imMsg << "You cannot jump over your own token" << std::endl;
        return false;
      }
    }
  }

  // 6. Player tried to move to a spot with a token inside it
  if (endType != EMPTY) {
    // Token at spot is their own:
    if(is_same_type(startType, endType)){
      std::cout << imMsg << "A token that belongs to you is in that cell" <<
      std::endl;
    }
    // Token is of opponent's, to jump over must specify empty spot
    else {
      std::cout << imMsg << "Opponent's token is in that spot. " <<
                            "To jump over specify an empty cell" << std::endl;
    }
    return false;
  }

  return true;
}

bool draughts::model::board::is_same_type(type t1, type t2) {
  // Function checks whether types match in same category, x tokens or o tokens
  // 1. Same parametersjumpType == startType
  if(t1 == t2)
    return true;

  // 2. Cross tokens
  else if((t1 == N_CROSS && t2 == K_CROSS) || (t1 == K_CROSS && t2 == N_CROSS))
    return true;

  // 3. Circle tokens
  else if((t1 == N_CIRCLE && t2 == K_CIRCLE) || (t1 == K_CIRCLE && t2 == N_CIRCLE))
    return true;

  return false;
}

// #################### Validation: Any possible moves left ####################
bool draughts::model::board::check_all_possible_moves(int numXToken, int numYToken) {
  type currentType;
  bool possibleMove = false;
  int totalTokens = numXToken + numYToken;

  // Loop through entire board to check whether a move could be made
  for(int row = 0; row < WIDTH; row++) {
    for(int col = 0; col < HEIGHT; col++) {
      // Store current type of token being iterated upon
      currentType = gameBoard[row][col].get_type();
      // Only check possible moves for non-empty cells
      if(currentType != EMPTY) {
        std::cout << "Checking token at: " << row << "," << col << std::endl;
        totalTokens--;
        // Tokens in Column 0 and 1 can only move right
        if(col == FIRST_COL || col == SECOND_COL) {
          if(check_move_direction(row, col, right))
            return true;
        }
        // Tokens in Column 8 and 7 can only move left
        else if(col == LAST_COL || col == SECOND_LAST_COL) {
          if(check_move_direction(row, col, left))
            return true;
        }
        // Check both directions for the rest of the tokens
        else {
          if(check_move_direction(row, col, left))
            return true;
          if(check_move_direction(row, col, right))
            return true;
        }
      }
      // All players' tokens have been checked, no moves available
      if(totalTokens == 0)
        return possibleMove;
    }
  }

  return possibleMove;
}

bool draughts::model::board::check_move_direction(int row, int col, int direction) {
  int forwardX, forwardY;       // Coordinates of landing spot after jump
  int backX, backY;             // Also for landing spot, for king tokens only
  type currentType = get_type(row, col);  // Type of current token to jump

  // Direction doesn't vary between token types for column (y-axis) movement
  forwardY = col + direction;
  backY = forwardY;

  // Moving by row will vary whether going up or down
  // 1. 'x' type tokens, forward = down + direction, backwards = reverse
  if(currentType == N_CROSS || currentType == K_CROSS) {
    forwardX = row + down;
    backX = row + up;
  } // 2. 'o' type tokens, forward = up + direction, backwards = reverse
  else if (currentType == N_CIRCLE || currentType == K_CIRCLE) {
    forwardX = row + up;
    backX = row + down;
  }

  // When direction in move is empty, there is a possible move
  if (gameBoard[forwardX][forwardY].get_type() == EMPTY)
    return true;
  // For the king pieces also need to check backwards movement
  else if (currentType == K_CIRCLE || currentType == K_CROSS) {
    if(gameBoard[backX][backY].get_type() == EMPTY)
      return true;
  }

  return false;
}

// #################### Jumping validation ####################
bool draughts::model::board::check_all_possible_jumps(type playerType, int count) {
  bool possibleJump = false;
  type currentType;

  // Reset all previous checked jumps made beforehand
  forcedJumps.clear();

  // Loop through entire board to check whether a jump could be made
  for(int row = 0; row < WIDTH; row++) {
    for(int col = 0; col < HEIGHT; col++) {
      // Store current type of token being iterated upon
      currentType = gameBoard[row][col].get_type();
      // Only check possible jumps for non-empty cells and those of current players'
      if(currentType != EMPTY && is_same_type(currentType, playerType)) {
        count--;
        if(check_individual_jump(row, col))
          possibleJump = true;
      }
      // All of player's tokens have been checked
      if(count == 0)
        return possibleJump;
    }
  }

  return possibleJump;
}

bool draughts::model::board::check_individual_jump(int row, int col){
  /* NOTE: Check if token at the specific location can jump again
   * Tokens in column 1 or 2 can only move rightwards, in column 7 or 8 leftwards
   * For the rest they can move left or right */
  bool possibleJump = false;

  // 1. Token is present in column 1/2 (0/1 in array) = Check right for jump
  if(col == FIRST_COL || col == SECOND_COL) {
    if (check_jump_direction(row, col, RIGHT_JUMP))
      return true;
  }
  // 2. Token is present in column 7/8 (6/7 in array) = Check left for jump
  else if (col == SECOND_LAST_COL || col == LAST_COL) {
    if (check_jump_direction(row, col, LEFT_JUMP))
      return true;
  }
  // 3. Token is anywhere else = Check both left and right for jump
  else {
    if (check_jump_direction(row, col, RIGHT_JUMP))
      possibleJump = true;
    if (check_jump_direction(row, col, LEFT_JUMP))
      possibleJump = true;
  }

  return possibleJump;
}

bool draughts::model::board::check_jump_direction(int row, int col, int direction){
  int forwardX, forwardY;       // Coordinates of landing spot after jump
  int backX, backY;             // Also for landing spot, for king tokens only
  type currentType = get_type(row, col);  // Type of current token to jump

  // Direction doesn't vary between token types for column (y-axis) movement
  forwardY = col + direction;
  backY = forwardY;

  // Moving by row will vary whether going up or down
  // 1. 'x' type tokens, forward = down + direction, backwards = reverse
  if(currentType == N_CROSS || currentType == K_CROSS) {
    forwardX = row + downJump;
    backX = row + upJump;
  } // 2. 'o' type tokens, forward = up + direction, backwards = reverse
  else if (currentType == N_CIRCLE || currentType == K_CIRCLE) {
    forwardX = row + upJump;
    backX = row + downJump;
  }

  // When landing spot is empty check if able to jump for all piece types
  if (gameBoard[forwardX][forwardY].get_type() == EMPTY) {
    if (can_jump(row, col, forwardX, forwardY))
      return true;
  }
  // For the king pieces also need to check a backwards jump
  if (currentType == K_CIRCLE || currentType == K_CROSS) {
    if(gameBoard[backX][backY].get_type() == EMPTY) {
      if (can_jump(row, col, backX, backY))
        return true;
    }
  }

  return false;
}

bool draughts::model::board::can_jump(int row, int col, int endX, int endY) {
  // Absolute row end positions, ensure you cant jump out forward/back out of bounds
  int xEndAbs = std::abs(endX);

  // Coordinates:
  coordinates start;   // Token being checked
  coordinates end;     // Landing location
  coordinates coords;  // Cell being jumped over
  // Types:
  type currentType;           // Current token to check
  type typeJumpedOver;        // Token in cell being jumped over

  // Get type of token to jump and of token that is going to be jumped over
  coords = get_token_jumped_over(row, col, endX, endY);
  currentType = get_type(row, col);
  typeJumpedOver = get_type(coords.first, coords.second);

  // 1. Is its type the same as current token?
  if (typeJumpedOver != EMPTY && !is_same_type(currentType, typeJumpedOver)) {
    // Add +1 to received positions as array starts from 0 and display is 1 to 8
    row += ARRAY_DIFF;        col += ARRAY_DIFF;
    endX += ARRAY_DIFF;       endY += ARRAY_DIFF;

    // Store individual x,y values as coordinate sets
    start = std::make_pair(row,col);
    end = std::make_pair(endX,endY);

    // Add coordinate to list of forced jumps if its not an out of bounds jump
    if (xEndAbs >= X_START && xEndAbs <= O_END) {
      forcedJumps.push_back(std::make_pair(start, end));
      return true;
    }
  }

  return false;
}

// #################### Score related functions ####################
int draughts::model::board::move_token(int startx, int starty, int endx, int endy) {
  bool scoreUpdate = false;     // Flag to tell model if score is to be updated
  int colMove = endy - starty;
  coordinates coords;           // Coordinates of cell to remove if jumped over

  type typeTokenMoved = get_type(startx, starty);

  /* Check if player moved two spaces, Since bad cases have been caught,
   * this is when a enemy piece is to be removed */
  if (colMove == downJump || colMove == upJump) {
    // Get coordinates of token that is jumped over
    coords = get_token_jumped_over(startx, starty, endx, endy);
    // Set it to empty
    gameBoard[coords.first][coords.second].set_type(EMPTY);
    // Increase score of current player by 1
    scoreUpdate = true;
  }

  // Set new cell contents to contain the token moved
  gameBoard[endx][endy].set_type(typeTokenMoved);
  // Set original cell where token moved from to be empty
  gameBoard[startx][starty].set_type(EMPTY);
  // Return score update (0 if no jump has been made, +1 if so)
  return scoreUpdate;
}

bool draughts::model::board::promote_token(int x, int y) {
  // Return 1 if token has been promoted (+1 score), or 0 when no promotion
  type tokenType = get_type(x, y);
  token king;

  // Only able to promote normal 'o' and normal 'x' pieces
  if(tokenType == N_CIRCLE || tokenType == N_CROSS) {
    king.promote_token(tokenType);
    gameBoard[x][y] = king;
    return true;
  }

  return false;
}

// #################### Getters and Setters ####################
char draughts::model::board::get_token(int x, int y) {
  return gameBoard[x][y].print_token();
}

type draughts::model::board::get_type(int x, int y) {
  return gameBoard[x][y].get_type();
}

coordinates draughts::model::board::get_token_jumped_over(int startx, int starty,
                                                          int endx, int endy)
{
  // Calculate coordinates of cell being jumped over, jump factor added later
  coordinates coords;
  int jumpX = startx;
  int jumpY = starty;

  int rowMove = endx - startx;
  int colMove = endy - starty;

  /* Shift coordinate back by one, there are 4 Cases:
  * rowMove = -ive and colMove = +ive: jumpX - jump, jumpY + jump
  * rowMove = +ive and colMove = -ive: jumpX + jump, jumpY - jump
  * rowMove = -ive and colMove = -ive: jumpX and jumpY - jump
  * rowMove = +ive and colMove = +ive: jumpX and jumpY + jump */

 if(rowMove < 0)
   jumpX -= jump;
 else
   jumpX += jump;

 if(colMove < 0)
   jumpY -= jump;
 else
   jumpY += jump;

  coords = std::make_pair(jumpX, jumpY);
  return coords;
}

std::list<moves> draughts::model::board::get_forced_jumps(void) {
  return forcedJumps;
}

int draughts::model::board::get_width(void) {
  return WIDTH;
}

int draughts::model::board::get_height(void) {
  return HEIGHT;
}
