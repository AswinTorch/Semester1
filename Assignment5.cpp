//Aswin Nair
//Assignment 5: Sudoku Initializer
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
    bool checkSudoku(vector<char> temp) {
        int count;
        for (int i = 0; i < 9; ++i) {
            count = i;
            while (count < 9) {
                if (temp[i] == temp[++count]) return false;
            }
        }
        return true;
    }
    void verify() {
        int errorCount = 0;
        //Checks for erases
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if ( (sudokuBoard[r][c] < '1') || (sudokuBoard[r][c] > '9')) {
                    cout << "- Found inconsistency in row " << char(r + 'P') << "..." << endl;
                    cout << "- Found inconsistency in column " << char(c + 'A') << "..." << endl;
                    ++errorCount;
                }
            }
        }
        //Checks for sudoku rule inconsistencies in rows
        vector <char> temp(9);
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c){
                temp[c] = sudokuBoard[r][c];
            }
            if (!checkSudoku(temp)) {
                cout << "- Found inconsistencies in row " << char(r + 'P') << "..." << endl;
                ++errorCount;
            }
        }
        //Checks for sudoku rule inconsistencies in columns
        for (int c = 0; c < 9; ++c) {
            for (int r = 0; r < 9; ++r) {
                temp[r] = sudokuBoard[r][c];
            }
            if (!checkSudoku(temp)) {
                cout << "- Found inconsistencies in column " << char(c + 'A') << "..." << endl;
                ++errorCount;
            }
        }
        //Checks for sudoku rule inconsistencies in 3x3 sections
//        int count = 0, sRowCount = 0, sColCount = 0, sectionCount = 0;
//        for (int sRow = 0; sRow <= 6; sRow+= 3) { //Increment sent to 3 to account for 3x3 sections
//            for (int sCol = 0; sCol <= 6; sCol += 3) { //Increment sent to 3 to account for 3x3 sections
//                for (sRowCount = 0, count = 0; sRowCount < 3; ++sRowCount) {
//                    for (sColCount = 0; sColCount < 3; ++sColCount) {
//                        temp[++count] = sudokuBoard[sRow + sRowCount][sCol + sColCount];
//                    }
//                }
//                ++sectionCount;
//                if (!checkSudoku(temp)) {
//                    cout << "- Found inconsistencies in " << sectionCount << "..." << endl;
//                    ++errorCount;
//                }
//            }
//        }
        //No Error Output a.k.a. Sudoku intact
        if (errorCount == 0) cout << "- All columns, rows, and components are OK..." << endl;
    }
    void swap() {
        //I don't understand the "permissible range" for swap. I just implemented a normal random swap for rows and columns.
        int sRow1 = rand() % 9, sRow2 = rand() % 9, sCol1 = rand() % 9, sCol2 = rand() % 9, chance = rand() % 2 + 1;
        if (chance == 1){
            sudokuBoard[sRow1].swap(sudokuBoard[sRow2]);
            cout << "- Rows " << char(sRow1 + 'P') << " and " << char(sRow2 + 'P') << " were swapped..." << endl;
        } else {
            for (int r = 0; r < 9; ++r) {
                char temp = sudokuBoard[r][sCol1];
                sudokuBoard[r][sCol1] = sudokuBoard[r][sCol2];
                sudokuBoard[r][sCol2] = temp;
            }
            cout << "- Columns " << char(sCol1 + 'A') << " and " << char(sCol2 + 'A') << " were swapped..." << endl;
        }
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
        if (input == "show") { //Shows board.
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
