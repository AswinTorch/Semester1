#define AUTO_INPUT                       //Comment this line out to end simulation and allow the player to input bet.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int roll() {return rand() % 6 + 1;}
int maxFunction(int a, int b, int c, int score){
    b = roll(), c = roll();
    cout << "You rolled ( " << b << ", " << c << " ) --> ";
    if (max(b, c) == b){
        c = roll();
        cout << "You rolled ( " << c << " ) --> ";
    }
    else if (max(b, c) == c){
        b = roll();
        cout << "You rolled ( " << b << " ) --> ";
    }
    score = a + b + c;
    cout << "You scored " << score << ".";
    return score;
}

int main() {
    int playerMoney = 1000, machineMoney = 1000;
    int playerDice1, playerDice2, playerDice3, machineDice1, machineDice2, machineDice3;
    int playerBet, playerTotalScore, machineTotalScore, roundNumber = 0;
    srand(time(0));
    //Loop
    while (true) {
        playerDice1 = roll(), playerDice2 = roll(), playerDice3 = roll();                                               //Random dice rolling
        machineDice1 = roll(), machineDice2 = roll(), machineDice3 = roll();
        ++roundNumber;                                                                                                  //Changes round number
        cout << "[Round " << roundNumber << "] You rolled ( " << playerDice1 << ", " << playerDice2 << ", " << "? ) ";
        cout << "and the Machine rolled ( " << machineDice1 << ", " << machineDice2 << ", " << "? ).\n";
#ifndef AUTO_INPUT
        cout << "How much will you bet: ";
        cin >> playerBet;
        while (playerBet > 10 || playerBet < 1) {                                                                       //If bet > 10 or < 1, resets.
            cout << "Your bet must be between $1 - $10 , how much will you bet: ";
            cin >> playerBet;
        }
#else                                                                                                                   //Simulation
        if (playerDice1 == playerDice2){
            playerBet = 10;
        }
        else if (machineDice1 == machineDice2){
            playerBet = 1;
        } else playerBet = rand() % 5 + 1;
        cout << "You have automatically bet: " << playerBet << endl;
#endif
        cout << "You had ( " << playerDice1 << ", " << playerDice2 << ", " << playerDice3 << " ) --> ";                 //Player Stuff
        if (playerDice1 == playerDice2 && playerDice2 == playerDice3){
            cout << "BIG FISH!";
        }
        else if (max(max(playerDice1, playerDice2), playerDice3) == playerDice1){
            playerTotalScore = maxFunction(playerDice1, playerDice2, playerDice3, playerTotalScore);                                                                      //Calls function to test max
        }
        else if (max(max(playerDice1, playerDice2), playerDice3) == playerDice2){
            playerTotalScore = maxFunction(playerDice2, playerDice1, playerDice3, playerTotalScore);                                                                      //Calls function to test max
        }
        else if (max(max(playerDice1, playerDice2), playerDice3) == playerDice3){
            playerTotalScore = maxFunction(playerDice3, playerDice2, playerDice1, playerTotalScore);                                                                      //Calls function to test max
        } else cout << "Oops, something went wrong.";
        cout << "\nMachine had ( " << machineDice1 << ", " << machineDice2 << ", " << machineDice3 << " ) --> ";        //Machine Stuff
        if (machineDice1 == machineDice2 && machineDice2 == machineDice3) {
            cout << "BIG FISH!";
        }
        else if (max(max(machineDice1, machineDice2), machineDice3) == machineDice1){
            machineTotalScore = maxFunction(machineDice1, machineDice2, machineDice3, machineTotalScore);
        }
        else if (max(max(machineDice1, machineDice2), machineDice3) == machineDice2){
            machineTotalScore = maxFunction(machineDice2, machineDice1, machineDice3, machineTotalScore);
        }
        else if (max(max(machineDice1, machineDice2), machineDice3) == machineDice3){
            machineTotalScore = maxFunction(machineDice3, machineDice2, machineDice1, machineTotalScore);
        } else cout << "Oops, something went wrong.";
        //WIN OR LOSE
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
        if (playerDice1 == playerDice2 && playerDice2 == playerDice3){
            cout << "\nYou won!";
        }
        else if (machineDice1 == machineDice2 && machineDice2 == machineDice3){
            cout << "\nYou lost!";
        } else cout << (playerTotalScore >= machineTotalScore ? "\nYou won! " : "\nYou lost! ");
        cout << "You have $" << playerMoney << " and the machine has $" << machineMoney << ". \n=============================\n";
        if (playerMoney  <= 0 || machineMoney <= 0) break;                                                              //Get out of loop
    }
    if (playerMoney <= 0){                                                                                              //ENDGAME
        cout << "YOU LOST THE GAME! :( \n";
    }
    else if (machineMoney <= 0){
        cout << "YOU WON THE GAME! :) \n";
    } else cout << "Something went wrong!";
}
