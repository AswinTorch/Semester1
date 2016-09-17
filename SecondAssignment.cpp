#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main (){
	srand(time(0));
	int playerPoints = 1000;
	string randomString;
	
	while (){
		cout << "Your current points: " << playerPoints << " , just type: ";
		if (rand() % 10 <= 2){
			//Numbers or Non alphanumeric chars 50% chance
			if (rand () % 2 == 1){
				//Numbers from 1 - 10
			}
			else {
				//Non alphanumeric chars
			}
		}
		else {
			//Upper or lower case letters 50% chance
			if (rand() % 2 == 1){
				//Upper case letters
			}
			else {
				//Lower case letters
			}
		}
		
		
		if (playerPoints <= 0 || playerPoints >= 5000) break;	//Case that breaks out of loop
	}
	
	
	
}
