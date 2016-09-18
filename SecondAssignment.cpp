#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using  ms = chrono::milliseconds;
using get_time = chrono::steady_clock ;

int randInt(int a, int b) {
    return (rand() % b + a);
}

int main() {
    srand(time(0));
    int playerPoints = 1000;
    string randomString, playerInput;

    while (true) {
        int count = 0, totalOffset = 0, offSet, totalPenalty = 0;
        cout << "\nYour current points: " << playerPoints << " , just type -> ";
        for (int a = 0; a < 7; ++a) {                                                                                   //Loop to assign chars to string randomly
            if ((rand() % 10 + 1) <= 2) {
                //Numbers or Non alphanumeric chars 50% chance
                if ((rand() % 2 + 1) == 1) {
                    randomString[a] = randInt(48, 10);                                                                  //Numbers from 0-9
                    cout << randomString[a];
                } else {
                    randomString[a] = randInt(33, 15);                                                                  //Non-alphanumeric characters
                    cout << randomString[a];
                }
            } else {
                //Upper or lower case letters 50% chance
                if ((rand() % 2 + 1) == 1) {
                    randomString[a] = randInt(65, 26);                                                                  //Capital letters
                    cout << randomString[a];
                } else {
                    randomString[a] = randInt(97, 26);                                                                  //Lowercase letters
                    cout << randomString[a];
                }
            }
        }
        auto start = get_time::now();                                                                                   //Starts timer when input begins
        cout << ": "; cin >> playerInput;
        auto end = get_time::now();                                                                                     //Ends timer after input finishes

        for (int b = 0; b < 7; ++b){                                                                                    //Checks if input matches random string
            if (playerInput[b] == randomString[b]){
                count++;
            }
            else {
                offSet = playerInput[b] - randomString[b];
                totalOffset += abs(offSet);
            }
        }
        cout << count;

        auto diff = end - start;
        long timeElapsed = chrono::duration_cast<ms>(diff).count();
        cout << timeElapsed << " milliseconds, ";                                                                       //Displays time elapsed
        if (timeElapsed <= 7000){
            cout << "you made it within the interval of 7000...";
        } else cout << "you *failed* it within the interval of 7000...";

        if (count < 7){
            cout << "\nString offset is " << totalOffset << ", ";        //Total Offset
        } else //No offset

        if (timeElapsed <= 7000){                           //If within time interval
            if (count == 7){
                totalPenalty += 500;                        //No offset, perfect score
            } else if (count < 7){
                totalPenalty -= totalOffset;                //Offset
            }
        }
        else if (timeElapsed > 7000){                       //If above time interval
            if (count == 7){
                totalPenalty -= (timeElapsed - 7000);       //Time penalty with no offset
            } else if (count < 7) {
                totalPenalty -= (timeElapsed - 7000);
                totalPenalty -= totalOffset;                //Offset with time penalty
            }
        }
        cout << "your total penalty is " << totalPenalty << "...";
        playerPoints += totalPenalty;

        if (playerPoints <= 0 || playerPoints >= 5000) break;                                                           //Case that breaks out of loop
    }

    cout << "\nYOUR POINTS: " << playerPoints << "\nBye.";
}
