//Aswin Nair
//Typing Lesson
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std; using namespace chrono;
int randInt(int a, int b){return rand() % b + a;}                                                                       //RNG function for upper case and lower case letters
int main(){
    srand(time(0));                                                                                                     //Seed for rng
    int playerPoints = 1000;

    while (true){                                                                                                       //Loop
        string randomString, inputString;
        int totalOffset = 0, totalPenalty = 0;
        bool stringsMatch;

        cout << "Your current points " << playerPoints << ", just type -> ";
        for (int a = 0; a < 7; ++a) {
            if (rand() % 10 + 1 <= 2){                                                                                  //20% CHANCE OF NUMBERS OR NON ALPHA NUMERIC CHARS
                if (rand() % 2 + 1 == 1){
                    randomString += 48;
                    cout << "[0-9]";                                                                                    //50% chance of numbers displayed as [0-9], value is 0
                } else {
                    randomString += '*';                                                                                //50% chance of nonalnum displayed [%-&], value is *
                    cout << "[%-&]";
                }
            } else {                                                                                                    //80% CHANCE OF LETTERS
                if (rand() % 2 + 1 == 1){
                    randomString += randInt('A', 26);                                                                   //50% chance of upper case letters
                    cout << randomString[a];
                } else {
                    randomString += randInt('a', 26);                                                                   //50% chance of lower case letters
                    cout << randomString[a];
                }
            }
        }
        cout << " :  ";
        auto startTimer = steady_clock::now();                                                                          //Stopwatch starts timing
        cin >> inputString;
        auto endTimer = steady_clock::now();                                                                            //Stopwatch ends timing
        auto timeElapsed = duration_cast<milliseconds>(endTimer - startTimer).count();                                  //Calculates the diff to be time elapsed

        while (inputString.length() < randomString.length()) inputString += ' ';                                        //Adds spaces to inputString to match length of randomString
        while (randomString.length() < inputString.length()) randomString += ' ';                                       //Adds spaces to randomString to match length of inputString

        for (int a = 0; a < randomString.length(); ++a) {
            if (randomString[a] == inputString[a]){
                stringsMatch = true;
            } else if (randomString[a] != inputString[a]){
                if (isdigit(randomString[a]) && isdigit(inputString[a])){
                    stringsMatch = true;
                }else if (!(isalnum(randomString[a])) && !(isalnum(inputString[a])) && !(isspace(inputString[a]))){     //Calculating offset and comparing strings
                    stringsMatch = true;                                                                                //No errors after 100 tests
                }else {
                    stringsMatch = false;
                    totalOffset += abs(randomString[a] - inputString[a]);
                }
            } else cout << "Error 1";
        }
        if (timeElapsed <= 7000) cout << timeElapsed << " milliseconds, you made it within the interval of 7000...\n";  //Interval of 7000, pass or fail displayed
        else cout << timeElapsed << " milliseconds, you *failed* it within the interval of 7000...\n";

        if (stringsMatch && timeElapsed <= 7000){                                                                       //500 points if within time and strings match
            playerPoints += 500;
        } else if (stringsMatch && timeElapsed > 7000){                                                                 //Time penalty with no offset
            playerPoints -= (timeElapsed - 7000);
        } else if (!stringsMatch && timeElapsed < 7000){                                                                //Offset with no time penalty
            playerPoints -= totalOffset;
            cout << "String offset is " << totalOffset << ", your total penalty is " << totalOffset << "...\n";
        } else if (!stringsMatch && timeElapsed > 7000){                                                                //Offset and time penalty, double offset penalty
            totalPenalty += (totalOffset * 2);
            totalPenalty += abs(timeElapsed - 7000);
            playerPoints -= totalPenalty;
            cout << "String offset is " << totalOffset << ", your total penalty is " << totalPenalty << "...\n";
        } else cout << "Error 2";

        if (playerPoints <= 0 || playerPoints > 5000) break;                                                            //Loop breaks if playerPoints <= 0 or > 5000
    }
    cout << "===============================================";
    cout << "\nPoints: " << playerPoints << endl;
    cout << (playerPoints >= 5000 ? "You won!" : "You lost!");                                                          //Win or lose
}
