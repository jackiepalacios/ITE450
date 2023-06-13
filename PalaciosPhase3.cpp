/*Jacqueline Palacios
jpalacio@my.athens.edu
00100531
March 9, 2023
Phase 3
*/

#include <iostream>
#include <iomanip>
#include <set>
using namespace std;
#define empty 0

//name constants for charts
const int SIZE = 4;
const int ROW = 4, COL = 4;

void playRoll();
void playSudoku();
void printBoard(int [][SIZE]);
bool isValid(int [][SIZE], int, int, int);
void fillBoard(int [][SIZE], int, int);
int validateRow(int&); //validates row
int validateCol(int&); //validates column
int validateInput(int&); //validates input
int valid_row(int, int [][SIZE]);
int valid_col(int, int [][SIZE]);
int valid_subsquares(int [][SIZE]);

int main()
{
    srand(time(0)); // initialize random seed
    
    int selection = 0;
    const int GAME1 = 1;
    const int GAME2 = 2;
    const int EXIT = 3;
  
    do
    {
        cout<<"\nWelcome to our 2 in 1 game! This program will let you select a game\n"
            <<"to play. Please enter a number (1-3) to pick your selection.\n\n";
        cout<<"1. Play High roll vs. Low roll\n"
            <<"2. Play 4x4 Sudoku\n"
            <<"3. Exit the program\n\n\n";
        cout<<"Selection: ";
        cin>>selection;

        while(selection != GAME1 && selection != GAME2 && selection != EXIT)
        {
            cout<<"\n\nYou have entered an invalid menu choice.\n";
            cout<<"Please enter a choice from the menu (1-3): ";
            cin>>selection;
        }


        switch(selection)
        {
        case GAME1: 
        {

            playRoll();
            
            break;
        }

        case GAME2:
        { 
            playSudoku();

            break;
        }

            case EXIT:
        { 
            cout<<"\nThank you for using our program. We will see you again in our next game!";
            return 0;
        }
        }
    } while(selection == GAME1 || selection == GAME2);  
}

//CREATE GAME MAIN FUNCTIONS
void playRoll() 
{
    int selection, roll = 0;

    cout<<"\nWelcome to game 1 of 2 in this program! This game will consist\n"
        <<"of High roll vs. Low roll.\n\n"
        <<"You will select whether you want to 'bet' on a high roll or a low roll.\n"
        <<"Afterwards, you will pick a number between 1-12.\n\n"
        <<"After your selection, a die will be rolled and your victory\n"
        <<"(or failure) will be revealed!\n";

    do
    {
        srand(time(0)); // initialize random seed
        int maxNum = 12;
        char rollBet = ' ';
        int highRoll = rand() % maxNum + 1;
        int lowRoll = rand() % maxNum + 1;


        cout<<"\nWill you bet on high or low? Please type 'H' for high, 'L' for low: ";
        cin>>rollBet;

        // input validation for high or low
        while (!(rollBet == 'H' || rollBet == 'h' || rollBet == 'L' || rollBet == 'l'))
        {
            cout<<"\n\nYou have entered an invalid option. Please try again.\n"
                <<"Enter either (H) or (L): ";
                cin>>rollBet;
        }

        cout<<"\n\nPlease enter a number between 1-12 for your die: ";
        cin>>roll;

        //input validation
        while (roll < 1 || roll > 12)
    {
        cout<<"\n\nYou have entered an invalid option. Please try again.\n"
                <<"Enter a number between 1-12 for your die: ";
        cin>>roll;
    }

        if (rollBet == 'H' || rollBet == 'h') {

            // determine the winner and display the result
            if (highRoll > roll)
            {
                cout<<"\nThe die rolled a value of "<<highRoll<<endl;
                cout<<"Congratulations! You win! Will you play again?\n";
            }
            else if (roll > highRoll)
            {
                cout<<"\nThe die rolled a value of "<<highRoll<<endl;
                cout<<"You lose! Will you play again?\n";
            }
            else
            {
                cout<<"\nThe die rolled a value of "<<highRoll<<endl;
                cout << "It's a tie! Will you play again?\n";
            }
        }

        else if (rollBet == 'L' || rollBet == 'l') {
                if (roll > lowRoll)
            {
                cout<<"\nThe die rolled a value of "<<lowRoll<<endl;
                cout<<"Congratulations! You win! Will you play again?\n";
            }
            else if (lowRoll > roll)
            {
                cout<<"\nThe die rolled a value of "<<lowRoll<<endl;
                cout<<"You lose! Will you play again?\n";
            }
            else
            {
                cout<<"\nThe die rolled a value of "<<lowRoll<<endl;
                cout << "It's a tie! Will you play again?\n";
            }
    }

    //ask to play again
    cout<<"Please enter 1 for yes, 2 for no: ";
    cin>>selection;

    // input validation for playing game again
    while (selection < 1 || selection > 2)
    {
        cout<<"\n\nYou have entered an invalid option. Please try again.\n"
                <<"Enter either 1 for yes, 2 for no: ";
        cin>>selection;
    }

    } while(selection == 1);
}

