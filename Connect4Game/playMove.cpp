#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes (if you need)

void playMove(GameState& game_state) {
  int getRow = game_state.get_selectedRow(); 
  int getCol = game_state.get_selectedColumn();
 
  //if valid check which player's turn it is (check if placing R or Y)
  if(game_state.get_moveValid() == true){
    int player = 0;
    if(game_state.get_turn() == true){
      player = R;  
    } else{
      player = Y; 
    }

    //change gameboard to where player put counter
    game_state.set_gameBoard(getRow, getCol, player);

    //check for horizontal wins
    if(game_state.get_gameBoard(getRow, 3) == player){
      int counter = 0; 
      //check right
      for(int i = 2; i >= 0; i--){
        if(game_state.get_gameBoard(getRow, i) != player){
          break;
        }
        else{
            counter++;
        }   
      }
      //check left
      for(int i = 4; i <= 6; i++){
        if(game_state.get_gameBoard(getRow, i) != player){
          break;
        }
        else{
            counter++;
        } 
      }
      if(counter == 3){
        game_state.set_winner(player); 
        game_state.set_gameOver(true); 
      }
    }

    //check for vertical wins
    if(game_state.get_winner()==false){
      if(game_state.get_gameBoard(3, getCol) == player){
        int counter = 0; 
        //check top
        for(int i = 2; i >= 0; i--){
          if(game_state.get_gameBoard(i, getCol) != player){
            break;
          }
          else{
              counter++;
          }   
        } 
        //check left
        for(int i = 4; i <= 6; i++){
          if(game_state.get_gameBoard(i, getCol) != player){
            break;
          }
          else{
              counter++;
          } 
        }
        if(counter == 3){
          game_state.set_winner(player); 
          game_state.set_gameOver(true); 
        }
      }
    }

    //check for diagonal wins
    if (game_state.get_gameOver()==false) {
      int counter = 0;
      for (int i = -3; i <= 3; i++){
        int row = getRow + i;
        int col = getCol + i;
          if (game_state.get_gameBoard(row, col) == player){
            counter++;
            if(counter == 4) {
              game_state.set_winner(player);
              game_state.set_gameOver(true);
              break;
            }
          } else{
            counter = 0;
          } 
      }
    }
  
    // Check for diagonal wins other direction
    if (game_state.get_gameOver()==false){
      int counter = 0;
      for (int i = -3; i <= 3; i++){
        int row = getRow + i;
        int col = getCol - i;
        if (game_state.get_gameBoard(row, col) == player){
          counter++;
          if(counter == 4){
            game_state.set_winner(player);
            game_state.set_gameOver(true);
            break;
          }
        } else{
          counter = 0;
        }
      }
    }
    
    //change players for next turn
    if(game_state.get_turn() == true){
      game_state.set_turn(false);  
    } else if (game_state.get_turn() == false){
      game_state.set_turn(true);  
    }
  } 
}
