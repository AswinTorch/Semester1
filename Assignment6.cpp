//Aswin Nair
//Assignment 6: Circle Art
#define _USE_MATH_DEFINES
#include <iostream>
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace Graph_lib;
using namespace std;

int main() {
	srand(unsigned(time(0)));
	int iterations, randomColor = rand() % 255, radius = 0, numberOfCircles;
	//Process
	while (true){
		cout << "Enter number of rings to generate: ";
		cin >> iterations;
		Point pointl(0,0);
		Simple_window window(pointl,500,500,"Assignment #6: Circle Art");
		//Creates the main big circle
		Circle mainCircle {Point{250,250},200};
		//Main circle set to black to increase visibility, all inner circles randomized.
		mainCircle.set_color(Color::black);
		window.attach(mainCircle);

		//Ring generation based on user input
		for (int a = 0; a < iterations; ++a){
			numberOfCircles = rand() % 10 + 2;
		    for (int a = 0; a < numberOfCircles; ++a){
		    	randomColor = rand() % 255;
		    	/*Calculation for radius of inner circle based on radius of outer (200) and
		    	  number of circles in one iteration (random 2-10 chosen). */
		    	radius = 200*sin(M_PI/numberOfCircles)/(1 + sin(M_PI/numberOfCircles));

		    	int theta = (2*M_PI)/numberOfCircles;
		    	int x = 250 + radius * cos(theta * M_PI / 180);
		    	int y = 250 + radius * sin(theta * M_PI / 180);
		    	Circle *circle = new Circle(Point{x,y},radius);
		    	circle->set_color(Color(randomColor));
		       	window.attach(*circle);
		   	}
		}


		//Displays number of whole ring generations (iterations)
		ostringstream ringNumText;
		if (iterations == 1) ringNumText << "After " << iterations << " ring generation";
		else ringNumText << "After " << iterations << " ring generations";
		Text text1 {Point{160,480}, ringNumText.str()};
		text1.set_color(Color::black);
		window.attach(text1);

		if (iterations < 0) {
			cout << "Bye..." << endl;
			break;
		}
	    window.wait_for_button();
	}
}

