#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    //Variables
    srand(time(0));
    string input;
    int wordCount, count = 0;
    vector<string> animalNames(0);
    //Input Process
    cout << "Enter at least five animal names such as cat, dog, etc..." << endl;
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
            return 0;                                                                                                   //Quits game if user enters "quit"
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

    while (true){
        vector <string> challengeSet(0), temporaryVector(0), inputNames(0);
        string challengeString = "", word;
        bool found = false;
        temporaryVector = animalNames;

        random_shuffle(temporaryVector.begin(), temporaryVector.end());
        wordCount = rand() % 3 + 1;
        for (int a = 0; a < wordCount; ++a){
            challengeSet.push_back(temporaryVector[a]);
        }
        for (int a = 0; a < challengeSet.size(); ++a) {                                                                 //Scrambling and making string
            challengeString += challengeSet[a];
        }
        random_shuffle(challengeString.begin(), challengeString.end());

        cout << "What are " << wordCount << " animals in \"" << challengeString << "\" ? ";
        getline(cin, input);
        if (input == "quit"){
            break;
        } else if (input == "?"){
            for (int a = 0; a < animalNames.size(); ++a) {
                cout << a + 1 << ": " << animalNames[a] << endl;                                                        //Displays animal names entered if input is '?'
            }
        } else {
            //Do token and delimit
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
            if (inputNames == challengeSet){
                cout << "Yes!" << endl;
                ++count;
            } else{
                cout << "No!" << endl;
                count = 0;
            }

            if (count == 2){
                cout << "Succeeded two consecutive times, challenge goes up!" << endl;
            }
        }
    }

    cout << "\nBye...";
}
