#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

int randInt(int a, int b) {return (rand() % b + a);}

int main() {
    srand(time(0));
    int playerPoints = 1000;
    string randomString, playerInput;

    while (true) {                                                                                                      //Main loop
        int count = 0, totalOffset = 0, offSet, totalPenalty = 0;
        cout << "\nYour current points: " << playerPoints << " , just type -> ";
        for (int a = 0; a < 7; ++a) {                                                                                   //Loop to assign chars to string randomly
            if ((rand() % 10 + 1) <= 2) {                                                                               //Numbers or Non alphanumeric chars 50% chance
                if ((rand() % 2 + 1) == 1) {
                    randomString[a] = randInt(48, 10);                                                                  //Numbers from 0-9
                    cout << randomString[a];
                } else {
                    randomString[a] = randInt(33, 15);                                                                  //Non-alphanumeric characters
                    cout << randomString[a];
                }
            } else {                                                                                                    //Upper or lower case letters 50% chance
                if ((rand() % 2 + 1) == 1) {
                    randomString[a] = randInt(65, 26);                                                                  //Capital letters
                    cout << randomString[a];
                } else {
                    randomString[a] = randInt(97, 26);                                                                  //Lowercase letters
                    cout << randomString[a];
                }
            }
        }
        auto startTimer = chrono::steady_clock::now();                                                                       //Starts timer when input begins
        cout << ": "; cin >> playerInput;
        auto endTimer = chrono::steady_clock::now();                                                                         //Ends timer after input finishes

        for (int b = 0; b < 7; ++b){                                                                                    //Checks if input matches random string
            if (playerInput[b] == randomString[b]){
                count++;
            }
            else {
                offSet = playerInput[b] - randomString[b];                                                              //Calculates total offset
                totalOffset += abs(offSet);
            }
        }
        auto diffTimer = endTimer - startTimer;
        auto timeElapsed = chrono::duration_cast<chrono::milliseconds>(diffTimer).count();
        cout << timeElapsed << " milliseconds, ";                                                                       //Calculates and displays time elapsed
        if (timeElapsed <= 7000){
            cout << "you made it within the interval of 7000...";
        } else cout << "you *failed* it within the interval of 7000...";

        if (timeElapsed <= 7000 && count == 7){
            totalPenalty += 500;
            playerPoints += totalPenalty;
        } else if (timeElapsed <= 7000 && count < 7){
            totalPenalty -= totalOffset;
            playerPoints += totalPenalty;
        } else if (timeElapsed > 7000 && count == 7){                                                                   //Calculating penalty
            totalPenalty -= (timeElapsed - 7000);
            playerPoints += totalPenalty;
        } else if (timeElapsed > 7000 && count < 7){
            totalPenalty -= (timeElapsed - 7000);
            totalPenalty -= totalOffset;
            playerPoints += totalPenalty;
        } else cout << "Something's wrong.";

        if (count < 7){
            cout << "\nString offset is " << totalOffset << ", ";                                                       //Displays total offset and penalty
            cout << "your total penalty is " << abs(totalPenalty) << "...";
        } else //No offset

        playerPoints;                                                                                                   //Loop doesn't break unless this is here
        if (playerPoints <= 0 || playerPoints >= 5000) break;                                                           //Case that breaks out of loop
    }
    cout << "\n=================================================";
    cout << "\nYour points: " << playerPoints << endl;
    cout << (playerPoints >= 5000 ? "You won!" : "You lost!");                                                          //Win or Lose
}
