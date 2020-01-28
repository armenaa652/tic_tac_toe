#include <iostream>
#include <iomanip>
#include <limits>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif
#include <string>
using namespace std;

void boardSetup();
void playerChoice(char);
void computerChoice(char,int);
void startup();
int computerLogic(char,int);
bool gameWin(char);
bool gameDraw();
bool errorCheck(char);
char matrix[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int xwins = 0,owins = 0;



int main()
{
    int num2 = 0, difficulty = 1;
    char player, computer, choice;
    bool error = true;
    do
    {
        if (system("CLS")) system("clear");
        cout << endl << setw(26) << "" << "\33[4mPlease Select Gamemode:\33[0m" << endl
             << setw(26) << "" << "1. Player vs Player"<< endl
             << setw(26) << "" << "2. Player vs Computer" << endl;
        cout << setw(24) << "";
        cin >> choice;
        if(choice == '1')
        {
            startup();
            boardSetup();
            bool gameExit = false;
            bool gameExit2 = false;
            for(int num = 2; gameExit == false and gameExit2 == false; num++)
            {
                if(num % 2 == 0)
                    player = 'X';
                else if(num % 2 == 1)
                    player = 'O';
                playerChoice(player);
                boardSetup();
                gameExit = gameWin(player);
                if(gameExit == false)
                    gameExit2 = gameDraw();
            }
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
        }
        else if(choice == '2')
        {
            do
            {
                cout << setw(29) << "" <<  "\33[4mWhat difficulty?\33[0m" << endl
                << setw(26) << "" << "1. Easy"<< endl
                << setw(26) << "" << "2. Medium" << endl
                << setw(26) << "" << "3. Hard"<< endl
                << setw(26) << "" << "4. Impossible" << endl;
                cout << setw(24) << "";
                cin >> difficulty;
                if(difficulty != 1 and difficulty != 2 and difficulty != 3 and difficulty != 4)
                    error = true;
                else error = false;
            }while(error == true);

            do
            {
                cout << setw(22) << "" <<  "\33[4mWould you like to be X's or O's?\33[0m" << endl;
                cout << setw(24) << "";
                cin >> choice;
                if(choice != 'x' and choice != 'X' and choice != 'o' and choice != 'O')
                    error = true;
                else error = false;
            }while(error == true);
            startup();
            boardSetup();
            bool gameExit = false;
            bool gameExit2 = false;
            for(int num = 2; gameExit == false and gameExit2 == false; num++)
            {
                if(choice == 'x' or choice == 'X')
                    {
                        player = 'X';
                        computer = 'O';
                        if(num % 2 == 0)
                            playerChoice(player);
                        else if(num % 2 == 1)
                        {
                            computerChoice(computer,difficulty);
                            player = computer;
                        }
                    }

                if(choice == 'o' or choice == 'O')
                    {
                        player = 'O';
                        computer = 'X';
                        if(num % 2 == 1)
                        {
                            playerChoice(player);
                        }
                        else if(num % 2 == 0)
                        {
                            computerChoice(computer,difficulty);
                            player = computer;
                        }
                    }
                boardSetup();
                gameExit = gameWin(player);
                if(gameExit == false)
                    gameExit2 = gameDraw();
            }

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
        }
        else if (choice == '3')
        {
            num2 = 1;
        }

    }while(num2 == 0);
    return 0;
}

void startup()
{
    matrix[0][0] = '1';
    matrix[0][1] = '2';
    matrix[0][2] = '3';
    matrix[1][0] = '4';
    matrix[1][1] = '5';
    matrix[1][2] = '6';
    matrix[2][0] = '7';
    matrix[2][1] = '8';
    matrix[2][2] = '9';
}

void boardSetup()
{

    int x, y;
    if (system("CLS")) system("clear");
    cout << endl;
    for(y = 0; y < 3; y++)
    {
        cout << setw(34);
        for(x = 0; x< 3; x++)
        {
            if(x < 2)
            cout << matrix[y][x] << " | ";
            else if(y==0 and x==2)
            cout << matrix[y][x]<< setw(28) << "X wins | O wins";

            else
            cout << matrix[y][x];
        }
        if(y != 0 and y < 2)
        cout << endl << setw(33) << "" <<"- - - - -" << endl;
        else if(y == 0)
        cout << endl << setw(33) << "" <<"- - - - -" << setw(20) << xwins << "|" << owins << endl;
        else
        cout << endl << endl;
    }
}

void playerChoice(char turn)
{
    char choice;
    bool error;
    do
    {
        cout << setw(28) << "" << "\33[4mPress # to place "<< turn <<"\33[0m: ";
        cin >> choice;
        error = errorCheck(choice);
        if (error == true)
        {
            cout << endl << "Error! Please input a number that has not been selected from 1 to 9" << endl << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(error==true);
    if (choice == '1')
        matrix[0][0] = turn;
    else if (choice == '2')
        matrix[0][1] = turn;
    else if (choice == '3')
        matrix[0][2] = turn;
    else if (choice == '4')
        matrix[1][0] = turn;
    else if (choice == '5')
        matrix[1][1] = turn;
    else if (choice == '6')
        matrix[1][2] = turn;
    else if (choice == '7')
        matrix[2][0] = turn;
    else if (choice == '8')
        matrix[2][1] = turn;
    else if (choice == '9')
        matrix[2][2] = turn;
}

void computerChoice(char turn,int diff)
{
    char choice = '0';
    int num = 0;

    bool error = true;
    do
    {
        for(int cnt = 0; error == true and cnt < 200; cnt++)
        {
            choice = '0';
            num = computerLogic(turn,diff);
            choice += num;
            error = errorCheck(choice);
        }

        if(choice == '0')
        {
            choice = '0';
            for(int cnt = 0; cnt != 10; cnt++)
            {
                num = rand() % 9 + 1;
            }
            choice += num;
            num = 0;
            error = errorCheck(choice);
        }

    } while(error==true);
    if (choice == '1')
        matrix[0][0] = turn;
    else if (choice == '2')
        matrix[0][1] = turn;
    else if (choice == '3')
        matrix[0][2] = turn;
    else if (choice == '4')
        matrix[1][0] = turn;
    else if (choice == '5')
        matrix[1][1] = turn;
    else if (choice == '6')
        matrix[1][2] = turn;
    else if (choice == '7')
        matrix[2][0] = turn;
    else if (choice == '8')
        matrix[2][1] = turn;
    else if (choice == '9')
        matrix[2][2] = turn;
}

int computerLogic(char piece,int difficulty)
{
    char oppiece;
    if(piece == 'X')
        oppiece = 'O';
    else
        oppiece = 'X';
    int choiceult[4];
    int x=0;
    for(int i = 0; i < 4; i++)
        choiceult[i] = 0;
    int check;
    for(check = 0; check <= 23 && difficulty > 1; check++)
    {
        if(matrix[0][1] == matrix[0][2] and check <= 0 and matrix[0][0] == '1' ){
            if (matrix[0][1] == piece)
                choiceult[x] = 11;
            else
                choiceult[x] = 1;
            x++;
        }
        if(matrix[1][0] == matrix[2][0] and check == 1 and matrix[0][0] == '1' ){
            if (matrix[1][0] == piece)
                choiceult[x] = 11;
            else
                choiceult[x] = 1;
            x++;
        }
        if(matrix[1][1] == matrix[2][2] and check == 2 and matrix[0][0] == '1' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 11;
            else
                choiceult[x] = 1;
            x++;
        }
        if(matrix[0][0] == matrix[0][2] and check == 3 and matrix[0][1] == '2' ){
            if (matrix[0][0] == piece)
                choiceult[x] = 12;
            else
                choiceult[x] = 2;
            x++;
        }
        if(matrix[1][1] == matrix[2][1] and check == 4 and matrix[0][1] == '2' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 12;
            else
                choiceult[x] = 2;
            x++;
        }
        if(matrix[0][0] == matrix[0][1] and check == 5 and matrix[0][2] == '3' ){
            if (matrix[0][1] == piece)
                choiceult[x] = 13;
            else
                choiceult[x] = 3;
            x++;
        }
        if(matrix[1][1] == matrix[2][0] and check == 6 and matrix[0][2] == '3' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 13;
            else
                choiceult[x] = 3;
            x++;
        }
        if(matrix[1][2] == matrix[2][2] and check == 7 and matrix[0][2] == '3' ){
            if (matrix[1][2] == piece)
                choiceult[x] = 13;
            else
                choiceult[x] = 3;
            x++;
        }
        if(matrix[0][0] == matrix[2][0] and check == 8 and matrix[1][0] == '4' ){
            if (matrix[0][0] == piece)
                choiceult[x] = 14;
            else
                choiceult[x] = 4;
            x++;
        }
        if(matrix[1][1] == matrix[1][2] and check == 9 and matrix[1][0] == '4' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 14;
            else
                choiceult[x] = 4;
            x++;
        }
        if(matrix[0][0] == matrix[2][2] and check == 10 and matrix[1][1] == '5' ){
            if (matrix[0][0] == piece)
                choiceult[x] = 15;
            else
                choiceult[x] = 5;
            x++;
        }
        if(matrix[0][2] == matrix[2][0] and check == 11 and matrix[1][1] == '5' ){
            if (matrix[0][2] == piece)
                choiceult[x] = 15;
            else
                choiceult[x] = 5;
            x++;
        }
        if(matrix[0][1] == matrix[2][1] and check == 12 and matrix[1][1] == '5' ){
            if (matrix[0][1] == piece)
                choiceult[x] = 15;
            else
                choiceult[x] = 5;
            x++;
        }
        if(matrix[1][0] == matrix[1][2] and check == 13 and matrix[1][1] == '5' ){
            if (matrix[1][0] == piece)
                choiceult[x] = 15;
            else
                choiceult[x] = 5;
            x++;
        }
        if(matrix[1][1] == matrix[1][0] and check == 14 and matrix[1][2] == '6' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 16;
            else
                choiceult[x] = 6;
            x++;
        }
        if(matrix[0][2] == matrix[2][2] and check == 15 and matrix[1][2] == '6' ){
            if (matrix[0][2] == piece)
                choiceult[x] = 16;
            else
                choiceult[x] = 6;
            x++;
        }
        if(matrix[0][0] == matrix[1][0] and check == 16 and matrix[2][0] == '7' ){
            if (matrix[0][0] == piece)
                choiceult[x] = 17;
            else
                choiceult[x] = 7;
            x++;
        }
        if(matrix[1][1] == matrix[0][2] and check == 17 and matrix[2][0] == '7' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 17;
            else
                choiceult[x] = 7;
            x++;
        }
        if(matrix[2][1] == matrix[2][2] and check == 18 and matrix[2][0] == '7' ){
            if (matrix[2][1] == piece)
                choiceult[x] = 17;
            else
                choiceult[x] = 7;
            x++;
        }
        if(matrix[0][1] == matrix[1][1] and check == 19 and matrix[2][1] == '8' ){
            if (matrix[0][1] == piece)
                choiceult[x] = 18;
            else
                choiceult[x] = 8;
            x++;
        }
        if(matrix[2][0] == matrix[2][2] and check == 20 and matrix[2][1] == '8' ){
            if (matrix[2][2] == piece)
                choiceult[x] = 18;
            else
                choiceult[x] = 8;
            x++;
        }
        if(matrix[0][2] == matrix[1][2] and check == 21 and matrix[2][2] == '9' ){
            if (matrix[0][2] == piece)
                choiceult[x] = 19;
            else
                choiceult[x] = 9;
            x++;
        }
        if(matrix[0][0] == matrix[1][1] and check == 22 and matrix[2][2] == '9' ){
            if (matrix[1][1] == piece)
                choiceult[x] = 19;
            else
                choiceult[x] = 9;
            x++;
        }
        if(matrix[2][0] == matrix[2][1] and check == 23 and matrix[2][2] == '9' ){
            if (matrix[2][1] == piece)
                choiceult[x] = 19;
            else
                choiceult[x] = 9;
            x++;
        }
        for(int i = 0; i < 4 && check == 23; i++){
            if (choiceult[i] > 10)
                return choiceult[i] - 10;
        }
    }
    for(int i = 0; i < 4 && check == 24; i++){
        if (choiceult[i] > 0)
            return choiceult[i];
    }
    if(difficulty > 3){
        if(matrix[1][1] == piece){
            if(matrix[2][1] == oppiece && matrix[1][2] == oppiece && matrix[2][2] == '9' && matrix[2][0]=='7' && matrix[0][2] == '3'){
                return 9;
            }
            if(matrix[0][0] == piece){
                if(((matrix[0][1] == '2' && matrix[2][0] == '7')||(matrix[0][1] == '2' && matrix[2][2] == '9')||(matrix[2][0] == '7' && matrix[2][2] == '9')) && matrix[0][2] == '3')
                    return 3;
                if(((matrix[0][2] == '3' && matrix[1][0] == '4')||(matrix[0][2] == '3' && matrix[2][2] == '9')||(matrix[1][0] == '4' && matrix[2][2] == '9')) && matrix[2][0] == '7')
                    return 7;
            }
            if(matrix[0][2] == piece){
                if(((matrix[0][1] == '2' && matrix[2][0] == '7')||(matrix[0][1] == '2' && matrix[2][2] == '9')||(matrix[2][0] == '7' && matrix[2][2] == '9')) && matrix[0][0] == '1')
                    return 1;
                if(((matrix[1][2] == '6' && matrix[2][0] == '7')||(matrix[1][2] == '6' && matrix[0][0] == '1')||(matrix[2][0] == '7' && matrix[0][0] == '1')) && matrix[2][2] == '9')
                    return 9;
            }
            if(matrix[2][0] == piece){
                if(((matrix[0][2] == '3' && matrix[1][0] == '4')||(matrix[0][2] == '3' && matrix[2][2] == '9')||(matrix[1][0] == '4' && matrix[2][2] == '9')) && matrix[0][0] == '1')
                    return 1;
                if(((matrix[2][1] == '8' && matrix[0][2] == '3')||(matrix[2][1] == '8' && matrix[0][0] == '1')||(matrix[0][2] == '3' && matrix[0][0] == '1')) && matrix[2][2] == '9')
                    return 9;
            }
            if(matrix[2][2] == piece){
                if(((matrix[0][0] == '1' && matrix[2][0] == '7')||(matrix[1][2] == '6' && matrix[0][0] == '1')||(matrix[2][0] == '7' && matrix[1][2] == '6')) && matrix[0][2] == '3')
                    return 3;
                if(((matrix[0][2] == '3' && matrix[0][0] == '1')||(matrix[0][2] == '3' && matrix[2][1] == '8')||(matrix[0][0] == '1' && matrix[2][1] == '8')) && matrix[2][0] == '7')
                    return 7;
            }
        }
        if(matrix[1][1] == oppiece){
            if(matrix[0][0] == oppiece){
                if(((matrix[0][1] == '2' && matrix[2][0] == '7')||(matrix[0][1] == '2' && matrix[2][2] == '9')||(matrix[2][0] == '7' && matrix[2][2] == '9')) && matrix[0][2] == '3')
                    return 3;
                if(((matrix[0][2] == '3' && matrix[1][0] == '4')||(matrix[0][2] == '3' && matrix[2][2] == '9')||(matrix[1][0] == '4' && matrix[2][2] == '9')) && matrix[2][0] == '7')
                    return 7;
            }
            if(matrix[0][2] == oppiece){
                if(((matrix[0][1] == '2' && matrix[2][0] == '7')||(matrix[0][1] == '2' && matrix[2][2] == '9')||(matrix[2][0] == '7' && matrix[2][2] == '9')) && matrix[0][0] == '1')
                    return 1;
                if(((matrix[1][2] == '6' && matrix[2][0] == '7')||(matrix[1][2] == '6' && matrix[0][0] == '1')||(matrix[2][0] == '7' && matrix[0][0] == '1')) && matrix[2][2] == '9')
                    return 9;
            }
            if(matrix[2][0] == oppiece){
                if(((matrix[0][2] == '3' && matrix[1][0] == '4')||(matrix[0][2] == '3' && matrix[2][2] == '9')||(matrix[1][0] == '4' && matrix[2][2] == '9')) && matrix[0][0] == '1')
                    return 1;
                if(((matrix[2][1] == '8' && matrix[0][2] == '3')||(matrix[2][1] == '8' && matrix[0][0] == '1')||(matrix[0][2] == '3' && matrix[0][0] == '1')) && matrix[2][2] == '9')
                    return 9;
            }
            if(matrix[2][2] == oppiece){
                if(((matrix[0][0] == '1' && matrix[2][0] == '7')||(matrix[1][2] == '6' && matrix[0][0] == '1')||(matrix[2][0] == '7' && matrix[1][2] == '6')) && matrix[0][2] == '3')
                    return 3;
                if(((matrix[0][2] == '3' && matrix[0][0] == '1')||(matrix[0][2] == '3' && matrix[2][1] == '8')||(matrix[0][0] == '1' && matrix[2][1] == '8')) && matrix[2][0] == '7')
                    return 7;
            }
        }
        if((matrix[0][0] == oppiece && matrix[2][2] == oppiece)||(matrix[0][2] == oppiece && matrix[2][0] == oppiece))
            return 2;
    }
    if(difficulty > 2){
        if(matrix[1][1] == '5')
            return 5;
        if(matrix[2][2] == oppiece && matrix[0][0] == '1')
            return 1;
        if(matrix[2][0] == oppiece && matrix[0][2] == '3')
            return 3;
        if(matrix[0][2] == oppiece && matrix[2][0] == '7')
            return 7;
        if(matrix[0][0] == oppiece && matrix[2][2] == '9')
            return 9;
        if(matrix[0][0] == '1')
            return 1;
        if(matrix[0][2] == '3')
            return 3;
        if(matrix[2][0] == '7')
            return 7;
        if(matrix[2][2] == '9')
            return 9;
    }
    return 0;
}

//Win: If you have two in a row, play the third to get three in a row.
//Block: If the opponent has two in a row, play the third to block them.
//Fork: Create an opportunity where you can win in two ways.
//Block Opponent's Fork:

//Option 1: Create two in a row to force the opponent into defending, as long as it doesn't result in them creating a fork or winning. For example, if "X" has a corner, "O" has the center, and "X" has the opposite corner as well, "O" must not play a corner in order to win. (Playing a corner in this scenario creates a fork for "X" to win.)

//Option 2: If there is a configuration where the opponent can fork, block that fork.
//Center: Play the center.
//Opposite Corner: If the opponent is in the corner, play the opposite corner.
//Empty Corner: Play an empty corner.
//Empty Side: Play an empty side.


bool errorCheck(char num)
{
    int x=0,y=0;
    switch(num)
    {
        case '9':   x++;
        case '8':   x++;
        case '7':   y++;
                    y++;
                    break;
        case '6':   x++;
        case '5':   x++;
        case '4':   y++;
                    break;
        case '3':   x++;
        case '2':   x++;
        case '1':   break;
    }
    if(num >= '1' and num <= '9')
    {
            if (matrix[y][x] == num)
                return false;
            else
                return true;
    }
    else
    {
        return true;
    }
}

bool gameWin(char player)
{
    bool win;
    if (matrix[0][0] == matrix[0][1] and matrix[0][1] == matrix[0][2])
        win = true;
    else if (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2])
        win = true;
    else if (matrix[2][0] == matrix[2][1] and matrix[2][1] == matrix[2][2])
        win = true;
    else if (matrix[0][0] == matrix[1][0] and matrix[1][0] == matrix[2][0])
        win = true;
    else if (matrix[0][1] == matrix[1][1] and matrix[1][1] == matrix[2][1])
        win = true;
    else if (matrix[0][2] == matrix[1][2] and matrix[1][2] == matrix[2][2])
        win = true;
    else if (matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2])
        win = true;
    else if (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2])
        win = true;
    else
        win = false;
    if(win == true)
    {
        if(player == 'X')
        {
            xwins++;
            boardSetup();
            cout << "X-cellent! ";

        }
        else
        {
            owins++;
            boardSetup();
            cout << "O-mazing! ";

        }
        cout << player << " Wins the game!" << endl;
        return true;
    }
    else
        return false;
}

bool gameDraw()
{
    if(matrix[0][0] != '1' and matrix[0][1] != '2' and matrix[0][2] != '3'
       and matrix[1][0] != '4' and matrix[1][1] != '5' and matrix[1][2] != '6'
       and matrix[2][0] != '7' and matrix[2][1] != '8' and matrix[2][2] != '9')
        {
            cout << "Game is a draw!" << endl;
            return true;
        }
    else
        return false;
}
