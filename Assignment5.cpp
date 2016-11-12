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
    void verify() {
        bool isValid = true;
        vector<char> comp1(9), comp2(9), comp3(9), comp4(9), comp5(9), comp6(9), comp7(9), comp8(9), comp9(9);
        comp1.push_back(sudokuBoard[0][0]); comp1.push_back(sudokuBoard[0][1]); comp1.push_back(sudokuBoard[0][2]);
        comp1.push_back(sudokuBoard[1][0]); comp1.push_back(sudokuBoard[1][1]); comp1.push_back(sudokuBoard[1][2]);
        comp1.push_back(sudokuBoard[2][0]); comp1.push_back(sudokuBoard[2][1]); comp1.push_back(sudokuBoard[2][2]);

        comp2.push_back(sudokuBoard[0][3]); comp2.push_back(sudokuBoard[0][4]); comp2.push_back(sudokuBoard[0][5]);
        comp2.push_back(sudokuBoard[1][3]); comp2.push_back(sudokuBoard[1][4]); comp2.push_back(sudokuBoard[1][5]);
        comp2.push_back(sudokuBoard[2][3]); comp2.push_back(sudokuBoard[2][4]); comp2.push_back(sudokuBoard[2][5]);

        comp3.push_back(sudokuBoard[0][6]); comp3.push_back(sudokuBoard[0][7]); comp3.push_back(sudokuBoard[0][8]);
        comp3.push_back(sudokuBoard[1][6]); comp3.push_back(sudokuBoard[1][7]); comp3.push_back(sudokuBoard[1][8]);
        comp3.push_back(sudokuBoard[2][6]); comp3.push_back(sudokuBoard[2][7]); comp3.push_back(sudokuBoard[2][8]);

        comp4.push_back(sudokuBoard[3][0]); comp4.push_back(sudokuBoard[3][1]); comp4.push_back(sudokuBoard[3][2]);
        comp4.push_back(sudokuBoard[4][0]); comp4.push_back(sudokuBoard[4][1]); comp4.push_back(sudokuBoard[4][2]);
        comp4.push_back(sudokuBoard[5][0]); comp4.push_back(sudokuBoard[5][1]); comp4.push_back(sudokuBoard[5][2]);

        comp5.push_back(sudokuBoard[3][3]); comp5.push_back(sudokuBoard[3][4]); comp5.push_back(sudokuBoard[3][5]);
        comp5.push_back(sudokuBoard[4][3]); comp5.push_back(sudokuBoard[4][4]); comp5.push_back(sudokuBoard[4][5]);
        comp5.push_back(sudokuBoard[5][3]); comp5.push_back(sudokuBoard[5][4]); comp5.push_back(sudokuBoard[5][5]);

        comp6.push_back(sudokuBoard[3][6]); comp6.push_back(sudokuBoard[3][7]); comp6.push_back(sudokuBoard[3][8]);
        comp6.push_back(sudokuBoard[4][6]); comp6.push_back(sudokuBoard[4][7]); comp6.push_back(sudokuBoard[4][8]);
        comp6.push_back(sudokuBoard[5][6]); comp6.push_back(sudokuBoard[5][7]); comp6.push_back(sudokuBoard[5][8]);

        comp7.push_back(sudokuBoard[6][0]); comp7.push_back(sudokuBoard[6][1]); comp7.push_back(sudokuBoard[6][2]);
        comp7.push_back(sudokuBoard[7][0]); comp7.push_back(sudokuBoard[7][1]); comp7.push_back(sudokuBoard[7][2]);
        comp7.push_back(sudokuBoard[8][0]); comp7.push_back(sudokuBoard[8][1]); comp7.push_back(sudokuBoard[8][2]);

        comp8.push_back(sudokuBoard[6][3]); comp8.push_back(sudokuBoard[6][4]); comp8.push_back(sudokuBoard[6][5]);
        comp8.push_back(sudokuBoard[7][3]); comp8.push_back(sudokuBoard[7][4]); comp8.push_back(sudokuBoard[7][5]);
        comp8.push_back(sudokuBoard[8][3]); comp8.push_back(sudokuBoard[8][4]); comp8.push_back(sudokuBoard[8][5]);

        comp9.push_back(sudokuBoard[6][6]); comp9.push_back(sudokuBoard[6][7]); comp9.push_back(sudokuBoard[6][8]);
        comp9.push_back(sudokuBoard[7][6]); comp9.push_back(sudokuBoard[7][7]); comp9.push_back(sudokuBoard[7][8]);
        comp9.push_back(sudokuBoard[8][6]); comp9.push_back(sudokuBoard[8][7]); comp9.push_back(sudokuBoard[8][8]);


        //Checks each component (9 of 3x3 boxes) for repeating chars.
        for (int a = 1; a < 9; ++a) {
            if (comp1[0] == comp1[a]) isValid = false;
            if (comp2[0] == comp2[a]) isValid = false;
            if (comp3[0] == comp3[a]) isValid = false;
            if (comp4[0] == comp4[a]) isValid = false;
            if (comp5[0] == comp5[a]) isValid = false;
            if (comp6[0] == comp6[a]) isValid = false;
            if (comp7[0] == comp7[a]) isValid = false;
            if (comp8[0] == comp8[a]) isValid = false;
            if (comp9[0] == comp9[a]) isValid = false;
        }

        if (isValid){
            cout << "All columns, rows, and components are OK..." << endl;
        } else cout << "Inconsistencies in : " << endl;
        comp1.clear(); comp2.clear(); comp3.clear(); comp4.clear(); comp5.clear(); comp6.clear(); comp7.clear();
        comp8.clear(); comp9.clear();
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