//SUDOKU CODE STARTS HERE
void playSudoku() 
{
    int selection = 0;

    cout<<"\nWelcome to game 2 of 2 in this program! This game\n" 
        <<"will consist of a 4x4 version of Sudoku.\n\n";
    cout<<"1. Each digit from 1-4 should appear in a row once.\n"
        <<"2. Each digit from 1-4 should appear in a column once.\n"
        <<"3. No row or column should have the same value appear.\n";
    do
    {

        // create a new Sudoku board
        int board[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = 0;
            }
        }
        
        // fill the Sudoku board with random numbers
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int num = rand() % 4 + 1;
                if (isValid(board, i, j, num)) {
                    board[i][j] = num;
                }
            }
        }
        
        // print the Sudoku board
        cout << endl;
        cout << "Sudoku Puzzle" << endl;
        cout << "=============" << endl;
        printBoard(board);

        //INSERT FUNCTION FOR USER TO FILL BOARD
        fillBoard(board, 0, 0);
        
        cout<<endl<<endl;

    //ask to play again
    cout<<"Will you play again?\n";
    cout<<"Please enter 1 for yes, 2 for no: ";
    cin>>selection;

    // input validation for playing game again
    while (selection < 1 || selection > 2)
    {
        cout<<"\n\nYou have entered an invalid option. Please try again.\n"
                <<"Enter either 1 for yes, 2 for no: ";
        cin>>selection;
    }

    } while(selection == 1);
}

void printBoard(int board[][SIZE]) 
{
    // print the Sudoku board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
            if ((j + 1) % 2 == 0) {
                cout << " ";
            }
        }
        cout << endl;
        if ((i + 1) % 2 == 0) {
            cout << endl;
        }
    }
}

