#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

GameState::GameState(){
    selectedRow = 0; 
    selectedColumn = 0; 
    moveValid = true;
    gameOver = false;
    turn = true; //starts with R which = true 
    winner = Empty; 
    for(int i = 0; i <= boardSize; i++){
        for(int j = 0; j <= boardSize; j++){
            gameBoard[i][j] = Empty;
        }
    }
}

int GameState::get_selectedRow(){
    return(selectedRow);
}

int GameState::get_selectedColumn(){
    return(selectedColumn);
}

void GameState::set_selectedRow(int value){
    if(value > boardSize-1 || value < 0){
        return; 
    } else{
        selectedRow = value; 
        return;
    }
}

void GameState::set_selectedColumn(int value){
    if(value > boardSize-1 || value < 0){
        return; 
    } else{
        selectedColumn = value; 
        return;
    }
}

bool GameState::get_moveValid(){
    return moveValid; 
}

void GameState::set_moveValid(bool value){
    moveValid = value; 
    return; 
}

bool GameState::get_gameOver(){
    return gameOver; 
}

void GameState::set_gameOver(bool value){
    gameOver = value;
    return; 
}

bool GameState::get_turn(){
    return turn;
}

void GameState::set_turn(bool value){
    turn = value;
    return;
}

int GameState::get_winner(){
    return winner; 
}

void GameState::set_winner(int value){
    winner = value; 
    return; 
}

int GameState::get_gameBoard(int row, int col){
    return gameBoard[row][col];
}

void GameState::set_gameBoard(int row, int col, int value){
  gameBoard[row][col] = value; 
}
