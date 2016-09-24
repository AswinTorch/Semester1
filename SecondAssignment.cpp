#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std; using namespace chrono;
int randInt(int a, int b){return rand() % b + a;}
int main(){
    srand(time(0));
    int playerPoints = 1000;

    while (true){
        string randomString, inputString;
        int totalOffset = 0, totalPenalty = 0;
        bool stringsMatch;

        cout << "Your current points " << playerPoints << ", just type -> ";
        for (int a = 0; a < 7; ++a) {
            if (rand() % 10 + 1 <= 2){
                if (rand() % 2 + 1 == 1){
                    randomString += 48;
                    cout << "[0-9]";
                } else {
                    randomString += '*';
                    cout << "[%-&]";
                }
            } else {
                if (rand() % 2 + 1 == 1){
                    randomString += randInt('A', 26);
                    cout << randomString[a];
                } else {
                    randomString += randInt('a', 26);
                    cout << randomString[a];
                }
            }
        }
        cout << " :  ";
        auto startTimer = steady_clock::now();
        cin >> inputString;
        auto endTimer = steady_clock::now();
        auto timeElapsed = duration_cast<milliseconds>(endTimer - startTimer).count();

        while (inputString.length() < randomString.length()) inputString += ' ';
        while (randomString.length() < inputString.length()) randomString += ' ';

        for (int a = 0; a < randomString.length(); ++a) {
            if (randomString[a] == inputString[a]){
                stringsMatch = true;
            } else if (randomString[a] != inputString[a]){
                stringsMatch = false;
                totalOffset += abs(randomString[a] - inputString[a]);
                if (isdigit(randomString[a]) && isdigit(inputString[a])){
                    stringsMatch = true;
                    totalOffset -= abs(randomString[a] - inputString[a]);
                }else if (!(isalnum(randomString[a])) && !(isalnum(inputString[a])) && !(isspace(inputString[a]))){
                    stringsMatch = true;                    //It thinks space isnt alphanum so it accepts it.
                    totalOffset -= abs(randomString[a] - inputString[a]);
                }
            } else cout << "Error 1";
        }
        if (timeElapsed <= 7000) cout << timeElapsed << " milliseconds, you made it within the interval of 7000...\n";
        else cout << timeElapsed << " milliseconds, you *failed* it within the interval of 7000...\n";

        if (stringsMatch && timeElapsed <= 7000){
            playerPoints += 500;
        } else if (stringsMatch && timeElapsed > 7000){
            playerPoints -= (timeElapsed - 7000);
        } else if (!stringsMatch && timeElapsed < 7000){
            playerPoints -= totalOffset;
            cout << "String offset is " << totalOffset << ", your total penalty is " << totalOffset << "...\n";
        } else if (!stringsMatch && timeElapsed > 7000){
            totalPenalty += (totalOffset * 2);
            totalPenalty += abs(timeElapsed - 7000);
            playerPoints -= totalPenalty;
            cout << "String offset is " << totalOffset << ", your total penalty is " << totalPenalty << "...\n";
        } else cout << "Error 2";

        if (playerPoints <= 0 || playerPoints > 5000) break;
    }
    cout << "===============================================";
    cout << "\nPoints: " << playerPoints << endl;
    cout << (playerPoints >= 5000 ? "You won!" : "You lost!");
}
