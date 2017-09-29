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
  init_board();
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
        // else {
        //   gameBoard[row][col] = nCircle;
        // }
      }
    }
  }

  gameBoard[4][1] = nCircle;
  gameBoard[6][3] = nCircle;
}

bool draughts::model::board::check_valid_selection(type playerType, int x, int y) {
  type tokenType = get_type(x, y);

  // 1a. Check player type against token type, if valid type, return
  if(validate_type(playerType, tokenType))
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
      else if (validate_type(startType, jumpType)){
        std::cout << imMsg << "You cannot jump over your own token" << std::endl;
        return false;
      }
    }
  }

  // 6. Player tried to move to a spot with a token inside it
  if (endType != EMPTY) {
    // Token at spot is their own:
    if(validate_type(startType, endType)){
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

bool draughts::model::board::validate_type(type t1, type t2) {
  // Function checks whether types match in same category, x tokens or o tokens
  // 1. Same parametersjumpType == startType
  if(t1 == t2)
    return true;

  // 2. Cross tokens
  else if((t1 == N_CROSS && t2 == K_CROSS) || (t1 == K_CROSS && t2 == N_CROSS))
    return true;

  // 3. Circle tokens
  else if((t1 == N_CIRCLE && t2 == N_CIRCLE) || (t1 == K_CIRCLE && t2 == N_CIRCLE))
    return true;

  return false;
}

// #################### Score related functions ####################
int draughts::model::board::move_token(int startx, int starty, int endx, int endy) {
  int scoreUpdate = 0;          // Flag to tell model if score is to be updated
  int colMove = endy - starty;
  std::pair<int, int> coords;   // Coordinates of cell to remove if jumped over

  type typeTokenMoved = get_type(startx, starty);

  /* Check if player moved two spaces, Since bad cases have been caught,
   * this is when a enemy piece is to be removed */
  if (colMove == downJump || colMove == upJump) {
    coords = get_token_jumped_over(startx, starty, endx, endy);

    gameBoard[coords.first][coords.second].set_type(EMPTY);
    scoreUpdate++;
  }

  // Set new cell contents to contain the token moved
  gameBoard[endx][endy].set_type(typeTokenMoved);
  // Set original cell where token moved from to be empty
  gameBoard[startx][starty].set_type(EMPTY);
  // Return score update (0 if no jump has been made, +1 if so)
  return scoreUpdate;
}

int draughts::model::board::promote_token(int x, int y) {
  // Return 1 if token has been promoted (+1 score), or 0 when no promotion
  type tokenType = get_type(x, y);
  token king;

  // Only able to promote normal 'o' and normal 'x' pieces
  if(tokenType == N_CIRCLE || tokenType == N_CROSS) {
    king.promote_token(tokenType);
    gameBoard[x][y] = king;
    return 1;
  }

  return 0;
}

bool draughts::model::board::check_extra_moves(int x, int y) {
  /* Tokens in column 1 can only move rightwards, in column 8 leftwards
   * For the rest they can move left or right */

  // Column 1
  if (y == 0)

}

// #################### Getters and Setters ####################
char draughts::model::board::get_token(int x, int y) {
  return gameBoard[x][y].print_token();
}

type draughts::model::board::get_type(int x, int y) {
  return gameBoard[x][y].get_type();
}

std::pair<int,int> draughts::model::board::get_token_jumped_over(
                   int startx, int starty, int endx, int endy)
{
  // Coordinates of cell being jumped over, jump factor added later
  std::pair<int, int> coords;
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

int draughts::model::board::get_width(void) {
  return WIDTH;
}

int draughts::model::board::get_height(void) {
  return HEIGHT;
}
