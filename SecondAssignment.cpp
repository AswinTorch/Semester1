//Aswin Nair
//Assignment 2
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std; using namespace chrono;

int randInt(int a, int b) {return (rand() % b + a);}                                                                    //RNG for chars upper case and lower case
int main() {
    srand(time(0));
    int playerPoints = 1000;

    while (true) {                                                                                                      //Main loop
        int count = 0, totalOffset = 0, totalPenalty = 0;
        bool inputMatchesString, inputLargerThanSeven;
        string randomString, stringInput;

        cout << "\nYour current points: " << playerPoints << " , just type -> ";
        for (int a = 0; a < 7; ++a) {                                                                                   //Loop to assign chars to string randomly
            if ((rand() % 10 + 1) <= 2) {                                                                               //Numbers or Non alphanumeric chars 50% chance
                if ((rand() % 2 + 1) == 1) {
                    randomString += '*';                                                                                //Numbers from 0-9 are displayed
                    cout << "[0-9]";
                } else {
                    randomString += 48;                                                                                 //Non-alnum chars displayed
                    cout << "[%-&]";
                }
            } else {                                                                                                    //Upper or lower case letters 50% chance
                if ((rand() % 2 + 1) == 1) {
                    randomString += randInt('A', 26);                                                                   //Capital letters generated and displayed
                    cout << randomString[a];
                } else {
                    randomString += randInt('a', 26);                                                                   //Lower case letters generated and displayed
                    cout << randomString[a];
                }
            }
        }                                                                                                               //Steady_clock used to mimic stopwatch time
        auto startTimer = steady_clock::now();                                                                          //Starts timer when input begins
        cout << ": "; cin >> stringInput;
        auto endTimer = steady_clock::now();                                                                            //Ends timer after input finishes

        for (int b = 0; b < 7; ++b){
            if (isdigit(randomString[b])){
                count ++;
            }
            else if (! isalnum(randomString[b])){
                count ++;
            }
            else if (stringInput[b] == randomString[b]){
                count++;
            }
            else if (isspace(stringInput[b])){
                totalOffset += abs(randomString[b] - 32);
            }
            else if(stringInput[b] != randomString[b]){
                totalOffset += abs(randomString[b] - stringInput[b]);
            } else cout << "Something's wrong.";
        }
        if (stringInput.length() > 7) {
            cout << "You entered more than 7 characters!";                                                              //Loops back to start if input > 7 chars
            continue;
        }
        if (count == 7) inputMatchesString = true;                                                                      //Just makes code more readable
        auto diffTimer = endTimer - startTimer;
        auto timeElapsed = duration_cast<milliseconds>(diffTimer).count();
        cout << timeElapsed << " milliseconds, ";                                                                       //Calculates and displays time elapsed
        if (timeElapsed <= 7000){
            cout << "you made it within the interval of 7000...";
        } else cout << "you *failed* it within the interval of 7000...";

        if (timeElapsed <= 7000 && inputMatchesString){                                                                 //Adds 500pts if within time and string matches
            totalPenalty += 500;
            playerPoints += totalPenalty;
        } else if (timeElapsed <= 7000 && count < 7){                                                                   //Removes string offset from pts when within time
            totalPenalty -= totalOffset;
            playerPoints += totalPenalty;
        } else if (timeElapsed > 7000 && inputMatchesString){                                                           //Removes time penalty only with no offset
            totalPenalty -= (timeElapsed - 7000);
            playerPoints += totalPenalty;
        } else if (timeElapsed > 7000 && count < 7){                                                                    //Removes offset pts and time penalty
            totalPenalty -= (timeElapsed - 7000);
            totalPenalty -= totalOffset;
            playerPoints += totalPenalty;
        } else cout << "Something's wrong.";                                                                            //For testing purposes

        if (count < 7){
            cout << "\nString offset is " << totalOffset << ", ";                                                       //Displays total offset and penalty
            cout << "your total penalty is " << abs(totalPenalty) << "...";
        } else {/*No offset, so nothing happens*/}

        playerPoints;                                                                                                   //Loop doesn't break unless this is here
        if (playerPoints <= 0 || playerPoints >= 5000) break;                                                           //Case that breaks out of loop
    }
    cout << "\n=================================================";
    cout << "\nYour points: " << playerPoints << endl;
    cout << (playerPoints >= 5000 ? "You won!" : "You lost!");                                                          //Win or Lose
}
