//Aswin Nair
//Assignment 7: Buffon's Needle
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Window.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace Graph_lib;
using namespace std;

struct Lines_window : Graph_lib::Window {
	    Lines_window(Point xy, int w, int h, const string& title );
	    //Needle variables
	    vector <Point*> midpoints, points1, points2, parallelPoints1, parallelPoints2;
	    vector <Text*> orderDisplayVector;
	    Graph_lib::Rectangle textBox;
	    Text piDisplay;
	    vector <Line*> needles, parallelLines;
	private:
	    //Buttons and Menus (Widgets)
	    Button quitButton, dropButton, menuButton;
	    In_box dropCountInput;
	    Menu motionMenu;

	    //Callback functions
	    static void cb_count(Address, Address);
	    static void cb_rotate(Address, Address);
	    static void cb_unlist(Address, Address);
        static void cb_menu(Address, Address);
	    static void cb_quit(Address, Address);
	    static void cb_drop(Address, Address);

	    //Actions invoked by callback functions
	    void hide_menu() { motionMenu.hide(); menuButton.show(); }
	    void count_pressed();
	    void rotate_pressed();
	    void unlist_pressed();
	    void menu_pressed() { menuButton.hide(); motionMenu.show(); }
	    void quit();
	    void drop();
	};
Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),
    quitButton(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
	dropButton(Point(x_max()-150,0), 70, 20, "Drop", cb_drop),
	menuButton(Point(x_max()-90,30), 90, 20, "Motion Menu", cb_menu),
	dropCountInput(Point(x_max()-230,0), 70, 20, "Enter Drop Count:"),
	motionMenu(Point(x_max()-70,30),70,20,Menu::vertical,"Motion"),
	textBox (Point{350, 325}, Point{1050, 350}),
	piDisplay(Point{490, 345}, "")
{
		//Attaching menus
		attach(dropCountInput);
    	attach(quitButton);
    	attach(dropButton);
    	motionMenu.attach(new Button(Point(0,0),0,0,"Count",cb_count));
    	motionMenu.attach(new Button(Point(0,0),0,0,"Rotate",cb_rotate));
    	motionMenu.attach(new Button(Point(0,0),0,0,"(Un)List",cb_unlist));
        attach(motionMenu);
    	motionMenu.hide();
    	attach(menuButton);

        //Constant Parallel Lines
        for (int a = 200; a <= 1200; a += 200){
        	Point* p1 = new Point(a,25); parallelPoints1.push_back(p1);
        	Point* p2 = new Point(a,675); parallelPoints2.push_back(p2);
        	Line* parallelLine = new Line(*p1, *p2);
        	parallelLines.push_back(parallelLine);
        }
        for (int a = 0; a < parallelLines.size(); ++a){
        	parallelLines[a]->set_color(Color::blue);
        	attach (*parallelLines[a]);
        }
}

void Lines_window::cb_drop(Address, Address pw) { reference_to<Lines_window>(pw).drop(); }
void Lines_window::cb_quit(Address, Address pw) { reference_to<Lines_window>(pw).quit(); }
void Lines_window::cb_count(Address, Address pw) { reference_to<Lines_window>(pw).count_pressed(); }
void Lines_window::cb_rotate(Address, Address pw) { reference_to<Lines_window>(pw).rotate_pressed(); }
void Lines_window::cb_unlist(Address, Address pw) { reference_to<Lines_window>(pw).unlist_pressed(); }
void Lines_window::cb_menu(Address, Address pw) { reference_to<Lines_window>(pw).menu_pressed(); }

//Functions
void Lines_window::quit() { hide(); }
void Lines_window::drop() {
	//Drops the needles according to user input
	int dropCount = dropCountInput.get_int();
	for (int a = 0; a < needles.size(); ++a){ detach(*needles[a]); delete needles[a]; delete points1[a]; delete points2[a]; delete midpoints[a];}
	for (int b = 0; b < orderDisplayVector.size(); ++b) {detach(*orderDisplayVector[b]); delete orderDisplayVector[b];}
	needles.clear(); midpoints.clear(); points1.clear(); points2.clear(); orderDisplayVector.clear(); detach(piDisplay); detach(textBox);
	int x, y; double x1, y1, x2, y2, theta = 0;
	for(int a = 0; a < dropCount; ++a){
		theta = (rand()%360) * (M_PI/180);
		x = rand() % 1200 + 100; y = rand() % 600 + 50;
		Point* midpoint = new Point(x,y); midpoints.push_back(midpoint);
		x1 = x + 100*cos(theta); y1 = y + 100*sin(theta);
		Point* p1 = new Point(x1,y1); points1.push_back(p1);
		x2 = x - (100 * cos(theta)); y2 = y - (100 * sin(theta));
	    Point* p2 = new Point (x2,y2); points2.push_back(p2);
		Line* needle = new Line(Point(x1,y1), Point(x2,y2));
		needles.push_back(needle);
		attach(*needles[a]);
	}
	redraw();
}
void Lines_window::count_pressed() {
	//Counts and colors the crossed needles red, approximates and displays pi.
	for (int a = 0; a < orderDisplayVector.size(); ++a) { detach(*orderDisplayVector[a]); delete orderDisplayVector[a]; }
	detach(piDisplay); detach(textBox); orderDisplayVector.clear();
	int dropCount = dropCountInput.get_int(), crossedCount = 0, mainX;
	//Calculating the intersecting lines and coloring them red
	for (int a = 0; a < needles.size(); ++a){
		for (int b = 0; b < parallelLines.size(); ++b){
			mainX = parallelPoints1[b]->x;
			if (points1[a]->x < mainX && points2[a]->x > mainX){
				needles[a]->set_color(Color::red);
				++crossedCount;
			} else if (points2[a]->x < mainX && points1[a]->x > mainX){
				needles[a]->set_color(Color::red);
				++crossedCount;
			}
		}
	}
	//Calculation and display of pi
	double calculatedPi = double(2 * dropCount)/double(crossedCount);
	textBox.set_fill_color(Color::white);
	attach(textBox);

	ostringstream piMessage;
	piMessage << "Found " << crossedCount << " crossed needles, and estimated pi is " << calculatedPi << "!";
	piDisplay.set_label(piMessage.str());
	attach(piDisplay);
	redraw();
}
void Lines_window::rotate_pressed() {
	//Rotates the needles on a random angle, resets color to black, removes order display
	int dropCount = dropCountInput.get_int();
	for (int a = 0; a < needles.size(); ++a){ detach(*needles[a]); delete needles[a]; delete points1[a]; delete points2[a]; }
	for (int a = 0; a < orderDisplayVector.size(); ++a) {detach(*orderDisplayVector[a]); delete orderDisplayVector[a];}
	needles.clear(); points1.clear(); points2.clear(); orderDisplayVector.clear(); detach(piDisplay); detach(textBox);

	double x1, y1, x2, y2, theta = 0;
	for (int a = 0; a < dropCount; ++a){
		theta = (rand() % 360) * (M_PI/180);
		x1 = midpoints[a]->x + 100*cos(theta), y1 = midpoints[a]->y + 100*sin(theta);
		x2 = midpoints[a]->x - 100*cos(theta), y2 = midpoints[a]->y - 100*sin(theta);
		Point* p1 = new Point(x1,y1); points1.push_back(p1);
		Point* p2 = new Point (x2,y2); points2.push_back(p2);
		Line* needle = new Line (Point (x1, y1), Point (x2, y2));
		needles.push_back(needle);
		attach(*needles[a]);
	}
	redraw();
}
void Lines_window::unlist_pressed() {
	//(Un)Lists the order of the creation of needles next to their midpoints
	for (int a = 0; a < orderDisplayVector.size(); ++a) {detach(*orderDisplayVector[a]); delete orderDisplayVector[a]; }
	detach(piDisplay); detach(textBox);
	if (orderDisplayVector.size() == 0){
		for (int a = 0; a < needles.size(); ++a) needles[a]->set_color(Color::black);
		int dropOrder = 0;
		for (int a = 0; a < midpoints.size(); ++a){
			ostringstream orderMessage;
			orderMessage << a + 1;
			Text* orderDisplay = new Text (*midpoints[a], orderMessage.str());
			orderDisplayVector.push_back(orderDisplay);
			attach(*orderDisplayVector[a]);
		}
	} else {
		orderDisplayVector.clear();
		for (int a = 0; a < orderDisplayVector.size(); ++a) {detach(*orderDisplayVector[a]); delete orderDisplayVector[a]; }
	}
	redraw();
}

int main() {
	srand(unsigned(time(0)));
	Lines_window mainWindow(Point(0,0),1400,700,"Assignment 7: Buffon's Needle");
	gui_main(); //Runs the program
}
