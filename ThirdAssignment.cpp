#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    srand(time(0));                                                                                                     //Variables
    string input;
    int wordCount, strikeCount = 0, successCount = 0, missCount = 0;
    vector<string> animalNames(0);

    cout << "Enter at least five animal names, e.g., cat, dog, etc..." << endl;
    while (true) {
        cout << "> ";
        getline(cin, input);
        bool found = false;
        string word;
        if (input == "?") {
            for (int a = 0; a < animalNames.size(); ++a) {
                cout << a + 1 << ": " << animalNames[a] << endl;                                                        //Displays animal names entered if input is '?'
            }
        } else if (input == "quit") {
            cout << "\nBye..."; return 0;                                                                                                   //Quits game if user enters "quit"
        } else {
            for (int a = 0; a < input.length(); ++a) {
                if (!isspace(input[a])) {
                    word += input[a];
                    found = true;
                    continue;
                }                                                                                                       //For loop that parses string, removes spaces
                if (!found) continue;
                animalNames.push_back(word);
                word = "";
                found = false;
            }
            if (found) animalNames.push_back(word);
            if (input == "" && animalNames.size() < 5) cout << "Enter at least five names." << endl;                    //Cases to break loop of input
            if (input == "" && animalNames.size() >= 5) break;
        }
    }
    //Game Process
    for (int a = 0; a < animalNames.size(); ++a) {                                                                      //Displays animal names entered
        cout << a + 1 << ": " << animalNames[a] << endl;
    }

    while (true) {
        vector<string> challengeSet(0), temporaryVector(0), inputNames(0);
        string challengeString = "", word;
        bool found = false;
        temporaryVector = animalNames;
        random_shuffle(temporaryVector.begin(), temporaryVector.end());
        wordCount = rand() % 3 + 1;
        for (int a = 0; a < wordCount; ++a) {
            challengeSet.push_back(temporaryVector[a]);
        }
        for (int a = 0; a < challengeSet.size(); ++a) {                                                                 //Scrambling and making string
            challengeString += challengeSet[a];
        }
        random_shuffle(challengeString.begin(), challengeString.end());

        for (int a = 0; a < strikeCount; ++a) {
            while (true) {
                int position = rand() % challengeString.length();                                                       //Does underscore challenge under conditions
                if (challengeString[position] == '_') continue;
                challengeString[position] = '_';
                break;
            }
        }

        if (wordCount == 1) cout << "\nWhat is " << wordCount << " animal in \"" << challengeString << "\" ? ";
        else cout << "\nWhat are " << wordCount << " animals in \"" << challengeString << "\" ? ";

        getline(cin, input);
        if (input == "quit") {                                                                                           //Quits program if quit is entered
            cout << "\nBye..."; return 0;
        } else if (input == "?") {                                                                                       //Displays animal names entered if input is '?'
            for (int a = 0; a < animalNames.size(); ++a) {
                cout << a + 1 << ": " << animalNames[a] << endl;
            }
        } else {                                                                                                        //Takes in input
            if (input.length() < challengeString.length()) {
                cout << "Your number of input is incorrect. Enter again: ";
                input = "";
                getline(cin, input);
            }
            for (int a = 0; a < input.length(); ++a) {
                if (!isspace(input[a])) {
                    word += input[a];
                    found = true;
                    continue;
                }                                                                                                       //For loop that parses string, removes spaces
                if (!found) continue;
                inputNames.push_back(word);
                word = "";
                found = false;
            }
            if (found) inputNames.push_back(word);
            sort(inputNames.begin(), inputNames.end());
            sort(challengeSet.begin(), challengeSet.end());                                                             //Sort both arrays and compare if both are equal
        }

        if (inputNames == challengeSet) {
            cout << "Yes!" << endl;
            missCount = 0;
            ++successCount;
            if (successCount >= 2) {
                ++strikeCount;
                successCount = 0;
                cout << "Succeeded two consecutive times, challenge goes up!" << endl;
            }
        } else if (inputNames != challengeSet) {
            cout << "No!" << endl;
            successCount = 0;
            ++missCount;
            if (missCount >= 2) {
                --strikeCount;
                missCount = 0;
                cout << "Missed two consecutive times, challenge goes down!" << endl;
                if (strikeCount < 0) strikeCount = 0;
            }
        }
    }
}
