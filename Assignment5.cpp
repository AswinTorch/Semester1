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
        //Hardcoded board that follows the rules taken from Blackboard Example Output
        vector<char> a_row(9);
        a_row = {'2', '3', '4', '8', '9', '1', '5', '6', '7'}; sudokuBoard.push_back(a_row);
        a_row = {'5', '6', '7', '2', '3', '4', '8', '9', '1'}; sudokuBoard.push_back(a_row);
        a_row = {'8', '9', '1', '5', '6', '7', '2', '3', '4'}; sudokuBoard.push_back(a_row);
        a_row = {'3', '4', '5', '9', '1', '2', '6', '7', '8'}; sudokuBoard.push_back(a_row);
        a_row = {'6', '7', '8', '3', '4', '5', '9', '1', '2'}; sudokuBoard.push_back(a_row);
        a_row = {'9', '1', '2', '6', '7', '8', '3', '4', '5'}; sudokuBoard.push_back(a_row);
        a_row = {'1', '2', '3', '7', '8', '9', '4', '5', '6'}; sudokuBoard.push_back(a_row);
        a_row = {'4', '5', '6', '1', '2', '3', '7', '8', '9'}; sudokuBoard.push_back(a_row);
        a_row = {'7', '8', '9', '4', '5', '6', '1', '2', '3'}; sudokuBoard.push_back(a_row);
    }
    void erase () {
        int row = rand() % 9, column = rand() % 9;
        sudokuBoard[row][column] = '-';
        cout << "Erasing row " << char(row + 'P') << " column " << char(column + 'A') << endl;
    }
    void checkSector (){

    }
    void verify() {
        bool val1 = false, val2 = false, val3 = false, val4 = false, val5 = false, val6 = false;
        bool val7 = false, val8 = false, val9 = false;
        int row = 0, col = 0;
        for (int a = 0; a < sudokuBoard[row].size(); ++a) {
            if (sudokuBoard[row][col] == '1') val1 = !val1;
            else if (sudokuBoard[row][col] == '2') val2 = !val2;
            else if (sudokuBoard[row][col] == '3') val3 = !val3;
            else if (sudokuBoard[row][col] == '4') val4 = !val4;
            else if (sudokuBoard[row][col] == '5') val5 = !val5;
            else if (sudokuBoard[row][col] == '6') val6 = !val6;
            else if (sudokuBoard[row][col] == '7') val7 = !val7;
            else if (sudokuBoard[row][col] == '8') val8 = !val8;
            else if (sudokuBoard[row][col] == '9') val9 = !val9;
            ++col;
        }
        bool resultRow = (val1 && val2 && val3 && val4 && val5 && val6 && val7 && val8 && val9);

        val1 = false, val2 = false, val3 = false, val4 = false, val5 = false, val6 = false;
        val7 = false, val8 = false, val9 = false;
        row = 0, col = 0;
        for (int b = 0; b < sudokuBoard[col].size(); ++b) {
            if (sudokuBoard[row][col] == '1') val1 = !val1;
            else if (sudokuBoard[row][col] == '2') val2 = !val2;
            else if (sudokuBoard[row][col] == '3') val3 = !val3;
            else if (sudokuBoard[row][col] == '4') val4 = !val4;
            else if (sudokuBoard[row][col] == '5') val5 = !val5;
            else if (sudokuBoard[row][col] == '6') val6 = !val6;
            else if (sudokuBoard[row][col] == '7') val7 = !val7;
            else if (sudokuBoard[row][col] == '8') val8 = !val8;
            else if (sudokuBoard[row][col] == '9') val9 = !val9;
            ++row;
        }
        bool resultCol = (val1 && val2 && val3 && val4 && val5 && val6 && val7 && val8 && val9);
        checkSector();
        if (resultCol && resultRow){
            cout << "All columns, rows, and components are OK..." << endl;
        } else cout << "Not sudoku" << endl;
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
