//Aswin Nair
//Animal Quiz Word Scrambler Game
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
        cout << "> "; getline(cin, input);                                                                              //First input prompting to enter at least 5 words
        bool found = false; string word;
        if (input == "?") {
            for (int a = 0; a < animalNames.size(); ++a) {
                cout << a + 1 << ": " << animalNames[a] << endl;                                                        //Displays animal names entered if input is '?'
            }
        } else if (input == "quit") {
            cout << "\nBye..."; return 0;                                                                               //Quits game if user enters "quit"
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
    for (int a = 0; a < animalNames.size(); ++a) {                                                                      //Displays animal names entered
        cout << a + 1 << ": " << animalNames[a] << endl;
    }
    while (true) {
        vector<string> challengeSet(0), temporaryVector(0), inputNames(0);
        string challengeString = "", word;
        bool found = false;
        temporaryVector = animalNames;                                                                                  //Keeps animalNames intact by using a temp vector to shuffle
        random_shuffle(temporaryVector.begin(), temporaryVector.end());
        wordCount = rand() % 3 + 1;
        for (int a = 0; a < wordCount; ++a) {
            challengeSet.push_back(temporaryVector[a]);
        }
        for (int a = 0; a < challengeSet.size(); ++a) {                                                                 //Scrambling and creating string
            challengeString += challengeSet[a];
        }
        random_shuffle(challengeString.begin(), challengeString.end());

        for (int a = 0; a < strikeCount; ++a) {
            while (true) {
                int position = rand() % challengeString.length();                                                       //Does underscore challenge under strike conditions
                if (challengeString[position] == '_') continue;
                challengeString[position] = '_';
                break;
            }
        }
        if (wordCount == 1) cout << "\nWhat is " << wordCount << " animal in \"" << challengeString << "\" ? ";         //Question to the user
        else cout << "\nWhat are " << wordCount << " animals in \"" << challengeString << "\" ? ";
        getline(cin, input);
        if (input == "quit") {                                                                                          //Quits program if quit is entered
            cout << "\nBye..."; return 0;
        } else if (input == "?") {                                                                                      //Displays animal names entered if input is '?'
            for (int a = 0; a < animalNames.size(); ++a) {
                cout << a + 1 << ": " << animalNames[a] << endl;
            }
        } else {
            while (true) {
                inputNames.clear(); word = "";
                for (int a = 0; a < input.length(); ++a) {
                    if (!isspace(input[a])) {
                        word += input[a];
                        found = true;
                        continue;
                    }                                                                                                   //For-loop that parses string, removes spaces
                    if (!found) continue;
                    inputNames.push_back(word);
                    word = "";
                    found = false;
                }
                if (found) inputNames.push_back(word);
                sort(inputNames.begin(), inputNames.end());                                                             //Sorts for conditions to work
                sort(challengeSet.begin(), challengeSet.end());
                if (inputNames.size() == challengeSet.size()) break;
                else if (inputNames.size() < challengeSet.size() || inputNames.size() > challengeSet.size()){
                    cout << "Your number of input is incorrect. Enter again: ";                                         //Input check
                    getline(cin, input);
                    if (input == "quit") {
                        cout << "\nBye...";
                        return 0;                                                                                       //Quits program if quit is entered in input check
                    }
                }
            }
        }
        if (inputNames == challengeSet) {                                                                               //When user answers correctly
            cout << "Yes!" << endl;
            missCount = 0; ++successCount;
            if (successCount >= 2) {
                ++strikeCount; successCount = 0;
                cout << "Succeeded two consecutive times, challenge goes up!" << endl;
            }
        } else if (inputNames != challengeSet) {                                                                        //When user answers incorrectly
            cout << "Nope!" << endl;
            successCount = 0; ++missCount;
            if (missCount >= 2) {
                --strikeCount; missCount = 0;
                cout << "Missed two consecutive times, challenge goes down!" << endl;
                if (strikeCount < 0) strikeCount = 0;
            }
        }
    }
}
