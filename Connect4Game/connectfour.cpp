#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes

// to run if compilation error: ./connectfour

// The main function
int main() {
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds];

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col;
  int row = 0;
  int round = 0;
  int move_counter = 0;
  int R_wins = 0;
  int Y_wins = 0;

  cout << "Game 1\n"; 
  while (!game_state[round].get_gameOver()) {
    cout << "Enter column to place piece: ";
    cin >> col;

    if (cin.eof()) {
      cerr << endl << "Game ended by user." << endl;
      exit(0);
    }
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      col = -1; // giving col invalid value so it will be handled as invalid
                // input below
    }

    
    // Check validity of input and if not valid, handle accordingly
    if (col <= boardSize - 1 && col >= 0) {
      game_state[round].set_moveValid(false);
      for (int i = 6; i >= 0; i--) {
        if (game_state[round].get_gameBoard(i, col) == Empty) {
          row = i;
          game_state[round].set_moveValid(true); 
          break;
        }
      }
    }
    
    // The coordinates are valid; set the selectedRow and selectedColumn
    if (game_state[round].get_moveValid() == true) {
      cout << "column chosen: " << col << "\n"; 
      game_state[round].set_selectedRow(row);
      game_state[round].set_selectedColumn(col);

      //place player's move onto the board
      playMove(game_state[round]);
      move_counter++;

      //gameboard is full if there are 49 valid moves 
      if(move_counter == 49){
        game_state[round].set_gameOver(true);
      }
      
      //print the game board
      for (int i = 0; i <= boardSize - 1; i++) {
        for (int j = 0; j <= boardSize - 1; j++) {
          if(game_state[round].get_gameBoard(i, j) == 1){
            cout << "R"; 
          } else if(game_state[round].get_gameBoard(i, j) == -1){
            cout << "Y"; 
          } else{
            cout << "_";
          }
        }
        cout << "\n";
      }  
    } else{
      cout << "Invalid column!\n"; 
    } 

    //if game over, set up for new game to start
    if(game_state[round].get_gameOver() == true){
      move_counter = 0; 
      if(game_state[round].get_winner() == 0){
        cout << "The round is a draw!\n";     
      } else if(game_state[round].get_winner() == 1){
        cout << "\nR won this round!\n";
        R_wins++;
        if (R_wins == 2){ 
          cout << "R won the match!\n";
          exit(0);
        }
      }else{
        cout << "\nY won this round!\n";
        Y_wins++;
        if (Y_wins == 2){
          cout << "Y won the match!\n";
          exit(0);
        }
      }

      if(R_wins == 1 && Y_wins == 1){
        cout << "The match is a draw!"; 
        exit(0); 
      }
      round++;
      cout << "Game " << round + 1 << "\n";
    }
    
  }
}
