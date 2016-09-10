#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
    int playerMoney = 100, machineMoney = 100;
    int playerDice1, playerDice2, playerDice3, machineDice1, machineDice2, machineDice3;
    int playerBet, playerTotalScore, machineTotalScore, roundNumber = 0;
    srand(time(0));
    //Loop
    while (true) {
        playerDice1 = rand() % 6 + 1, playerDice2 = rand() % 6 + 1, playerDice3 = rand() % 6 + 1;                       //Random dice rolling
        machineDice1 = rand() % 6 + 1, machineDice2 = rand() % 6 + 1, machineDice3 = rand() % 6 + 1;
        ++roundNumber;                                                                                                  //Changes round number
        cout << "[Round " << roundNumber << "] You rolled ( " << playerDice1 << ", " << playerDice2 << ", " << "? ) ";
        cout << "and the Machine rolled ( " << machineDice1 << ", " << machineDice2 << ", " << "? ).\n";
        cout << "How much will you bet: ";
        cin >> playerBet;
        while (playerBet > 10 || playerBet < 1) {                                                                       //If bet > 10 or < 1, resets.
            cout << "Your bet must be between $1 - $10 , how much will you bet: ";
            cin >> playerBet;
        }
        cout << "You had ( " << playerDice1 << ", " << playerDice2 << ", " << playerDice3 << " ) --> ";                 //Player Stuff
        if (playerDice1 == playerDice2 && playerDice2 == playerDice3){
            cout << "BIG FISH!";
        }
        else if (max(max(playerDice1, playerDice2), playerDice3) == playerDice1){
            playerDice2 = rand() % 6 + 1;
            playerDice3 = rand() % 6 + 1;
            cout << "You rolled ( " << playerDice2 << ", " << playerDice3 << " ) --> ";
            if (max(playerDice2, playerDice3) == playerDice2){
                playerDice3 = rand() % 6 + 1;
                cout << "You rolled ( " << playerDice3 << " ) --> ";
            }
            else if (max(playerDice2, playerDice3) == playerDice3){
                playerDice2 = rand() % 6 + 1;
                cout << "You rolled ( " << playerDice2 << " ) --> ";
            }
            playerTotalScore = playerDice1 + playerDice2 + playerDice3;
            cout << "You scored " << playerTotalScore << ".";
        }
        else if (max(max(playerDice1, playerDice2), playerDice3) == playerDice2){
            playerDice1 = rand() % 6 + 1;
            playerDice3 = rand() % 6 + 1;
            cout << "You rolled ( " << playerDice1 << ", " << playerDice3 << " ) --> ";
            if (max(playerDice1, playerDice3) == playerDice1){
                playerDice3 = rand() % 6 + 1;
                cout << "You rolled ( " << playerDice3 << " ) --> ";
            }
            else if (max(playerDice1, playerDice3) == playerDice3){
                playerDice1 = rand() % 6 + 1;
                cout << "You rolled ( " << playerDice1 << " ) --> ";
            }
            playerTotalScore = playerDice1 + playerDice2 + playerDice3;
            cout << "You scored " << playerTotalScore << ".";
        }
        else if (max(max(playerDice1, playerDice2), playerDice3) == playerDice3){
            playerDice1 = rand() % 6 + 1;
            playerDice2 = rand() % 6 + 1;
            cout << "You rolled ( " << playerDice1 << ", " << playerDice2 << " ) --> ";
            if (max(playerDice1, playerDice2) == playerDice1){
                playerDice2 = rand() % 6 + 1;
                cout << "You rolled ( " << playerDice2 << " ) --> ";
            }
            else if (max(playerDice1, playerDice2) == playerDice2){
                playerDice1 = rand() % 6 + 1;
                cout << "You rolled ( " << playerDice1 << " ) --> ";
            }
            playerTotalScore = playerDice1 + playerDice2 + playerDice3;
            cout << "You scored " << playerTotalScore << ".";
        }
        else cout << "Oops, something went wrong.";
        cout << "\nMachine had ( " << machineDice1 << ", " << machineDice2 << ", " << machineDice3 << " ) --> ";        //Machine Stuff
        if (machineDice1 == machineDice2 && machineDice2 == machineDice3) {
            cout << "BIG FISH!";
        }
        else if (max(max(machineDice1, machineDice2), machineDice3) == machineDice1){
            machineDice2 = rand() % 6 + 1;
            machineDice3 = rand() % 6 + 1;
            cout << "Machine rolled ( " << machineDice2 << ", " << machineDice3 << " ) --> ";
            if (max(machineDice2, machineDice3) == machineDice2){
                machineDice3 = rand() % 6 + 1;
                cout << "Machine rolled ( " << machineDice3 << " ) --> ";
            }
            else if (max(machineDice2, machineDice3) == machineDice3){
                machineDice2 = rand() % 6 + 1;
                cout << "Machine rolled ( " << machineDice2 << " ) --> ";
            }
            machineTotalScore = machineDice1 + machineDice2 + machineDice3;
            cout << "Machine scored " << machineTotalScore << ".";
        }
        else if (max(max(machineDice1, machineDice2), machineDice3) == machineDice2){
            machineDice1 = rand() % 6 + 1;
            machineDice3 = rand() % 6 + 1;
            cout << "Machine rolled ( " << machineDice1 << ", " << machineDice3 << " ) --> ";
            if (max(machineDice1, machineDice3) == machineDice1){
                machineDice3 = rand() % 6 + 1;
                cout << "Machine rolled ( " << machineDice3 << " ) --> ";
            }
            else if (max(machineDice1, machineDice3) == machineDice3){
                machineDice1 = rand() % 6 + 1;
                cout << "Machine rolled ( " << machineDice1 << " ) --> ";
            }
            machineTotalScore = machineDice1 + machineDice2 + machineDice3;
            cout << "Machine scored " << machineTotalScore << ".";
        }
        else if (max(max(machineDice1, machineDice2), machineDice3) == machineDice3){
            machineDice1 = rand() % 6 + 1;
            machineDice2 = rand() % 6 + 1;
            cout << "Machine rolled ( " << machineDice1 << ", " << machineDice2 << " ) --> ";
            if (max(machineDice1, machineDice2) == machineDice1){
                machineDice2 = rand() % 6 + 1;
                cout << "Machine rolled ( " << machineDice2 << " ) --> ";
            }
            else if (max(machineDice1, machineDice2) == machineDice2){
                machineDice1 = rand() % 6 + 1;
                cout << "Machine rolled ( " << machineDice1 << " ) --> ";
            }
            machineTotalScore = machineDice1 + machineDice2 + machineDice3;
            cout << "Machine scored " << machineTotalScore << ".";
        }
        else cout << "Oops, something went wrong.";
        //Win or Lose
        if (playerDice1 == playerDice2 && playerDice2 == playerDice3){
            playerMoney += playerBet * 50;
            machineMoney -= playerBet * 50;
        }
        else if (machineDice1 == machineDice2 && machineDice2 == machineDice3){
            machineMoney += playerBet * 50;
            playerMoney -= playerBet * 50;
        }
        else {
            playerMoney += playerBet * (playerTotalScore - machineTotalScore);
            machineMoney -= playerBet * (playerTotalScore - machineTotalScore);
        }
        cout << (playerTotalScore >= machineTotalScore ? "\nYou won! " : "\nYou lost! ");
        cout << "You have $" << playerMoney << " and the machine has $" << machineMoney << ". \n=============================\n";
        if (playerMoney  <= 0 || machineMoney <= 0){                                                                    //Get out of loop
            break;
        }
    }
    if (playerMoney <= 0){                                                                                              //ENDGAME
        cout << "YOU LOST THE GAME! :( \n";
    }
    else if (machineMoney <= 0){
        cout << "YOU WON THE GAME! :) \n";
    }
    else if (playerMoney <= 0 && machineMoney <= 0){
        cout << "IT'S A TIE!";
    } else cout << "Something went wrong!";
}
