#ifndef GameState_h
#define GameState_h

#include "globals.h"

class GameState {
 private:
  int selectedRow;     // Game board row coordinate selected (in the range
                       // 0..boardSize-1)
  int selectedColumn;  // Game board column coordinate selected (in the range
                       // 0..boardSize-1)
  bool moveValid;  // Is the grid location selected by the above coordinates a
                   // valid move?
  bool
      gameOver;  // Is the game over as a result of the selected row and column?
  bool turn;     // Whose turn is it?
  int winner;    // who won the game? (Empty if a tie or game still in progress)
  int gameBoard[boardSize][boardSize];  // The game board

 public:
  // The constructor. It initializes:
  //     selectedRow to 0
  //     selectedColum to 0
  //     moveValid to true
  //     gameOver to false
  //     turn to true
  //     winner to Empty
  //     gameBoard locations to Empty (see globals.h)
  GameState();

  // Return the selected row (in the range 0..boardSize - 1)
  int get_selectedRow();

  // Return the selected column (in the range 0..boardSize - 1)
  int get_selectedColumn();

  // Set the selected row to value in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
  void set_selectedRow(int value);

  // Set the selected column in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
  void set_selectedColumn(int value);

  // Get the moveValid value
  bool get_moveValid();

  // Set the moveValid variable to value
  void set_moveValid(bool value);

  // Get the gameOver value
  bool get_gameOver();

  // Set the gameOver variable to value
  void set_gameOver(bool value);

  // Get the value of turn
  bool get_turn();

  // Set the value of turn
  void set_turn(bool value);

  // Get the value of winner
  int get_winner();

  // Set the value of winner;
  void set_winner(int value);

  // Get the game board value at the board location at row and col
  // This method checks that row, col and value are in range/valid
  // and if not it returns Empty
  int get_gameBoard(int row, int col);

  // Set the game board value at the board location at row and col to value
  // This method checks that row, col and value are in range/valid and if not it
  // just returns
  void set_gameBoard(int row, int col, int value);
};

#endif /* GameState_h */
