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
#include <vector>
using namespace Graph_lib;
using namespace std;

int main() {
	srand(unsigned(time(0)));
	int iterations, randomColor = rand() % 255, radius = 0, numberOfCircles, outerRadius = 200;
	Vector_ref <Circle> circles; //vector_ref used for auto deallocation
	//Process
	while (true){
		cout << "Enter number of generations: "; cin >> iterations;
		Point pointl(0,0); Simple_window window(pointl,500,500,"Assignment #6: Circle Art");
		//Creates the main big circle
		Circle mainCircle {Point{250,250},200};
		//Main circle set to black to increase visibility, all inner circles randomized.
		mainCircle.set_color(Color::black);
		window.attach(mainCircle);

		//Ring generation based on user input
		for (int a = 0; a < iterations; ++a){
			numberOfCircles = rand() % 50 + 2; //Set from 2-50 to avoid no generations
		    for (int b = 0; b < numberOfCircles; ++b){
		    	randomColor = rand() % 255;
		    	/*Calculation for radius of inner circle based on radius of outer (200) and
		    	  number of circles in one iteration (random 2-10 chosen). */
		    	radius = outerRadius*sin(M_PI/numberOfCircles)/(1 + sin(M_PI/numberOfCircles));
		    	double theta = (2*M_PI/numberOfCircles)*b;
		    	//Calculation for position based on radius and center of outer circle.
		    	//(Formula used from Stack Overflow)
		    	double outerX = 250 + outerRadius * cos(theta), outerY = 250 + outerRadius * sin(theta);
		    	double x = outerX - (radius*cos(theta)), y = outerY - (radius*sin(theta));
		    	Circle *circle = new Circle(Point{x, y},radius);
		    	circle->set_color(Color(randomColor));
		       	window.attach(*circle);
		       	circles.push_back(circle);
		   	}
		}

		//Displays number of whole ring generations (iterations)
		ostringstream ringNumText;
		if (iterations == 1) ringNumText << "After " << iterations << " ring generation";
		else ringNumText << "After " << iterations << " ring generations";
		Text message {Point{160,480}, ringNumText.str()};
		message.set_color(Color::black);
		window.attach(message);
		if (iterations < 0) { cout << "Bye..." << endl; break; }
	        window.wait_for_button();

	    	//Detaching the circles for next input
	   	 for (int a = 0; a < circles.size(); ++a){
	    		window.detach(circles[a]);
	   	 }
	}
}
