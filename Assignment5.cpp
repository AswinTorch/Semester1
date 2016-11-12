//Aswin Nair
//Assignment 5: Sudoku Initializer
//Assignment not finished, only show and erase function works completely.
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

class Board {
    vector <vector <char> > sudokuBoard;
public:
    Board(){
        //Hard-coded board that follows the rules taken from Blackboard Example Output
        vector<char> row(9);
        row = {'2', '3', '4', '8', '9', '1', '5', '6', '7'}; sudokuBoard.push_back(row);
        row = {'5', '6', '7', '2', '3', '4', '8', '9', '1'}; sudokuBoard.push_back(row);
        row = {'8', '9', '1', '5', '6', '7', '2', '3', '4'}; sudokuBoard.push_back(row);
        row = {'3', '4', '5', '9', '1', '2', '6', '7', '8'}; sudokuBoard.push_back(row);
        row = {'6', '7', '8', '3', '4', '5', '9', '1', '2'}; sudokuBoard.push_back(row);
        row = {'9', '1', '2', '6', '7', '8', '3', '4', '5'}; sudokuBoard.push_back(row);
        row = {'1', '2', '3', '7', '8', '9', '4', '5', '6'}; sudokuBoard.push_back(row);
        row = {'4', '5', '6', '1', '2', '3', '7', '8', '9'}; sudokuBoard.push_back(row);
        row = {'7', '8', '9', '4', '5', '6', '1', '2', '3'}; sudokuBoard.push_back(row);
    }
    void erase () {
        int row = rand() % 9, column = rand() % 9;
        sudokuBoard[row][column] = '-';
        cout << "Erasing row " << char(row + 'P') << " column " << char(column + 'A') << endl;
    }
    void verify() {

    }
    void swap() {

    }
    friend ostream& operator << (ostream& o, const Board& b){
        cout << "   ";
        for (int col = 0; col < 9; ++col) o << setw(3) << char('A' + col);
        o << endl;
        for (int row = 0; row < 9; ++row){
            o << setw(3) << char('P' + row);
            for (int col = 0; col < 9; ++col) o << setw(3) << b.sudokuBoard[row][col];
            o << endl;
        }
        return o;
    }
};

void showBoard (Board b) {cout << b;}


int main() {
    srand(unsigned(time(0)));
    Board b; string input;

    //Start of Game
    cout << "Welcome to Sudoku Initializer!" << endl;
    while (true){
        cout << "> "; cin >> input;
        if (input == "show") { //Shows board if input is show.
            showBoard(b);
        } else if (input == "swap"){ //Swaps random row/column positions.
            b.swap();
        } else if (input == "erase"){ //Erases random cell and replaces with dash.
            b.erase();
        } else if (input == "verify"){ //Verifies the board according to sudoku rules.
            b.verify();
        } else if (input == "quit") { //Quits game.
            cout << "Bye..."; return 0;
        } else cout << "Please enter a valid command." << endl; //Error check for valid commands.
    }
}
