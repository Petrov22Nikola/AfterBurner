#include <iostream>
#include <ctype.h>
using namespace std;
int optimal = 0;

int victoryCondition(int board[9]){
  //Horizontal
  for(int j=0;j<7;j+=3){
    if(board[j] != 0){
      if(board[j] == board[j+1] && board[j] == board[j+2]){
        return board[j];
      }
    }
  }
  //Vertical
  for(int k=0;k<3;k+=1){
    if(board[k] != 0){
      if(board[k] == board[k+3] && board[k] == board[k+6]){
        return board[k];
      }
    }
  }
  //Diagonal
  if(board[4] != 0){
    if(board[4] == board[0] && board[4] == board[8]){
      return board[4];
    }
    if(board[4] == board[2] && board[4] == board[6]){
      return board[4];
    }
  }
  for(int m=0;m<9;m++){
    if(board[m] == 0){
      return 0;
    }
  }
  return 3;
}

int optimalMove(int player, int board[9]){
  int pseudoBoard[9];
  int moveRanking[9] = {0,0,0,0,0,0,0,0,0};
  copy(board, board+8, pseudoBoard);
  for(int n=0;n<9;n++){
    int temp = n;
    if(pseudoBoard[n] == 0){
      pseudoBoard[n] = player;
      int result = victoryCondition(pseudoBoard);
      if(result == player){
        moveRanking[n] = player;
      }else if(result == 3){
        moveRanking[n] = 3;
      }else if(result == 0){
        if(player == 2){
          moveRanking[n] = optimalMove(1,pseudoBoard);
        }else{
          moveRanking[n] = optimalMove(2,pseudoBoard);
        }
      }
      pseudoBoard[temp] = 0;
    }
  }
  for(int g=0;g<9;g++){
    if(player == moveRanking[g]){
      optimal = g+1;
      return player;
    }
  }
  for(int h=0;h<9;h++){
    if(moveRanking[h] == 3){
      optimal = h+1;
      return 3;
    }
  }
  return 0;
}

int main() {
  int board[9] = {0,0,0,0,0,0,0,0,0};
  //Move sequence
  char computer;
  int tS;
  cout << "Computer plays noughts/crosses (N/C): \n";
  cin >> computer;
  if(tolower(computer)=='n'){
    tS = 1;
  }else if(tolower(computer)=='c'){
    tS = 0;
  }else{
    cout << "Shrek is love, Shrek is life";
    return 0;
  }
  while(victoryCondition(board) == 0){
    //User input
    int choice;
    if(tS%2 == 1){
      cout << "Enter move (1->9, left->right, top->bottom): ";
      cin >> choice;
      if(choice < 1 || choice > 9 || board[choice-1] != 0){
        cout << "Shrek is love, Shrek is life";
        return 0;
      }
      board[choice-1] = 1;
    }else{
      optimalMove(2, board);
      board[optimal-1] = 2;
      cout << "Computer's Move: ";
      cout << optimal;
      cout << "\n";
    }
    tS += 1;
  }
  int nothing;
  if(victoryCondition(board) == 1){
    cout << "Mankind wins!" << endl;
    cout << "Press enter to terminate program: ";
    cin >> nothing;
    return 1;
  }
  if(victoryCondition(board) == 2){
    cout << "Computer wins!" << endl;
    cout << "Press enter to terminate program: ";
    cin >> nothing;
    return 2;
  }
  if(victoryCondition(board) == 3){
    cout << "Indecisive game..." << endl;
    cout << "Press enter to terminate program: ";
    cin >> nothing;
    return 3;
  }
}