bool isValid(int board[][SIZE], int row, int col, int num) 
{
    // check if placing num in (row, col) is valid
    for (int i = 0; i < SIZE; i++) 
    {
        if (board[row][i] == num) 
        {
            return false;
        }
    }
    for (int i = 0; i < SIZE; i++) 
    {
        if (board[i][col] == num) 
        {
            return false;
        }
    }
    int boxRow = row / 2 * 2;
    int boxCol = col / 2 * 2;
    for (int i = boxRow; i < boxRow + 2; i++) 
    {
        for (int j = boxCol; j < boxCol + 2; j++) 
        {
            if (board[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

int validateRow(int &row)
{
  while(row < 1 || row > 4)
  {
    cout<<"You have entered an invalid row number. Please choose an empty row numbers 1 through 4: ";
    cin>>row;
    }
  return row;
}

int validateCol(int &col)
{
  while(col < 1 || col > 4)
  {
      cout<<"You have entered an invalid column number. Please choose an empty column numbers 1 through 4: ";
      cin>>col;
  }
  return col;
}

int validateInput(int &input)
{
  while(input < 1 || input > 4)
  {
      cout<<"You have entered an invalid value. Please choose a value numbers 1 through 4: ";
      cin>>input;
  }
  return input;
}

bool isEmptyLocation(int board[][SIZE], int &row, int &col)
{
    for (row = 0; row < ROW; row++)
    for (col = 0; col < COL; col++)
    if (board[row][col] == empty)
    {
        return true;
    }
    return false;
}

int valid_row(int row, int board[][SIZE])
{
  set<int> s;

  for(int i = 0; i < 4; i++)
  {
    // Checking for values outside 0 and 4
    if(board[row][i] < 0 || board[row][i] > 4)
    {
      cout<<"Invalid value"<<endl;
      return -1;
    }
    else
    { 
        //Checking for repeated values.
        if(board[row][i] != 0)
        {
            if(s.insert(board[row][i]).second == false)
            {
            return 0;
            }
        }
    }
  }
  return 1;
}

int valid_col(int col, int board[][SIZE])
{
  set<int> s;

  for(int i = 0; i < 4; i++)
  {
    // Checking for values outside 0 and 4
    if(board[i][col] < 0 || board[i][col] > 4)
    {
      cout<<"Invalid value"<<endl;
      return -1;
    }
    else
    { 
        //Checking for repeated values.
        if(board[i][col] != 0)
        {
            if(s.insert(board[i][col]).second == false)
            {
                return 0;
            }
        }
    }
  }
  return 1;
}

int valid_subsquares(int board[][SIZE])
{
  for(int row = 0; row < 4; row = row + 2)
  {
    for(int col = 0; col < 4; col = col + 2)
    {
        set<int> s;
        for(int r = row; r < row + 2; r++)
        {
          for(int c = col; c < col + 2; c++)
          {
            if(board[r][c] < 0 || board[r][c] > 4)
            {
              cout<<"Invalid value"<<endl;
              return -1;
            }
            else
            {
              // Checking for repeated values
              if(board[r][c] != 0)
              {
                if(s.insert(board[r][c]).second == false)
                {
                  return 0;
                }
              } 
            }
          }
        }    
    }
  }
  return 1;
}

//Function to check if the board invalid.
void valid_board(int board [][SIZE])
{
  for(int i = 0; i < 4; i++)
  {
    int res1 = valid_row(i, board);
    int res2 = valid_col(i, board);
    // If a row or a column is invalid, then the board is invalid.
    if(res1 < 1 || res2 < 1){
      cout<<"The board is invalid. You lose!"<<endl;
      return;
    }
  }
  // if any one the subsquares is invalid, then the board is invalid.
  int res3 = valid_subsquares(board);
  if(res3 < 1)
  {
    cout<<"The board is invalid. You lose!"<<endl;
  }
  else
  {
    cout<<"Congratulations! The board is valid."<<endl;
  }
}

void fillBoard(int board[][SIZE], int row, int col)
{
  int rowBoard, colBoard, inputBoard = 0;

  while(isEmptyLocation(board, row, col))
  {
    //validates the row
    cout<<"Enter the row number (1-4): ";
    cin>>rowBoard;
    validateRow(rowBoard);
    cout<<endl;

    //validates the col
    cout<<"Enter the column number (1-4): ";
    cin>>colBoard;
    validateCol(colBoard);
    cout<<endl;

    //validates the input
    cout<<"Enter the value number (1-4): ";
    cin>>inputBoard;
    validateInput(inputBoard);
    cout<<endl;

    board[row][col] = inputBoard;
  }
    cout<<endl<<endl<<"Sudoku Puzzle"<<endl;
    cout<<"============="<<endl;
    printBoard(board);
    cout<<endl<<endl;
    valid_board(board);
}